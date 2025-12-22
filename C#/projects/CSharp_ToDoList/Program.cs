using System;
using System.Collections.Generic;
using System.Linq;

namespace TodoListProject
{
    class TaskItem
    {
        public int Id { get; set; }
        public string Description { get; set; }
        public DateTime? DueDate { get; set; }
        public bool Completed { get; set; }
        public string Priority { get; set; } // Low, Medium, High
    }

    class TodoApp
    {
        static List<TaskItem> todos = new List<TaskItem>();
        static int nextId = 1;

        static void Main()
        {
            Console.Title = "Advanced To-Do List";
            bool running = true;
            while (running)
            {
                ShowMenu();
                Console.Write("Choose an option: ");
                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1": AddTask(); break;
                    case "2": ViewTasks(); break;
                    case "3": MarkCompleted(); break;
                    case "4": EditTask(); break;
                    case "5": DeleteTask(); break;
                    case "6": SearchTask(); break;
                    case "7": SortTasks(); break;
                    case "8": ClearCompleted(); break;
                    case "0": running = false; Console.WriteLine("Goodbye!"); break;
                    default: Console.WriteLine("Invalid option."); break;
                }

                if (running)
                {
                    Console.WriteLine("\nPress any key to return to menu...");
                    Console.ReadKey();
                    Console.Clear();
                }
            }
        }

        static void ShowMenu()
        {
            Console.WriteLine("=========== TO-DO LIST ===========");
            Console.WriteLine("1. Add Task");
            Console.WriteLine("2. View All Tasks");
            Console.WriteLine("3. Mark Task as Completed");
            Console.WriteLine("4. Edit Task");
            Console.WriteLine("5. Delete Task");
            Console.WriteLine("6. Search Task");
            Console.WriteLine("7. Sort Tasks");
            Console.WriteLine("8. Clear Completed Tasks");
            Console.WriteLine("0. Exit");
            Console.WriteLine("==================================");
        }

        static void AddTask()
        {
            Console.Write("Enter task description: ");
            string desc = Console.ReadLine();

            Console.Write("Enter priority (Low, Medium, High): ");
            string priority = Console.ReadLine();

            Console.Write("Enter due date (yyyy-mm-dd) or leave blank: ");
            string dateInput = Console.ReadLine();
            DateTime? dueDate = null;
            if (DateTime.TryParse(dateInput, out DateTime parsedDate))
                dueDate = parsedDate;

            todos.Add(new TaskItem
            {
                Id = nextId++,
                Description = desc,
                Priority = priority,
                DueDate = dueDate,
                Completed = false
            });

            Console.WriteLine("Task added successfully.");
        }

        static void ViewTasks()
        {
            if (todos.Count == 0)
            {
                Console.WriteLine("No tasks found.");
                return;
            }

            Console.WriteLine("\n--- TASK LIST ---");
            foreach (var t in todos)
            {
                string status = t.Completed ? "[X]" : "[ ]";
                string due = t.DueDate.HasValue ? t.DueDate.Value.ToShortDateString() : "No due date";
                Console.WriteLine($"{status} #{t.Id} {t.Description} | Priority: {t.Priority} | Due: {due}");
            }
        }

        static void MarkCompleted()
        {
            Console.Write("Enter task ID to mark complete: ");
            if (int.TryParse(Console.ReadLine(), out int id))
            {
                var task = todos.FirstOrDefault(t => t.Id == id);
                if (task != null)
                {
                    task.Completed = true;
                    Console.WriteLine("Task marked as completed.");
                }
                else
                    Console.WriteLine("Task not found.");
            }
        }

        static void EditTask()
        {
            Console.Write("Enter task ID to edit: ");
            if (int.TryParse(Console.ReadLine(), out int id))
            {
                var task = todos.FirstOrDefault(t => t.Id == id);
                if (task != null)
                {
                    Console.Write("New description (leave blank to keep): ");
                    string desc = Console.ReadLine();
                    if (!string.IsNullOrWhiteSpace(desc)) task.Description = desc;

                    Console.Write("New priority (leave blank to keep): ");
                    string priority = Console.ReadLine();
                    if (!string.IsNullOrWhiteSpace(priority)) task.Priority = priority;

                    Console.Write("New due date (yyyy-mm-dd) or blank: ");
                    string date = Console.ReadLine();
                    if (DateTime.TryParse(date, out DateTime newDate)) task.DueDate = newDate;

                    Console.WriteLine("Task updated.");
                }
                else
                    Console.WriteLine("Task not found.");
            }
        }

        static void DeleteTask()
        {
            Console.Write("Enter task ID to delete: ");
            if (int.TryParse(Console.ReadLine(), out int id))
            {
                var task = todos.FirstOrDefault(t => t.Id == id);
                if (task != null)
                {
                    todos.Remove(task);
                    Console.WriteLine("Task deleted.");
                }
                else
                    Console.WriteLine("Task not found.");
            }
        }

        static void SearchTask()
        {
            Console.Write("Enter keyword: ");
            string keyword = Console.ReadLine().ToLower();
            var results = todos.Where(t => t.Description.ToLower().Contains(keyword)).ToList();

            if (results.Count == 0)
            {
                Console.WriteLine("No matching tasks found.");
                return;
            }

            Console.WriteLine("\n--- SEARCH RESULTS ---");
            foreach (var t in results)
                Console.WriteLine($"#{t.Id} {t.Description} (Priority: {t.Priority})");
        }

        static void SortTasks()
        {
            Console.WriteLine("Sort by: 1. Priority  2. Due Date");
            string option = Console.ReadLine();

            if (option == "1")
            {
                todos = todos
                    .OrderByDescending(t => t.Priority.Equals("High", StringComparison.OrdinalIgnoreCase))
                    .ThenByDescending(t => t.Priority.Equals("Medium", StringComparison.OrdinalIgnoreCase))
                    .ThenBy(t => t.Priority.Equals("Low", StringComparison.OrdinalIgnoreCase))
                    .ToList();
                Console.WriteLine("Sorted by priority.");
            }
            else if (option == "2")
            {
                todos = todos.OrderBy(t => t.DueDate ?? DateTime.MaxValue).ToList();
                Console.WriteLine("Sorted by due date.");
            }
        }

        static void ClearCompleted()
        {
            todos.RemoveAll(t => t.Completed);
            Console.WriteLine("All completed tasks cleared.");
        }
    }
}