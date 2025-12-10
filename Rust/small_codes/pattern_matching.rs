// Pattern matching demo with references
enum Status {
    Success(u16),
    Warning(u16),
    Error(String),
}

fn main() {
    let codes = [
        Status::Success(200),
        Status::Warning(300),
        Status::Error("Network failure".into()),
    ];

    for code in &codes {
        match code {
            &Status::Success(n) => println!("Success code: {}", n),
            &Status::Warning(n) => println!("Warning code: {}", n),
            &Status::Error(ref msg) => println!("Error: {}", msg),
        }
    }
}