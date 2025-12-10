/**
 * @file XO_Classes.h
 * @brief Memory Tic-Tac-Toe game classes
 * @author
 * @date 2024
 *
 * Players place symbols and need to remember positions
 */

#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class X_O_Board
 * @brief Memory Tic-Tac-Toe board
 */
class X_O_Board : public Board<char> {
private:
    char blank_symbol = '.';      ///< Symbol for empty cells
    vector<vector<char>> rb;      ///< Reference board for memory game

public:
    /**
     * @brief Constructor
     */
    X_O_Board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Check if player has won
     * @param player Pointer to the player
     * @return true if player has 3 in a row, false otherwise
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Check if player has lost (not used)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if board full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game over (win or draw), false otherwise
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class XO_UI
 * @brief UI class for Memory Tic-Tac-Toe
 */
class XO_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    XO_UI();

    /**
     * @brief Destructor
     */
    ~XO_UI() {};

    /**
     * @brief Create a player for the game
     * @param name Player name
     * @param symbol Player symbol
     * @param type Player type
     * @return Pointer to created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Get a move from the player
     * @param player Pointer to the current player
     * @return Pointer to the move made
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif