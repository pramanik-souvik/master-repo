// Enhanced Error Handling Demo
fn divide(a: f64, b: f64) -> Result<f64, String> {
    if b == 0.0 {
        Err("Division by zero is not allowed".into())
    } else {
        Ok(a / b)
    }
}

fn main() {
    // Demonstrate Result handling
    let divisions = vec![(10.0, 2.0), (5.0, 0.0), (7.0, 3.0)];
    for (a, b) in divisions {
        match divide(a, b) {
            Ok(result) => println!("{} ÷ {} = {:.2}", a, b, result),
            Err(err) => println!("Failed to divide {} by {}: {}", a, b, err),
        }
    }

    // Demonstrate Option with unwrap_or
    let some_value: Option<i32> = Some(42);
    let none_value: Option<i32> = None;

    println!("Some value: {}", some_value.unwrap_or(0));
    println!("None value fallback: {}", none_value.unwrap_or(-1));

    // Using unwrap_or_else for dynamic fallback
    let dynamic_fallback = none_value.unwrap_or_else(|| {
        println!("Computing fallback value...");
        100
    });
    println!("Dynamic fallback: {}", dynamic_fallback);
}