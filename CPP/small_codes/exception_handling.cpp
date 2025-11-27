#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
using namespace std;

class BankAccount {
    string owner;
    double balance;
public:
    BankAccount(string name, double initial) : owner(name), balance(initial) {
        if (initial < 0){
            throw invalid_argument("Initial balance cannot be negative!");
        }
    }

    void deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Deposit must be positive!");
        balance += amount;
        cout << owner << " deposited $" << amount << " | Balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) throw invalid_argument("Withdrawal must be positive!");
        if (amount > balance) throw runtime_error("Insufficient funds!");
        balance -= amount;
        cout << owner << " withdrew $" << amount << " | Balance: $" << balance << endl;
    }

    double getBalance() const { return balance; }
    string getOwner() const { return owner; }
};

int main() {
    map<int, BankAccount> accounts;
    try {
        accounts.emplace(1, BankAccount("Alice", 500));
        accounts.emplace(2, BankAccount("Bob", 1000));

        int choice;
        cout << "Banking System\n1 = Deposit\n2 = Withdraw\n3 = Check Balance\nChoice: ";
        cin >> choice;

        int id;
        cout << "Enter account ID (1 = Alice, 2 = Bob): ";
        cin >> id;

        if (accounts.find(id) == accounts.end())
            throw out_of_range("Account not found!");

        BankAccount &acc = accounts.at(id);

        if (choice == 1) {
            double amt;
            cout << "Enter deposit amount: ";
            cin >> amt;
            acc.deposit(amt);
        }
        else if (choice == 2) {
            double amt;
            cout << "Enter withdrawal amount: ";
            cin >> amt;
            acc.withdraw(amt);
        }
        else if (choice == 3) {
            cout << acc.getOwner() << "'s Balance: $" << acc.getBalance() << endl;
        }
        else {
            throw logic_error("Invalid menu choice!");
        }
    }
    catch (const out_of_range &e) {
        cerr << "Account Error: " << e.what() << endl;
    }
    catch (const invalid_argument &e) {
        cerr << "Input Error: " << e.what() << endl;
    }
    catch (const runtime_error &e) {
        cerr << "Transaction Error: " << e.what() << endl;
    }
    catch (const exception &e) {
        cerr << "Unexpected Error: " << e.what() << endl;
    }

    cout << "Thank you for using our bank system. Program ends safely.\n";
    return 0;
}