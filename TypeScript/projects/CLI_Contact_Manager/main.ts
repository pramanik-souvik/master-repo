// contact_manager.ts
// A full-featured CLI Contact Manager using TypeScript and File I/O

import * as readline from "readline";
import * as fs from "fs";

interface Contact {
  id: number;
  name: string;
  phone: string;
  email?: string;
}

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const contactsFile = "contacts.json";

// Load contacts from file
function loadContacts(): Contact[] {
  if (fs.existsSync(contactsFile)) {
    const data = fs.readFileSync(contactsFile, "utf-8");
    return JSON.parse(data);
  }
  return [];
}

// Save contacts to file
function saveContacts(contacts: Contact[]): void {
  fs.writeFileSync(contactsFile, JSON.stringify(contacts, null, 2));
}

// Add a new contact
function addContact(name: string, phone: string, email?: string): void {
  const contacts = loadContacts();
  const newContact: Contact = {
    id: Date.now(),
    name,
    phone,
    email,
  };
  contacts.push(newContact);
  saveContacts(contacts);
  console.log("\n Contact added successfully!\n");
  showMenu();
}

// List all contacts
function listContacts(): void {
  const contacts = loadContacts();
  if (contacts.length === 0) {
    console.log("\nNo contacts found.\n");
  } else {
    console.log("\n Contact List:");
    contacts.forEach((c, i) => {
      console.log(`${i + 1}. ${c.name} | ${c.phone} | ${c.email ?? "No email"}`);
    });
    console.log("");
  }
  showMenu();
}

// Search contact by name
function searchContact(name: string): void {
  const contacts = loadContacts();
  const results = contacts.filter((c) =>
    c.name.toLowerCase().includes(name.toLowerCase())
  );
  if (results.length === 0) {
    console.log("\nNo matching contacts found.\n");
  } else {
    console.log("\n Search Results:");
    results.forEach((c) =>
      console.log(`${c.name} | ${c.phone} | ${c.email ?? "No email"}`)
    );
    console.log("");
  }
  showMenu();
}

// Delete contact by name
function deleteContact(name: string): void {
  const contacts = loadContacts();
  const filtered = contacts.filter(
    (c) => c.name.toLowerCase() !== name.toLowerCase()
  );
  if (filtered.length === contacts.length) {
    console.log("\nNo contact found with that name.\n");
  } else {
    saveContacts(filtered);
    console.log("\n Contact deleted successfully.\n");
  }
  showMenu();
}

// CLI Menu
function showMenu(): void {
  console.log("=== CLI Contact Manager ===");
  console.log("1. Add Contact");
  console.log("2. View Contacts");
  console.log("3. Search Contact");
  console.log("4. Delete Contact");
  console.log("5. Exit");

  rl.question("\nChoose an option: ", (option) => {
    switch (option.trim()) {
      case "1":
        rl.question("Enter name: ", (name) => {
          rl.question("Enter phone: ", (phone) => {
            rl.question("Enter email (optional): ", (email) => {
              addContact(name, phone, email || undefined);
            });
          });
        });
        break;
      case "2":
        listContacts();
        break;
      case "3":
        rl.question("Enter name to search: ", (name) => searchContact(name));
        break;
      case "4":
        rl.question("Enter name to delete: ", (name) => deleteContact(name));
        break;
      case "5":
        console.log("Exiting... Goodbye!");
        rl.close();
        break;
      default:
        console.log("\nInvalid choice. Try again.\n");
        showMenu();
    }
  });
}

// Start program
showMenu();