// async_cli_game.ts
import * as readline from 'readline';

// Utility delay function
function delay(ms: number): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// Progress bar helper
function progressBar(step: number, total: number): string {
    const filled = Math.round((step / total) * 20);
    const empty = 20 - filled;
    return `[${'='.repeat(filled)}${' '.repeat(empty)}] ${Math.round((step/total)*100)}%`;
}

// Readline interface
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// Ask question
function askQuestion(query: string): Promise<string> {
    return new Promise(resolve => rl.question(query, resolve));
}

// Main async CLI game
async function runGame(): Promise<void> {
    console.log("\n=== Async CLI Game ===\n");

    await delay(500);
    console.log("Step 1: Welcome! Let's start the game...");

    await delay(500);
    const name = await askQuestion("Enter your name: ");
    console.log(`Hello, ${name}! Get ready for some tasks.\n`);

    await delay(500);
    console.log("Step 2: Simulated async tasks starting...\n");

    const totalTasks = 5;
    let streak = 0;

    for (let i = 1; i <= totalTasks; i++) {
        await delay(700);
        streak++;
        console.log(`Task ${i} completed ${progressBar(i, totalTasks)} Streak: ${streak}`);
    }

    console.log("\nStep 3: Quick quiz for bonus points!");

    let score = 0;
    const questions = [
        { q: "Capital of France?", a: "Paris" },
        { q: "5 + 7 = ?", a: "12" },
        { q: "JS: typeof null?", a: "object" }
    ];

    for (const {q,a} of questions) {
        const start = Date.now();
        const ans = await askQuestion(q + " ");
        const end = Date.now();
        const timeTaken = (end - start) / 1000;

        if (ans.trim().toLowerCase() === a.toLowerCase()) {
            let bonus = timeTaken < 5 ? 1 : 0; // bonus for quick answer
            score += 1 + bonus;
            console.log(`Correct! ${bonus ? "(Quick bonus!)" : ""}`);
        } else {
            console.log(`Wrong! Correct answer: ${a}`);
        }
    }

    console.log(`\nGame Finished! Your final score: ${score}`);
    rl.close();
}

// Run the game
runGame();