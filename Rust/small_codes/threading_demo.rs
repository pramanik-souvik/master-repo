// Threading demo
use std::thread;
use std::time::Duration;
fn main() {
    let handle = thread::spawn(|| {
        for i in 1..5 {
            println!("spawned: {}", i);
            thread::sleep(Duration::from_millis(200));
        }
    });
    for i in 1..3 {
        println!("main: {}", i);
        thread::sleep(Duration::from_millis(300));
    }
    handle.join().unwrap();
}