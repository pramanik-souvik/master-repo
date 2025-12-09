// Enhanced CLI Quiz App with Timer and Streaks
const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// Questions with categories
const questions = [
  { q: "Capital of France?", a: "Paris", category: "Geography" },
  { q: "5 + 7 = ?", a: "12", category: "Math" },
  { q: "Largest planet in our solar system?", a: "Jupiter", category: "Science" },
  { q: "Who wrote 'Hamlet'?", a: "Shakespeare", category: "Literature" },
  { q: "The boiling point of water in Celsius?", a: "100", category: "Science" },
  { q: "Square root of 81?", a: "9", category: "Math" },
  { q: "Capital of Japan?", a: "Tokyo", category: "Geography" },
  { q: "Who painted the Mona Lisa?", a: "Da Vinci", category: "Art" },
  { q: "5 * 6 = ?", a: "30", category: "Math" },
  { q: "Smallest prime number?", a: "2", category: "Math" },
  { q: "H2O is chemical formula for?", a: "Water", category: "Science" },
  { q: "Who discovered gravity?", a: "Newton", category: "Science" },
];

// Shuffle questions
function shuffle(array) {
  return array.sort(() => Math.random() - 0.5);
}

let score = 0;
let streak = 0;
let i = 0;
const shuffledQuestions = shuffle(questions);

function askQuestion() {
  if (i < shuffledQuestions.length) {
    const qObj = shuffledQuestions[i];
    console.log(`\nQuestion ${i + 1}/${shuffledQuestions.length} [${qObj.category}]`);

    let answered = false;
    const timer = setTimeout(() => {
      if (!answered) {
        console.log("\nTime's up! Moving to next question.");
        streak = 0;
        i++;
        askQuestion();
      }
    }, 15000); // 15-second timer

    rl.question(qObj.q + " ", answer => {
      answered = true;
      clearTimeout(timer);

      if (answer.trim().toLowerCase() === qObj.a.toLowerCase()) {
        streak++;
        score += 1 + Math.floor(streak / 3); // bonus: +1 point for every 3 correct in a row
        console.log("Correct! Current streak:", streak);
      } else {
        console.log(`Wrong! Correct answer: ${qObj.a}`);
        streak = 0;
      }

      i++;
      askQuestion();
    });

  } else {
    const percentage = Math.min(((score / shuffledQuestions.length) * 100).toFixed(1), 100);
    let grade;
    if (percentage >= 90) grade = "A+";
    else if (percentage >= 75) grade = "A";
    else if (percentage >= 50) grade = "B";
    else grade = "C";

    console.log("\nQuiz finished!");
    console.log("Final Score:", score);
    console.log("Percentage:", percentage + "%");
    console.log("Grade:", grade);
    rl.close();
  }
}

// Start the quiz
console.log("Welcome to the CLI Quiz App!");
console.log("You have 15 seconds per question. Streaks give bonus points.");
askQuestion();