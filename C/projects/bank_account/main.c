#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTIONS 100

// Transaction structure
typedef struct {
    char type[20];
    double amount;
    double balanceAfter;
} Transaction;

// Account structure
typedef struct {
    int accountNumber;
    char holderName[50];
    double balance;
    Transaction history[MAX_TRANSACTIONS];
    int transactionCount;
} Account;

// Function prototypes
void createAccount(Account *acc);
void deposit(Account *acc, double amount);
void withdraw(Account *acc, double amount);
void showBalance(Account *acc);
void showHistory(Account *acc);

int main() {
    Account acc;
    int choice;
    double amount;

    createAccount(&acc);

    while (1) {
        printf("\n===== Bank Account System =====\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Show Balance\n");
        printf("4. Transaction History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter amount to deposit: ");
                scanf("%lf", &amount);
                deposit(&acc, amount);
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%lf", &amount);
                withdraw(&acc, amount);
                break;
            case 3:
                showBalance(&acc);
                break;
            case 4:
                showHistory(&acc);
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Create account
void createAccount(Account *acc) {
    acc->transactionCount = 0;
    acc->balance = 0.0;

    printf("Enter account number: ");
    scanf("%d", &acc->accountNumber);
    getchar(); // consume newline

    printf("Enter account holder name: ");
    fgets(acc->holderName, sizeof(acc->holderName), stdin);
    acc->holderName[strcspn(acc->holderName, "\n")] = '\0'; // remove newline

    printf("Account created successfully!\n");
}

// Deposit
void deposit(Account *acc, double amount) {
    if (amount <= 0) {
        printf("Deposit amount must be positive.\n");
        return;
    }
    acc->balance += amount;

    // record transaction
    if (acc->transactionCount < MAX_TRANSACTIONS) {
        strcpy(acc->history[acc->transactionCount].type, "Deposit");
        acc->history[acc->transactionCount].amount = amount;
        acc->history[acc->transactionCount].balanceAfter = acc->balance;
        acc->transactionCount++;
    }

    printf("Deposited %.2f successfully.\n", amount);
}

// Withdraw
void withdraw(Account *acc, double amount) {
    if (amount <= 0) {
        printf("Withdrawal amount must be positive.\n");
        return;
    }
    if (amount > acc->balance) {
        printf("Insufficient funds.\n");
        return;
    }
    acc->balance -= amount;

    // record transaction
    if (acc->transactionCount < MAX_TRANSACTIONS) {
        strcpy(acc->history[acc->transactionCount].type, "Withdraw");
        acc->history[acc->transactionCount].amount = amount;
        acc->history[acc->transactionCount].balanceAfter = acc->balance;
        acc->transactionCount++;
    }

    printf("Withdrew %.2f successfully.\n", amount);
}

// Show balance
void showBalance(Account *acc) {
    printf("Account Number: %d\n", acc->accountNumber);
    printf("Holder Name: %s\n", acc->holderName);
    printf("Current Balance: %.2f\n", acc->balance);
}

// Show transaction history
void showHistory(Account *acc) {
    printf("\nTransaction History:\n");
    if (acc->transactionCount == 0) {
        printf("No transactions yet.\n");
        return;
    }
    for (int i = 0; i < acc->transactionCount; i++) {
        printf("%d. %s of %.2f | Balance after: %.2f\n", 
               i + 1, 
               acc->history[i].type, 
               acc->history[i].amount, 
               acc->history[i].balanceAfter);
    }
}