import * as readline from "readline";

class StorageBox<T> {
  private items: T[] = [];

  addItem(item: T): void {
    this.items.push(item);
  }

  getRandomItem(): T | undefined {
    if (this.items.length === 0) return undefined;
    const index = Math.floor(Math.random() * this.items.length);
    return this.items[index];
  }

  showAll(): void {
    console.log("Box contains:", this.items);
  }
}

// Readline setup
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

console.log("=== Generic Mystery Box ===");
console.log("You can store items of a specific type (number, string, or object)!");
console.log("Let's build your custom box...\n");

function askType() {
  rl.question("Choose box type (number/string/object): ", (type) => {
    type = type.trim().toLowerCase();

    if (type === "number") {
      const numBox = new StorageBox<number>();
      fillBox(numBox, type);
    } else if (type === "string") {
      const strBox = new StorageBox<string>();
      fillBox(strBox, type);
    } else if (type === "object") {
      const objBox = new StorageBox<{ name: string; level: number }>();
      fillBox(objBox, type);
    } else {
      console.log("Invalid type. Try again.");
      askType();
    }
  });
}

function fillBox<T>(box: StorageBox<T>, type: string) {
  rl.question(`Add an item to your ${type} box (type 'done' to finish): `, (input) => {
    if (input.trim().toLowerCase() === "done") {
      box.showAll();
      const random = box.getRandomItem();
      console.log("Random pick from your box:", random);
      console.log("See how generics keep your types consistent and safe!");
      rl.close();
      return;
    }

    let value: any;
    if (type === "number") {
      const num = Number(input);
      if (isNaN(num)) {
        console.log("Please enter a valid number.");
      } else {
        box.addItem(num as T);
      }
    } else if (type === "string") {
      box.addItem(input as T);
    } else if (type === "object") {
      const parts = input.split(",");
      if (parts.length !== 2) {
        console.log("Enter object as 'name,level' (e.g., Pikachu,5)");
      } else {
        const obj = { name: parts[0].trim(), level: Number(parts[1].trim()) };
        box.addItem(obj as T);
      }
    }

    fillBox(box, type);
  });
}

askType();