#include <stdio.h>

#define SIZE 3

char board[SIZE][SIZE];

// Function prototypes
void initBoard();
void printBoard();
int makeMove(int player, int row, int col);
int checkWinner();
int isFull();

int main() {
    int player = 1, row, col, winner = 0;

    initBoard();

    while (1) {
        printBoard();
        printf("Player %d's turn. Enter row and column (0-2): ", player);
        scanf("%d %d", &row, &col);

        if (makeMove(player, row, col)) {
            winner = checkWinner();
            if (winner) {
                printBoard();
                printf("Player %d wins!\n", winner);
                break;
            } else if (isFull()) {
                printBoard();
                printf("It's a draw!\n");
                break;
            }
            player = (player == 1) ? 2 : 1; // switch player
        } else {
            printf("Invalid move, try again.\n");
        }
    }

    return 0;
}

// Initialize board
void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

// Print board
void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

// Make a move
int makeMove(int player, int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return 0;
    if (board[row][col] != ' ') return 0;
    board[row][col] = (player == 1) ? 'X' : 'O';
    return 1;
}

// Check winner
int checkWinner() {
    for (int i = 0; i < SIZE; i++) {
        // rows
        if (board[i][0] != ' ' && 
            board[i][0] == board[i][1] && 
            board[i][1] == board[i][2]) 
            return (board[i][0] == 'X') ? 1 : 2;

        // columns
        if (board[0][i] != ' ' && 
            board[0][i] == board[1][i] && 
            board[1][i] == board[2][i]) 
            return (board[0][i] == 'X') ? 1 : 2;
    }

    // diagonals
    if (board[0][0] != ' ' && 
        board[0][0] == board[1][1] && 
        board[1][1] == board[2][2]) 
        return (board[0][0] == 'X') ? 1 : 2;

    if (board[0][2] != ' ' && 
        board[0][2] == board[1][1] && 
        board[1][1] == board[2][0]) 
        return (board[0][2] == 'X') ? 1 : 2;

    return 0;
}

// Check if board is full
int isFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}
