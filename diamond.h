/**
 * @file diamond.h
 * @brief Diamond-shaped Tic-Tac-Toe game classes
 * @author
 * @date 2024
 */

#ifndef DIAMOND_h
#define DIAMOND_h

#include <iostream>
#include "boardGame_Classes.h"
using namespace std;

/**
 * @class diamond_board
 * @brief Board class for diamond-shaped Tic-Tac-Toe
 *
 * Implements a 7x7 board with diamond-shaped playable area
 * and AI functionality using minimax algorithm
 */
class diamond_board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol for empty cells

    /**
     * @brief Check if position is valid (within diamond shape)
     * @param x Row index
     * @param y Column index
     * @return true if position is valid, false otherwise
     */
    bool val_pos(int x, int y);

    /**
     * @brief Minimax algorithm for AI decision making
     * @param is_maximizing Whether current player is maximizing
     * @param sym1 Symbol of player 1
     * @param sym2 Symbol of player 2
     * @param depth Search depth
     * @return Score of the position
     */
    int minimax(bool is_maximizing, char sym1, char sym2, int depth);

public:
    /**
     * @brief Constructor
     */
    diamond_board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to the player
     * @return false (not used in this game variant)
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if game is draw, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game is over, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to the player
     * @return true if player won, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if symbol has winning pattern
     * @param sym Symbol to check
     * @return true if symbol has win, false otherwise
     */
    bool check_win(char sym);

    /**
     * @brief Find best move for AI player
     * @param sym1 Symbol of AI player
     * @param sym2 Symbol of opponent
     * @return Pointer to best move
     */
    Move<char>* find_best_move(char sym1, char sym2);
};

/**
 * @class diamond_UI
 * @brief UI class for diamond Tic-Tac-Toe
 */
class diamond_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    diamond_UI();

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