import * as readline from "readline";

// Custom error class
class DivisionError extends Error {
  constructor(message: string) {
    super(message);
    this.name = "DivisionError";
  }
}

function divide(a: number, b: number): number {
  if (b === 0) {
    throw new DivisionError("Cannot divide by zero!");
  }
  return a / b;
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

console.log("=== Division Calculator ===");

function ask() {
  rl.question("Enter two numbers (a b): ", (input) => {
    if (input.trim().toLowerCase() === "exit") {
      console.log("Exiting calculator.");
      rl.close();
      return;
    }

    const parts = input.split(" ").map(Number);
    if (parts.length !== 2 || parts.some(isNaN)) {
      console.log("Invalid input. Example: 10 2");
      return ask();
    }

    const [a, b] = parts;

    try {
      const result = divide(a, b);
      console.log(`Result: ${a} / ${b} = ${result}`);
    } catch (e) {
      if (e instanceof DivisionError) {
        console.error("Custom Error:", e.message);
      } else {
        console.error("Unexpected Error:", (e as Error).message);
      }
    } finally {
      console.log("Calculation attempt completed.\n");
    }

    ask();
  });
}

ask();