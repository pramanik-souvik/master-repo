#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

const string FILE_NAME = "expenses.txt";

struct Expense {
    string description;
    double amount;
};

// Save all expenses back to file
void saveExpenses(const vector<Expense>& expenses) {
    ofstream fout(FILE_NAME, ios::trunc);
    for (auto& e : expenses) {
        fout << e.description << "," << e.amount << "\n";
    }
    fout.close();
}

// Load all expenses from file
vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream fin(FILE_NAME);
    string description;
    double amount;

    while (fin >> ws && getline(fin, description, ',')) {
        fin >> amount;
        expenses.push_back({description, amount});
    }
    fin.close();
    return expenses;
}

void addExpense() {
    string description;
    double amount;

    cout << "Enter description: ";
    cin.ignore();
    getline(cin, description);

    cout << "Enter amount: ";
    cin >> amount;

    ofstream fout(FILE_NAME, ios::app);
    fout << description << "," << amount << "\n";
    fout.close();

    cout << "Expense added successfully!\n";
}

void listExpenses() {
    auto expenses = loadExpenses();

    if (expenses.empty()) {
        cout << "No expenses found.\n";
        return;
    }

    cout << left << setw(5) << "#" << setw(20) << "Description" << setw(10) << "Amount" << "\n";
    cout << string(40, '-') << "\n";

    for (size_t i = 0; i < expenses.size(); i++) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << expenses[i].description
             << setw(10) << expenses[i].amount << "\n";
    }
}

void totalExpenses() {
    auto expenses = loadExpenses();

    double sum = 0;
    for (auto& e : expenses) sum += e.amount;

    cout << "Total Expenses: " << sum << "\n";
}

void deleteExpense() {
    auto expenses = loadExpenses();

    if (expenses.empty()) {
        cout << "No expenses to delete.\n";
        return;
    }

    listExpenses();
    cout << "Enter the expense number to delete: ";
    int index;
    cin >> index;

    if (index < 1 || index > (int)expenses.size()) {
        cout << "Invalid index!\n";
        return;
    }

    expenses.erase(expenses.begin() + (index - 1));
    saveExpenses(expenses);

    cout << "Expense deleted successfully!\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== Expense Tracker ===\n";
        cout << "1. Add Expense\n";
        cout << "2. List Expenses\n";
        cout << "3. Show Total\n";
        cout << "4. Delete Expense\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: listExpenses(); break;
            case 3: totalExpenses(); break;
            case 4: deleteExpense(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}