// Borrow checker demo with multiple borrows
fn append_exclamation(s: &mut String) {
    s.push_str("!");
}

fn main() {
    let mut greeting = String::from("Hello");

    // Mutable borrow to modify the string
    append_exclamation(&mut greeting);
    println!("After mutable borrow: {}", greeting);

    // Immutable borrows can coexist
    let first = &greeting;
    let second = &greeting;
    println!("Immutable borrows: '{}' and '{}'", first, second);
}