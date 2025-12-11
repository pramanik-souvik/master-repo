use chrono::{Datelike, Local, NaiveDate};
use eframe::egui;
/*
use serde::{Deserialize, Serialize};
use std::fs;
*/

mod models;
use models::{Priority, Todo};

mod storage;
use storage::{load_todos, save_todos};

#[derive(Default)]
struct TodoApp {
    todos: Vec<Todo>,
    new_task: String,
    new_priority: Priority,
    new_year: i32,
    new_month: u32,
    new_day: u32,
    filter_done: bool,
    filter_pending: bool,
}

impl TodoApp {
    fn add_task(&mut self) {
        let deadline = NaiveDate::from_ymd_opt(self.new_year, self.new_month, self.new_day);
        self.todos.push(Todo {
            task: self.new_task.clone(),
            done: false,
            priority: self.new_priority.clone(),
            deadline,
        });
        self.new_task.clear();
        save_todos(&self.todos);
    }

    fn delete_task(&mut self, index: usize) {
        self.todos.remove(index);
        save_todos(&self.todos);
    }

    fn init_date(&mut self) {
        let today = Local::today();
        self.new_year = today.year();
        self.new_month = today.month();
        self.new_day = today.day();
    }
}

impl eframe::App for TodoApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::SidePanel::left("add_panel").show(ctx, |ui| {
            ui.heading("Add Task");

            ui.label("Task:");
            ui.text_edit_singleline(&mut self.new_task);

            ui.label("Priority:");
            egui::ComboBox::from_label("")
                .selected_text(format!("{:?}", self.new_priority))
                .show_ui(ui, |cb| {
                    cb.selectable_value(&mut self.new_priority, Priority::Low, "Low");
                    cb.selectable_value(&mut self.new_priority, Priority::Medium, "Medium");
                    cb.selectable_value(&mut self.new_priority, Priority::High, "High");
                });

            ui.label("Deadline:");
            ui.horizontal(|ui| {
                ui.add(egui::DragValue::new(&mut self.new_year).clamp_range(1900..=2100));
                ui.add(egui::DragValue::new(&mut self.new_month).clamp_range(1..=12));
                ui.add(egui::DragValue::new(&mut self.new_day).clamp_range(1..=31));
            });

            if ui.button("Add Task").clicked() && !self.new_task.is_empty() {
                self.add_task();
            }
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Professional Rust To-Do List");

            ui.horizontal(|ui| {
                ui.checkbox(&mut self.filter_done, "Show Done");
                ui.checkbox(&mut self.filter_pending, "Show Pending");
            });

            ui.separator();

            egui::ScrollArea::vertical().show(ui, |ui| {
                let mut remove_indices = vec![];
                for (i, todo) in self.todos.iter_mut().enumerate() {
                    if (self.filter_done && todo.done)
                        || (self.filter_pending && !todo.done)
                        || (!self.filter_done && !self.filter_pending)
                    {
                        ui.horizontal(|ui| {
                            ui.checkbox(&mut todo.done, "");
                            let color = match todo.priority {
                                Priority::High => egui::Color32::RED,
                                Priority::Medium => egui::Color32::YELLOW,
                                Priority::Low => egui::Color32::GREEN,
                            };
                            ui.colored_label(color, format!(
                                "{}{}",
                                todo.task,
                                todo.deadline.map_or("".into(), |d| format!(" (Due: {})", d))
                            ));

                            if ui.button("Delete").clicked() {
                                remove_indices.push(i);
                            }
                        });
                    }
                }

                for &i in remove_indices.iter().rev() {
                    self.delete_task(i);
                }
            });
        });
    }
}

fn main() -> eframe::Result<()> {
    let mut app = TodoApp::default();
    app.todos = load_todos();
    app.init_date();

    let options = eframe::NativeOptions::default();
    eframe::run_native(
        "Professional Rust To-Do App",
        options,
        Box::new(|_cc| Ok(Box::new(app))),
    )
}