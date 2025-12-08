#include "Infinity_Board..h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor
InfinityTicTacToe::InfinityTicTacToe() {
    resetGame();
}

// Initialize or reset the game
void InfinityTicTacToe::resetGame() {
    board = vector<vector<char>>(GRID_SIZE, vector<char>(GRID_SIZE, ' '));
    moveHistory.clear();
    currentPlayer = 'X';
    moveCount = 0;
    gameEnded = false;
    winner = ' ';
    isComputerOpponent = false;
    computerSymbol = 'O';
}

// Start a new game
void InfinityTicTacToe::startGame(bool vsComputer) {
    resetGame();
    isComputerOpponent = vsComputer;

    cout << "=== Infinity Tic-Tac-Toe ===" << endl;
    cout << "Rules: After every " << MOVES_BEFORE_REMOVAL << " moves, the oldest mark disappears!" << endl;

    if (isComputerOpponent) {
        cout << "You are X, Computer is O" << endl;
    }

    cout << "Player X starts. Good luck!" << endl << endl;
    displayBoard();
}

// Make a move at specified position
bool InfinityTicTacToe::makeMove(int row, int col) {
    if (gameEnded) {
        cout << "Game has ended. Start a new game!" << endl;
        return false;
    }

    if (!isValidMove(row, col)) {
        cout << "Invalid position! Please choose row and column between 0-2." << endl;
        return false;
    }

    if (!isPositionEmpty(row, col)) {
        cout << "Position already occupied!" << endl;
        return false;
    }

    // Make the move
    board[row][col] = currentPlayer;
    moveHistory.push_back({ row, col });
    moveCount++;

    cout << "Player " << currentPlayer << " placed at (" << row << ", " << col << ")" << endl;

    // Check for win immediately after the move
    if (checkWin(row, col)) {
        gameEnded = true;
        winner = currentPlayer;
        displayBoard();
        cout << "\n*** Player " << currentPlayer << " wins! ***" << endl;
        return true;
    }

    // Check if board is full (draw)
    if (isBoardFull()) {
        gameEnded = true;
        winner = 'D';
        displayBoard();
        cout << "\n*** It's a draw! ***" << endl;
        return true;
    }

    // Switch to next player BEFORE removing moves
    switchPlayer();

    // Remove oldest move after every 3 moves (starting from move 4)
    // This happens AFTER switching, so removal is fair to both players
    if (moveCount > MOVES_BEFORE_REMOVAL &&
        (moveCount - MOVES_BEFORE_REMOVAL) % MOVES_BEFORE_REMOVAL == 0) {
        processOldestMoveRemoval();
    }

    displayBoard();

    return true;
}

// Computer makes a move
bool InfinityTicTacToe::makeComputerMove() {
    if (!isComputerOpponent || currentPlayer != computerSymbol || gameEnded) {
        return false;
    }

    cout << "\nComputer is thinking..." << endl;

    pair<int, int> move = getComputerMove();
    return makeMove(move.first, move.second);
}

// AI: Get computer's move
pair<int, int> InfinityTicTacToe::getComputerMove() {
    // Strategy 1: Try to win
    pair<int, int> winMove = findWinningMove(computerSymbol);
    if (winMove.first != -1) {
        return winMove;
    }

    // Strategy 2: Block opponent's winning move
    char opponent = (computerSymbol == 'X') ? 'O' : 'X';
    pair<int, int> blockMove = findWinningMove(opponent);
    if (blockMove.first != -1) {
        return blockMove;
    }

    // Strategy 3: Find best strategic move
    return findBestMove();
}

// Find a winning move for the given player
pair<int, int> InfinityTicTacToe::findWinningMove(char player) {
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            if (board[r][c] == ' ') {
                // Try this move
                board[r][c] = player;
                bool wins = checkWin(r, c);
                board[r][c] = ' '; // Undo

                if (wins) {
                    return { r, c };
                }
            }
        }
    }
    return { -1, -1 }; // No winning move found
}

// Find the best strategic move
pair<int, int> InfinityTicTacToe::findBestMove() {
    int bestScore = -1000;
    pair<int, int> bestMove = { -1, -1 };

    // Priority positions: center > corners > edges
    vector<pair<int, int>> moveOrder = {
        {1, 1}, // Center
        {0, 0}, {0, 2}, {2, 0}, {2, 2}, // Corners
        {0, 1}, {1, 0}, {1, 2}, {2, 1}  // Edges
    };

    for (auto pos : moveOrder) {
        int r = pos.first;
        int c = pos.second;

        if (board[r][c] == ' ') {
            int score = evaluatePosition(r, c, computerSymbol);

            if (score > bestScore) {
                bestScore = score;
                bestMove = { r, c };
            }
        }
    }

    // If no strategic move found, pick first available
    if (bestMove.first == -1) {
        for (int r = 0; r < GRID_SIZE; r++) {
            for (int c = 0; c < GRID_SIZE; c++) {
                if (board[r][c] == ' ') {
                    return { r, c };
                }
            }
        }
    }

    return bestMove;
}

// Evaluate how good a position is
int InfinityTicTacToe::evaluatePosition(int row, int col, char player) {
    int score = 0;

    // Center is most valuable
    if (row == 1 && col == 1) score += 4;

    // Corners are next
    if ((row == 0 || row == 2) && (col == 0 || col == 2)) score += 3;

    // Count how many lines this position contributes to
    int lineCount = 0;

    // Check row potential
    int friendlyInRow = 0, emptyInRow = 0;
    for (int c = 0; c < GRID_SIZE; c++) {
        if (board[row][c] == player) friendlyInRow++;
        else if (board[row][c] == ' ') emptyInRow++;
    }
    if (emptyInRow > 0) score += friendlyInRow;

    // Check column potential
    int friendlyInCol = 0, emptyInCol = 0;
    for (int r = 0; r < GRID_SIZE; r++) {
        if (board[r][col] == player) friendlyInCol++;
        else if (board[r][col] == ' ') emptyInCol++;
    }
    if (emptyInCol > 0) score += friendlyInCol;

    // Check diagonals if applicable
    if (row == col) {
        int friendlyInDiag = 0, emptyInDiag = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (board[i][i] == player) friendlyInDiag++;
            else if (board[i][i] == ' ') emptyInDiag++;
        }
        if (emptyInDiag > 0) score += friendlyInDiag;
    }

    if (row + col == GRID_SIZE - 1) {
        int friendlyInAntiDiag = 0, emptyInAntiDiag = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (board[i][GRID_SIZE - 1 - i] == player) friendlyInAntiDiag++;
            else if (board[i][GRID_SIZE - 1 - i] == ' ') emptyInAntiDiag++;
        }
        if (emptyInAntiDiag > 0) score += friendlyInAntiDiag;
    }

    return score;
}

// Remove the oldest move from the board
void InfinityTicTacToe::processOldestMoveRemoval() {
    if (moveHistory.size() <= MOVES_BEFORE_REMOVAL) return;

    int removeIndex = moveHistory.size() - MOVES_BEFORE_REMOVAL - 1;

    auto oldestMove = moveHistory[removeIndex];
    int row = oldestMove.first;
    int col = oldestMove.second;

    cout << "\n>>> Oldest move at (" << row << ", " << col
        << ") removed! <<<" << endl;
    board[row][col] = ' ';
}

// Check if the last move resulted in a win
bool InfinityTicTacToe::checkWin(int row, int col) const {
    char player = board[row][col];
    if (player == ' ') return false;

    // Check row
    bool rowWin = true;
    for (int c = 0; c < GRID_SIZE; c++) {
        if (board[row][c] != player) {
            rowWin = false;
            break;
        }
    }
    if (rowWin) return true;

    // Check column
    bool colWin = true;
    for (int r = 0; r < GRID_SIZE; r++) {
        if (board[r][col] != player) {
            colWin = false;
            break;
        }
    }
    if (colWin) return true;

    // Check main diagonal
    if (row == col) {
        bool diag1Win = true;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (board[i][i] != player) {
                diag1Win = false;
                break;
            }
        }
        if (diag1Win) return true;
    }

    // Check anti-diagonal
    if (row + col == GRID_SIZE - 1) {
        bool diag2Win = true;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (board[i][GRID_SIZE - 1 - i] != player) {
                diag2Win = false;
                break;
            }
        }
        if (diag2Win) return true;
    }

    return false;
}

// Check if board is full
bool InfinityTicTacToe::isBoardFull() const {
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            if (board[r][c] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Switch to the next player
void InfinityTicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Display the current board state
void InfinityTicTacToe::displayBoard() const {
    cout << "\nCurrent Board (Moves: " << moveCount << "):" << endl;
    cout << "  0   1   2" << endl;

    for (int r = 0; r < GRID_SIZE; r++) {
        cout << r << " ";
        for (int c = 0; c < GRID_SIZE; c++) {
            cout << board[r][c];
            if (c < GRID_SIZE - 1) cout << " | ";
        }
        cout << endl;

        if (r < GRID_SIZE - 1) {
            cout << "  ---------" << endl;
        }
    }
    cout << endl;
}

// Get board as string for display
string InfinityTicTacToe::getBoardString() const {
    string result = "  0   1   2\n";

    for (int r = 0; r < GRID_SIZE; r++) {
        result += to_string(r) + " ";
        for (int c = 0; c < GRID_SIZE; c++) {
            result += board[r][c];
            if (c < GRID_SIZE - 1) result += " | ";
        }
        result += "\n";

        if (r < GRID_SIZE - 1) {
            result += "  ---------\n";
        }
    }

    return result;
}

// Validation functions
bool InfinityTicTacToe::isValidMove(int row, int col) const {
    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE;
}

bool InfinityTicTacToe::isPositionEmpty(int row, int col) const {
    return board[row][col] == ' ';
}

// Getter functions
char InfinityTicTacToe::getCurrentPlayer() const {
    return currentPlayer;
}

char InfinityTicTacToe::getCell(int row, int col) const {
    if (!isValidMove(row, col)) {
        throw out_of_range("Invalid board position");
    }
    return board[row][col];
}

bool InfinityTicTacToe::isGameEnded() const {
    return gameEnded;
}

char InfinityTicTacToe::getWinner() const {
    return winner;
}

int InfinityTicTacToe::getMoveCount() const {
    return moveCount;
}

bool InfinityTicTacToe::isComputerTurn() const {
    return isComputerOpponent && currentPlayer == computerSymbol;
}