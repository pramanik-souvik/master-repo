#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const string FILE_NAME = "library.txt";

struct Book {
    int id;
    string title;
    string author;
    bool issued; // true if borrowed
};

// Load all books from file
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream fin(FILE_NAME);
    if (!fin) return books; // empty if file doesn't exist

    Book b;
    while (fin >> b.id) {
        fin.ignore();
        getline(fin, b.title, ',');
        getline(fin, b.author, ',');
        fin >> b.issued;
        books.push_back(b);
    }
    fin.close();
    return books;
}

// Save all books to file
void saveBooks(const vector<Book>& books) {
    ofstream fout(FILE_NAME, ios::trunc);
    for (auto& b : books) {
        fout << b.id << " " << b.title << "," << b.author << "," << b.issued << "\n";
    }
    fout.close();
}

void addBook() {
    auto books = loadBooks();
    Book b;

    cout << "Enter Book ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    b.issued = false;

    books.push_back(b);
    saveBooks(books);

    cout << "Book added successfully!\n";
}

void viewBooks() {
    auto books = loadBooks();
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    cout << left << setw(5) << "ID"
         << setw(25) << "Title"
         << setw(20) << "Author"
         << setw(10) << "Status" << "\n";
    cout << string(60, '-') << "\n";

    for (auto& b : books) {
        cout << left << setw(5) << b.id
             << setw(25) << b.title
             << setw(20) << b.author
             << setw(10) << (b.issued ? "Issued" : "Available") << "\n";
    }
}

void searchBook() {
    auto books = loadBooks();
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "Search by (1) ID or (2) Title: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;
        for (auto& b : books) {
            if (b.id == id) {
                cout << "Found: " << b.title << " by " << b.author
                     << " [" << (b.issued ? "Issued" : "Available") << "]\n";
                return;
            }
        }
    } else if (choice == 2) {
        cin.ignore();
        string title;
        cout << "Enter Title: ";
        getline(cin, title);
        for (auto& b : books) {
            if (b.title == title) {
                cout << "Found: " << b.title << " by " << b.author
                     << " [" << (b.issued ? "Issued" : "Available") << "]\n";
                return;
            }
        }
    }
    cout << "Book not found.\n";
}

void borrowBook() {
    auto books = loadBooks();
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    int id;
    cout << "Enter Book ID to borrow: ";
    cin >> id;

    for (auto& b : books) {
        if (b.id == id) {
            if (b.issued) {
                cout << "Book already issued!\n";
            } else {
                b.issued = true;
                saveBooks(books);
                cout << "Book borrowed successfully!\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void returnBook() {
    auto books = loadBooks();
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (auto& b : books) {
        if (b.id == id) {
            if (!b.issued) {
                cout << "Book was not issued.\n";
            } else {
                b.issued = false;
                saveBooks(books);
                cout << "Book returned successfully!\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void deleteBook() {
    auto books = loadBooks();
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            books.erase(books.begin() + i);
            saveBooks(books);
            cout << "Book deleted successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: borrowBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}