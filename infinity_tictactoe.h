#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <deque>

class InfinityTicTacToe {
private:
    // Game state
    std::vector<std::vector<char>> board;
    std::deque<std::pair<int, int>> moveHistory;
    char currentPlayer;
    int moveCount;
    bool gameEnded;
    char winner;
    bool isComputerOpponent;
    char computerSymbol;

    // Constants
    static const int GRID_SIZE = 3;
    static const int MOVES_BEFORE_REMOVAL = 3;

    // AI helper methods
    std::pair<int, int> getComputerMove();
    std::pair<int, int> findWinningMove(char player);
    std::pair<int, int> findBestMove();
    int evaluatePosition(int row, int col, char player);

public:
    // Constructor
    InfinityTicTacToe();

    // Game control
    void startGame(bool vsComputer = false);
    bool makeMove(int row, int col);
    bool makeComputerMove();
    void processOldestMoveRemoval();
    bool checkWin(int row, int col) const;
    bool isBoardFull() const;
    void switchPlayer();
    void resetGame();

    // Getters
    char getCurrentPlayer() const;
    char getCell(int row, int col) const;
    bool isGameEnded() const;
    char getWinner() const;
    int getMoveCount() const;
    bool isComputerTurn() const;

    // Display
    void displayBoard() const;
    std::string getBoardString() const;

    // Validation
    bool isValidMove(int row, int col) const;
    bool isPositionEmpty(int row, int col) const;
};

#endif // INFINITY_TICTACTOE_H