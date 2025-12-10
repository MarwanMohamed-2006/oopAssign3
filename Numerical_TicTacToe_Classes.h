/**
 * @file Numerical_TicTacToe_Classes.h
 * @brief Classes for Numerical Tic-Tac-Toe game
 * @author
 * @date 2024
 *
 * Player 1 uses odd numbers (1,3,5,7,9), Player 2 uses even numbers (2,4,6,8)
 * Win by getting 3 numbers in a row that sum to 15
 */

#ifndef NUMERICAL_TICTACTOE_CLASSES_H
#define NUMERICAL_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
using namespace std;

/**
 * @class Numerical_Board
 * @brief Board class for Numerical Tic-Tac-Toe
 */
class Numerical_Board : public Board<int>
{
private:
    int blank_symbol = 0;                 ///< Value representing empty cell
    set<int> player1_available;           ///< Available odd numbers for Player 1: {1, 3, 5, 7, 9}
    set<int> player2_available;           ///< Available even numbers for Player 2: {2, 4, 6, 8}

public:
    /**
     * @brief Constructor
     */
    Numerical_Board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Check if player has won
     * @param player Pointer to the player
     * @return true if player won (has 3 numbers summing to 15), false otherwise
     */
    bool is_win(Player<int>* player);

    /**
     * @brief Check if player has lost (not used in this game)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_lose(Player<int>*) { return false; }

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if board full with no winner, false otherwise
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game over (win or draw), false otherwise
     */
    bool game_is_over(Player<int>* player);

    /**
     * @brief Get available numbers for a player
     * @param symbol Player symbol (1 for odd, 2 for even)
     * @return Set of available numbers
     */
    set<int> get_available_numbers(int symbol) const;
};

/**
 * @class Numerical_UI
 * @brief UI class for Numerical Tic-Tac-Toe
 */
class Numerical_UI : public UI<int>
{
public:
    /**
     * @brief Constructor
     */
    Numerical_UI();

    /**
     * @brief Destructor
     */
    ~Numerical_UI() {}

    /**
     * @brief Create a player for the game
     * @param name Player name
     * @param symbol Player symbol (1 for odd, 2 for even)
     * @param type Player type
     * @return Pointer to created player
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Get a move from the player
     * @param player Pointer to the current player
     * @return Pointer to the move made
     */
    virtual Move<int>* get_move(Player<int>* player);

    /**
     * @brief Set up players for the game
     * @return Array of two player pointers
     */
    Player<int>** setup_players() override;
};

#endif