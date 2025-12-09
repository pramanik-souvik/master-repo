// JSON Validator CLI
import * as fs from "fs";
import * as readline from "readline";

// Create a CLI interface
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Utility function to validate JSON
function validateJSON(jsonStr: string): { valid: boolean; error?: string } {
  try {
    JSON.parse(jsonStr);
    return { valid: true };
  } catch (err: any) {
    return { valid: false, error: err.message };
  }
}

// Option 1: Validate JSON from user input
function validateFromInput(): void {
  rl.question("Enter JSON string to validate:\n", (input) => {
    const result = validateJSON(input);
    if (result.valid) {
      console.log("\n The JSON is valid!");
    } else {
      console.error(`\n Invalid JSON: ${result.error}`);
    }
    rl.close();
  });
}

// Option 2: Validate JSON from file
function validateFromFile(filePath: string): void {
  if (!fs.existsSync(filePath)) {
    console.error(` File not found: ${filePath}`);
    rl.close();
    return;
  }

  const content = fs.readFileSync(filePath, "utf-8");
  const result = validateJSON(content);

  console.log(`\n Validating file: ${filePath}`);
  if (result.valid) {
    console.log(" File contains valid JSON.");
  } else {
    console.error(` Invalid JSON in file:\n${result.error}`);
  }
  rl.close();
}

// Main menu
function startApp(): void {
  console.log("\n=== JSON Validator CLI ===");
  console.log("1. Validate JSON from input");
  console.log("2. Validate JSON from file");
  console.log("3. Exit\n");

  rl.question("Choose an option (1-3): ", (choice) => {
    switch (choice.trim()) {
      case "1":
        validateFromInput();
        break;
      case "2":
        rl.question("\nEnter file path: ", (filePath) => {
          validateFromFile(filePath.trim());
        });
        break;
      case "3":
        console.log("Goodbye!");
        rl.close();
        break;
      default:
        console.log("Invalid choice. Please select 1–3.");
        rl.close();
    }
  });
}

startApp();