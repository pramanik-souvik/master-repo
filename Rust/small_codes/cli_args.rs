// CLI Arguments: Simple Utility (Fixed)
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage:");
        println!("  greet [name]       → Greets a user");
        println!("  reverse [text]     → Reverses the given text");
        println!("  length [text]      → Shows length of the text");
        return;
    }

    match args[1].as_str() {
        "greet" => {
            let name = if let Some(n) = args.get(2) {
                n.clone()
            } else {
                "Friend".to_string()
            };
            println!("Hello, {}!", name);
        }
        "reverse" => {
            let text = if let Some(t) = args.get(2) {
                t.clone()
            } else {
                "Rust".to_string()
            };
            let reversed: String = text.chars().rev().collect();
            println!("Reversed: {}", reversed);
        }
        "length" => {
            let text = if let Some(t) = args.get(2) {
                t.clone()
            } else {
                "Rust".to_string()
            };
            println!("Length: {}", text.len());
        }
        _ => println!("Unknown command: {}", args[1]),
    }
}