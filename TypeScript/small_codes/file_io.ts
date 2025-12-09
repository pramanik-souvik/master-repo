import * as fs from "fs";
import * as readline from "readline";

// Step 1: Write a secret word into file (only once)
if (!fs.existsSync("secret.txt")) {
  fs.writeFileSync("secret.txt", "typescript");
}

// Read secret word
const secret = fs.readFileSync("secret.txt", "utf-8").trim().toLowerCase();
let progress = "_".repeat(secret.length);
let attempts = 6;
let wrongGuesses: string[] = [];

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

console.log("=== Word Guessing Game ===");
console.log(`Word: ${progress}  (length: ${secret.length})`);

function ask() {
  if (attempts === 0) {
    console.log("Game Over! The word was:", secret);
    fs.appendFileSync("results.txt", `Lost! Word: ${secret}\n`);
    rl.close();
    return;
  }
  if (progress === secret) {
    console.log("You guessed it! The word was:", secret);
    fs.appendFileSync("results.txt", `Won! Word: ${secret}\n`);
    rl.close();
    return;
  }

  rl.question("Guess a letter: ", (input) => {
    const letter = input.trim().toLowerCase();
    if (!letter.match(/^[a-z]$/)) {
      console.log("Please enter a single letter (a-z).");
      return ask();
    }

    if (secret.includes(letter)) {
      let newProgress = "";
      for (let i = 0; i < secret.length; i++) {
        newProgress += secret[i] === letter ? letter : progress[i];
      }
      progress = newProgress;
      console.log("Good guess!");
    } else {
      attempts--;
      wrongGuesses.push(letter);
      console.log(`Wrong! Attempts left: ${attempts}`);
    }

    console.log(`Word: ${progress}`);
    console.log(`Wrong guesses: ${wrongGuesses.join(", ") || "None"}`);

    ask();
  });
}

ask();