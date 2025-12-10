// Ownership and borrowing demo
fn takes_ownership(s: String) {
    println!("Took ownership: {}", s);
}

fn makes_copy(x: i32) {
    println!("Made a copy: {}", x);
}

fn gives_ownership() -> String {
    let s = String::from("I'm returned!");
    s
}

fn borrow_string(s: &String) {
    println!("Borrowed string: {}", s);
}

fn main() {
    // Ownership transfer
    let s1 = String::from("hello");
    takes_ownership(s1);
    // s1 is moved, cannot use here

    // Copy type
    let x = 42;
    makes_copy(x);
    println!("x is still accessible: {}", x);

    // Function returning ownership
    let s2 = gives_ownership();
    println!("Got ownership back: {}", s2);

    // Borrowing
    let s3 = String::from("Rust");
    borrow_string(&s3);
    println!("s3 is still usable after borrowing: {}", s3);

    // Mutable borrow
    let mut s4 = String::from("Hi");
    {
        let r = &mut s4;
        r.push_str(", there!");
        println!("Mutable borrow changed: {}", r);
    }
    println!("s4 after mutable borrow: {}", s4);
}