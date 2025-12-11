use crate::models::Todo;
use serde_json;
use std::fs;

pub fn load_todos() -> Vec<Todo> {
    if let Ok(data) = fs::read_to_string("todos.json") {
        if let Ok(todos) = serde_json::from_str(&data) {
            return todos;
        }
    }
    vec![]
}

pub fn save_todos(todos: &Vec<Todo>) {
    if let Ok(data) = serde_json::to_string_pretty(todos) {
        let _ = fs::write("todos.json", data);
    }
}
