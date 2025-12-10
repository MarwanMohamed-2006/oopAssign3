/**
 * @file Pyramid_Board.h
 * @brief Board class for Pyramid Tic-Tac-Toe
 * @author
 * @date 2024
 */

#pragma once
#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Pyramid_Board
 * @brief Board class for pyramid-shaped Tic-Tac-Toe
 *
 * Board layout:
 * Row 0: "  .  "
 * Row 1: " ... "
 * Row 2: "....."
 */
class Pyramid_Board : public Board<char> {
public:
    /**
     * @brief Constructor
     */
    Pyramid_Board();

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
     * @return true if board full with no winner, false otherwise
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
     * @brief Check if cell is valid (not space)
     * @param r Row index
     * @param c Column index
     * @return true if cell is playable, false if space
     */
    bool valid_cell(int r, int c) const;

    const vector<pair<int, int>> directions = {
        {0,1}, {0,-1}, {1,0}, {-1,0},  // Horizontal and vertical
        {1,1}, {-1,-1}, {1,-1}, {-1,1} // Diagonal directions
    }; ///< Directions to check for 3 in a row
};

#endif // PYRAMID_BOARD_H