use serde::{Serialize, Deserialize};
use serde_json::{self, Value};
use std::fs::{self, OpenOptions};
use std::io::{self, Write};

#[derive(Serialize, Deserialize, Debug)]
struct User {
    name: String,
    age: u8,
    email: String,
}

const FILE_PATH: &str = "users.json";

// Load users from JSON file
fn load_users() -> Vec<User> {
    if let Ok(data) = fs::read_to_string(FILE_PATH) {
        if let Ok(users) = serde_json::from_str::<Vec<User>>(&data) {
            return users;
        }
    }
    vec![]
}

// Save users to JSON file
fn save_users(users: &Vec<User>) {
    let json_data = serde_json::to_string_pretty(users).expect("Failed to serialize users");
    fs::write(FILE_PATH, json_data).expect("Failed to write file");
}

// Add a new user via CLI
fn add_user(users: &mut Vec<User>) {
    let mut name = String::new();
    let mut age = String::new();
    let mut email = String::new();

    println!("Enter name: ");
    io::stdin().read_line(&mut name).unwrap();
    println!("Enter age: ");
    io::stdin().read_line(&mut age).unwrap();
    println!("Enter email: ");
    io::stdin().read_line(&mut email).unwrap();

    let user = User {
        name: name.trim().to_string(),
        age: age.trim().parse().unwrap_or(0),
        email: email.trim().to_string(),
    };
    users.push(user);
    save_users(users);
    println!("User added successfully!\n");
}

// List all users
fn list_users(users: &Vec<User>) {
    println!("--- User List ---");
    for (i, user) in users.iter().enumerate() {
        println!("{}: {} ({} years) - {}", i + 1, user.name, user.age, user.email);
    }
    println!("-----------------\n");
}

// CLI menu
fn main() {
    let mut users = load_users();

    loop {
        println!("=== JSON User Manager ===");
        println!("1. List users");
        println!("2. Add user");
        println!("3. Exit");
        println!("Enter choice: ");

        let mut choice = String::new();
        io::stdin().read_line(&mut choice).unwrap();

        match choice.trim() {
            "1" => list_users(&users),
            "2" => add_user(&mut users),
            "3" => {
                println!("Exiting...");
                break;
            }
            _ => println!("Invalid choice!"),
        }
    }
}