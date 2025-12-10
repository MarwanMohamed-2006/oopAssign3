/**
 * @file Ultimate_XO.h
 * @brief Ultimate Tic-Tac-Toe game classes
 * @author
 * @date 2024
 *
 * 9x9 board divided into 9 smaller 3x3 boards
 * Win 3 small boards in a row to win the main board
 */

#ifndef ULTIMATE_XO_H
#define ULTIMATE_XO_H

#include "boardGame_Classes.h"

 /**
  * @class Ultimate_XO_Board
  * @brief Board class for Ultimate Tic-Tac-Toe
  */
class Ultimate_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';          ///< Symbol for empty cells
    char small_board_winners[3][3];   ///< Winners of each small board
    int next_board;                   ///< Next board player must play in

public:
    /**
     * @brief Constructor
     */
    Ultimate_XO_Board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won the main board
     * @param player Pointer to the player
     * @return true if player won, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost (not used)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if all small boards filled with no main winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game over (win or draw), false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Check winner of a small board
     * @param board_row Small board row (0-2)
     * @param board_col Small board column (0-2)
     * @return Winner symbol or blank_symbol if no winner
     */
    char check_small_board_winner(int board_row, int board_col);

    /**
     * @brief Check if symbol has won the main board
     * @param symbol Symbol to check
     * @return true if symbol has 3 small boards in a row, false otherwise
     */
    bool check_main_board_win(char symbol);

    /**
     * @brief Get the next board player must play in
     * @return Board number (0-8) or -1 if any board
     */
    int get_next_board() const { return next_board; }
};

/**
 * @class Ultimate_XO_UI
 * @brief UI class for Ultimate Tic-Tac-Toe
 */
class Ultimate_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    Ultimate_XO_UI();

    /**
     * @brief Create a player for the game
     * @param name Player name
     * @param symbol Player symbol
     * @param type Player type
     * @return Pointer to created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get a move from the player
     * @param player Pointer to the current player
     * @return Pointer to the move made
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif