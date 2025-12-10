/**
 * @file Four4_Board.h
 * @brief Board class for 4x4 Tic-Tac-Toe with moving tokens
 * @author
 * @date 2024
 */

#ifndef FOUR4_BOARD_H
#define FOUR4_BOARD_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Four4_Board
 * @brief 4x4 Tic-Tac-Toe board where tokens can be moved
 *
 * Initial setup:
 * Row 0: X O X O
 * Row 3: O X O X
 * Other rows: empty
 * Players move their tokens to adjacent empty cells
 */
class Four4_Board : public Board<char> {
public:
    /**
     * @brief Constructor
     */
    Four4_Board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to the player
     * @return true if player has 3 in a row, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost (not used)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if no legal moves for either player, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game over (win or draw), false otherwise
     */
    bool game_is_over(Player<char>* player) override;

private:
    /**
     * @brief Check if coordinates are within bounds
     * @param x Row index
     * @param y Column index
     * @return true if within 0-3, false otherwise
     */
    bool in_bounds(int x, int y) const;

    /**
     * @brief Check if player has any legal moves
     * @param s Player symbol
     * @return true if player can move, false otherwise
     */
    bool has_legal_move_for_player(char s) const;
};

#endif // FOUR4_BOARD_H