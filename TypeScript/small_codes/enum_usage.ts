import * as readline from "readline";

// String enum for better readability
enum Direction {
  Up = "UP",
  Down = "DOWN",
  Left = "LEFT",
  Right = "RIGHT",
}

// Player position
let position = { x: 0, y: 0 };

function move(dir: Direction) {
  switch (dir) {
    case Direction.Up:
      position.y++;
      break;
    case Direction.Down:
      position.y--;
      break;
    case Direction.Left:
      position.x--;
      break;
    case Direction.Right:
      position.x++;
      break;
  }
  console.log(`Moved ${dir}. Current position: (${position.x}, ${position.y})`);
}

// CLI for user input
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

console.log("=== Enum Navigation Demo ===");
console.log("Commands: up, down, left, right, exit");

function ask() {
  rl.question("Enter direction: ", (answer) => {
    const dir = answer.trim().toLowerCase();
    switch (dir) {
      case "up":
        move(Direction.Up);
        break;
      case "down":
        move(Direction.Down);
        break;
      case "left":
        move(Direction.Left);
        break;
      case "right":
        move(Direction.Right);
        break;
      case "exit":
        console.log("Exiting game.");
        rl.close();
        return;
      default:
        console.log("Invalid command!");
    }
    ask();
  });
}

ask();