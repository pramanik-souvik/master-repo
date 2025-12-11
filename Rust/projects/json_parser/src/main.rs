use serde_json::Value;
use std::fs;
use std::io::{self, Write};
use colored::*;

fn load_json(file_path: &str) -> Option<Value> {
    match fs::read_to_string(file_path) {
        Ok(content) => match serde_json::from_str(&content) {
            Ok(json) => Some(json),
            Err(e) => {
                eprintln!("{} {}", "JSON parse error:".red(), e);
                None
            }
        },
        Err(e) => {
            eprintln!("{} {}", "File read error:".red(), e);
            None
        }
    }
}

fn save_json(file_path: &str, json: &Value) {
    match fs::write(file_path, serde_json::to_string_pretty(json).unwrap()) {
        Ok(_) => println!("{}", "JSON saved successfully!".green()),
        Err(e) => eprintln!("{} {}", "File write error:".red(), e),
    }
}

fn query_json(json: &Value) {
    println!("{}", "Enter a key to query (or 'exit' to quit):".yellow());
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let key = input.trim();
    if key == "exit" {
        println!("{}", "Exiting query mode.".green());
        return;
    }

    match json.get(key) {
        Some(value) => println!("{} {}", "Value:".green(), value),
        None => println!("{}", "Key not found!".red()),
    }
}

fn update_json(json: &mut Value) {
    if let Value::Object(map) = json {
        println!("{}", "Enter key to update:".yellow());
        let mut key = String::new();
        io::stdin().read_line(&mut key).unwrap();
        let key = key.trim();

        println!("{}", "Enter new value:".yellow());
        let mut val = String::new();
        io::stdin().read_line(&mut val).unwrap();
        let val = val.trim();

        map.insert(key.to_string(), Value::String(val.to_string()));
        println!("{} '{}' updated!", "Success:".green(), key);
    } else {
        println!("{}", "JSON root is not an object, cannot update.".red());
    }
}

fn main() {
    println!("{}", "=== Rust JSON File Manager ===".bold().cyan());

    let mut json_data: Option<Value> = None;
    let mut file_path: Option<String> = None;

    loop {
        println!("\n{}", "Menu:".bold());
        println!("1. Load JSON file");
        println!("2. Query JSON key");
        println!("3. Update JSON key");
        println!("4. Save JSON file");
        println!("5. Exit");

        let mut choice = String::new();
        io::stdin().read_line(&mut choice).unwrap();
        let choice = choice.trim();

        match choice {
            "1" => {
                println!("Enter file path to load:");
                let mut path = String::new();
                io::stdin().read_line(&mut path).unwrap();
                let path = path.trim().to_string();
                file_path = Some(path.clone());
                json_data = load_json(&path);
            }
            "2" => {
                if let Some(json) = &json_data {
                    query_json(json);
                } else {
                    println!("{}", "No JSON loaded!".red());
                }
            }
            "3" => {
                if let Some(json) = &mut json_data {
                    update_json(json);
                } else {
                    println!("{}", "No JSON loaded!".red());
                }
            }
            "4" => {
                if let (Some(json), Some(path)) = (&json_data, &file_path) {
                    save_json(path, json);
                } else {
                    println!("{}", "No JSON loaded or no file path set!".red());
                }
            }
            "5" => {
                println!("{}", "Exiting program.".green());
                break;
            }
            _ => println!("{}", "Invalid choice!".red()),
        }
    }
}