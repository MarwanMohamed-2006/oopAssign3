/**
 * @file Tic_Tac_Toe.h
 * @brief 5x5 Tic-Tac-Toe game classes
 * @author
 * @date 2024
 *
 * Standard 5x5 Tic-Tac-Toe with 3 in a row to win
 */

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class TicTacToe_Board
 * @brief 5x5 Tic-Tac-Toe board
 */
class TicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Symbol for empty cells

public:
    /**
     * @brief Constructor
     */
    TicTacToe_Board();

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
     * @brief Count sequences for a player
     * @param player Pointer to the player
     * @return Number of 3-in-a-row sequences
     */
    int counting(Player<char>* player);

    /**
     * @brief Check if player has lost (not used)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_lose(Player<char>*);

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if board full, false otherwise
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if board full (25 moves), false otherwise
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Determine and display winner
     * @param player1 First player
     * @param player2 Second player
     */
    void winner(Player<char>* player1, Player<char>* player2);
};

/**
 * @class TicTacToe_UI
 * @brief UI class for 5x5 Tic-Tac-Toe
 */
class TicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    TicTacToe_UI() : UI<char>("Welcome to FCAI Tic-Tac-Toe Game", 3) {}

    /**
     * @brief Destructor
     */
    ~TicTacToe_UI() {};

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
    Move<char>* get_move(Player<char>* player);
};

#endif