// Enable experimentalDecorators in tsconfig.json first
// "experimentalDecorators": true

import * as readline from "readline";

// Method decorator
function log(target: any, propertyKey: string, descriptor: PropertyDescriptor) {
  const originalMethod = descriptor.value;
  descriptor.value = function (...args: any[]) {
    console.log(`Calling "${String(propertyKey)}" with arguments:`, args);
    const result = originalMethod.apply(this, args);
    console.log(`Result of "${String(propertyKey)}":`, result);
    return result;
  };
}

class Calculator {
  @log
  add(a: number, b: number): number {
    return a + b;
  }

  @log
  subtract(a: number, b: number): number {
    return a - b;
  }

  @log
  multiply(a: number, b: number): number {
    return a * b;
  }
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const calc = new Calculator();

console.log("=== Decorator Calculator ===");
rl.question("Choose operation (add/subtract/multiply): ", (op) => {
  rl.question("Enter first number: ", (num1) => {
    rl.question("Enter second number: ", (num2) => {
      const a = parseFloat(num1);
      const b = parseFloat(num2);

      if (op === "add") calc.add(a, b);
      else if (op === "subtract") calc.subtract(a, b);
      else if (op === "multiply") calc.multiply(a, b);
      else console.log("Invalid operation!");

      rl.close();
    });
  });
});