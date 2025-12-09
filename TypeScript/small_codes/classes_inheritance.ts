// interactive_animals.ts
import * as readline from 'readline';

class Animal {
    name: string;
    constructor(name: string) {
        this.name = name;
    }
    speak(): void {
        console.log(`${this.name} makes a sound.`);
    }
}

class Dog extends Animal {
    speak(): void {
        console.log(`${this.name} barks.`);
    }
}

class Cat extends Animal {
    speak(): void {
        console.log(`${this.name} meows.`);
    }
}

class Bird extends Animal {
    speak(): void {
        console.log(`${this.name} chirps.`);
    }
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function ask(question: string): Promise<string> {
    return new Promise(resolve => rl.question(question, resolve));
}

async function main() {
    console.log("=== Interactive Animal CLI ===");

    const type = (await ask("Choose animal type (dog/cat/bird): ")).toLowerCase();
    const name = await ask("Enter animal name: ");

    let animal: Animal;
    if (type === "dog") animal = new Dog(name);
    else if (type === "cat") animal = new Cat(name);
    else if (type === "bird") animal = new Bird(name);
    else animal = new Animal(name);

    console.log("\nAnimal speaks:");
    animal.speak();

    rl.close();
}

main();