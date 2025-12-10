/**
 * @file Infinity_Board.h
 * @brief Infinity Tic-Tac-Toe game class
 * @author
 * @date 2024
 *
 * After every 3 moves, the oldest mark disappears from the board
 */

#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <deque>

 /**
  * @class InfinityTicTacToe
  * @brief Main game class for Infinity Tic-Tac-Toe
  *
  * Features:
  * - 3x3 board
  * - Oldest move removed after every 3 moves
  * - Computer opponent with AI
  * - Win detection and game state management
  */
class InfinityTicTacToe {
private:
    // Game state
    std::vector<std::vector<char>> board;      ///< 3x3 game board
    std::deque<std::pair<int, int>> moveHistory; ///< History of moves for removal
    char currentPlayer;        ///< Current player (X or O)
    int moveCount;             ///< Total moves made
    bool gameEnded;            ///< Whether game has ended
    char winner;               ///< Winner (X, O, or D for draw)
    bool isComputerOpponent;   ///< Whether playing against computer
    char computerSymbol;       ///< Symbol used by computer

    // Constants
    static const int GRID_SIZE = 3;           ///< Board size (3x3)
    static const int MOVES_BEFORE_REMOVAL = 3; ///< Moves before oldest is removed

    // AI helper methods
    std::pair<int, int> getComputerMove();      ///< Get computer's move
    std::pair<int, int> findWinningMove(char player); ///< Find winning move for player
    std::pair<int, int> findBestMove();         ///< Find best strategic move
    int evaluatePosition(int row, int col, char player); ///< Evaluate position value

public:
    // Constructor
    InfinityTicTacToe();

    // Game control
    void startGame(bool vsComputer = false); ///< Start new game
    bool makeMove(int row, int col);         ///< Make a move at position
    bool makeComputerMove();                 ///< Computer makes a move
    void processOldestMoveRemoval();         ///< Remove oldest move
    bool checkWin(int row, int col) const;   ///< Check if move caused win
    bool isBoardFull() const;                ///< Check if board is full
    void switchPlayer();                     ///< Switch to next player
    void resetGame();                        ///< Reset game state

    // Getters
    char getCurrentPlayer() const;           ///< Get current player
    char getCell(int row, int col) const;    ///< Get cell content
    bool isGameEnded() const;                ///< Check if game ended
    char getWinner() const;                  ///< Get winner
    int getMoveCount() const;                ///< Get move count
    bool isComputerTurn() const;             ///< Check if computer's turn

    // Display
    void displayBoard() const;               ///< Display board to console
    std::string getBoardString() const;      ///< Get board as string

    // Validation
    bool isValidMove(int row, int col) const; ///< Check if move is valid
    bool isPositionEmpty(int row, int col) const; ///< Check if position is empty
};

#endif // INFINITY_TICTACTOE_H