#include <iostream>
using namespace std;

char board[3][3];
char currentPlayer = 'X';

// Initialize the board
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Print the board
void printBoard() {
    cout << "Current Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (board[i][j] == ' ' ? '.' : board[i][j]) << " ";
        }
        cout << endl;
    }
}

// Check if a player has won
char checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return board[0][i];
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return board[0][2];
    return ' '; // No winner
}

// Minimax algorithm to compute the best move
int minimax(bool isMaximizing) {
    char winner = checkWin();
    if (winner == 'X') return -1; // AI wins
    if (winner == 'O') return 1;  // Player wins

    bool movesLeft = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                movesLeft = true;
                break;
            }
        }
    }
    if (!movesLeft) return 0; // Draw

    int bestScore = isMaximizing ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isMaximizing ? 'O' : 'X';
                int score = minimax(!isMaximizing);
                board[i][j] = ' ';
                bestScore = isMaximizing ? max(bestScore, score) : min(bestScore, score);
            }
        }
    }
    return bestScore;
}

// AI makes the best move
void aiMove() {
    int bestScore = -1000, bestRow = -1, bestCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    board[bestRow][bestCol] = 'O';
}

// Main game loop
int main() {
    initializeBoard();
    while (true) {
        printBoard();
        if (checkWin() == 'O') {
            cout << "AI Wins!\n";
            break;
        }
        if (checkWin() == 'X') {
            cout << "You Win!\n";
            break;
        }

        int row, col;
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (board[row][col] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[row][col] = 'X';

        aiMove();

        bool movesLeft = false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    movesLeft = true;
                    break;
                }
            }
        }
        if (!movesLeft) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
