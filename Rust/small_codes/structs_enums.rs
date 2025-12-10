use std::io;

struct Point { x: i32, y: i32 }

#[derive(Debug)]
enum Direction { Up, Down, Left, Right }

impl Point {
    fn move_point(&mut self, dir: &Direction) {
        match dir {
            Direction::Up => self.y += 1,
            Direction::Down => self.y -= 1,
            Direction::Left => self.x -= 1,
            Direction::Right => self.x += 1,
        }
    }
}

fn main() {
    let mut p = Point { x: 0, y: 0 };
    println!("Start at: ({},{})", p.x, p.y);

    loop {
        println!("Enter direction (up/down/left/right) or 'exit': ");
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let input = input.trim().to_lowercase();

        if input == "exit" { break; }

        let dir = match input.as_str() {
            "up" => Direction::Up,
            "down" => Direction::Down,
            "left" => Direction::Left,
            "right" => Direction::Right,
            _ => {
                println!("Invalid input!");
                continue;
            }
        };

        p.move_point(&dir);
        println!("Moved {:?}, new position: ({},{})", dir, p.x, p.y);
    }

    println!("Final position: ({},{})", p.x, p.y);
}