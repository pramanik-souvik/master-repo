use std::fs::{self, OpenOptions};
use std::io::Write;
// use std::path::Path;

fn main() {
    let file_path = "rust_output.txt";

    // Write initial content
    fs::write(file_path, "Hello from Rust!\n").expect("Failed to write file");

    // Append additional content
    let mut file = OpenOptions::new()
        .append(true)
        .open(file_path)
        .expect("Failed to open file for appending");
    writeln!(file, "Appending a new line to the file!").expect("Failed to append");

    // Read and display content
    let content = fs::read_to_string(file_path).expect("Failed to read file");
    println!("File Content:\n{}", content);

    // List all text files in current directory
    println!("\nAll .txt files in current directory:");
    for entry in fs::read_dir(".").expect("Failed to read directory") {
        let entry = entry.expect("Failed to read entry");
        let path = entry.path();
        if path.is_file() && path.extension().and_then(|s| s.to_str()) == Some("txt") {
            println!("- {}", path.display());
        }
    }
}