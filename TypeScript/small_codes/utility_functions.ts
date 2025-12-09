// Enhanced Utility Functions Demo - Strongly Typed and Fun

// Add two numbers
function sum(a: number, b: number): number {
  return a + b;
}

// Compute average of an array
function average(nums: number[]): number {
  return nums.reduce((a, b) => a + b, 0) / nums.length;
}

// Capitalize the first letter
function capitalize(str: string): string {
  return str.charAt(0).toUpperCase() + str.slice(1);
}

// Reverse a string
function reverseString(str: string): string {
  return str.split("").reverse().join("");
}

// Test data
const numbers: number[] = [3, 5, 7, 9];
const word: string = "typescript";

// Output
console.log("=== Utility Functions Showcase ===");
console.log(`Sum (3 + 4): ${sum(3, 4)}`);
console.log(`Average of [${numbers}]: ${average(numbers).toFixed(2)}`);
console.log(`Capitalized: ${capitalize(word)}`);
console.log(`Reversed: ${reverseString(word)}`);