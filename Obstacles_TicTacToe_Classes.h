/**
 * @file Obstacles_TicTacToe_Classes.h
 * @brief Obstacles Tic-Tac-Toe game classes
 * @author
 * @date 2024
 *
 * 6x6 board with random obstacles appearing after every 2 moves
 */

#ifndef OBSTACLES_TICTACTOE_CLASSES_H  
#define OBSTACLES_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * @class Obstacles_Board
 * @brief 6x6 board with obstacles
 */
class Obstacles_Board : public Board<char> {
private:
    vector<pair<int, int>> obstaclePositions; ///< Positions of obstacles

public:
    /**
     * @brief Constructor
     */
    Obstacles_Board();

    /**
     * @brief Destructor
     */
    ~Obstacles_Board() {}

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won
     * @param player Pointer to the player
     * @return true if player has 4 in a row, false otherwise
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

    /**
     * @brief Add random obstacles to the board
     */
    void add_random_obstacles();

    /**
     * @brief Check if position has obstacle
     * @param x Row index
     * @param y Column index
     * @return true if obstacle present, false otherwise
     */
    bool is_obstacle(int x, int y) const;

    /**
     * @brief Check if move is valid
     * @param x Row index
     * @param y Column index
     * @return true if move is valid, false otherwise
     */
    bool is_valid_move(int x, int y) const;

    /**
     * @brief Display board with obstacles marked as #
     */
    void display_with_obstacles() const;
};

/**
 * @class Obstacles_UI
 * @brief UI class for Obstacles Tic-Tac-Toe
 */
class Obstacles_UI : public UI<char> {
private:
    Obstacles_Board* obsBoard; ///< Pointer to obstacles board

public:
    /**
     * @brief Constructor
     */
    Obstacles_UI();

    /**
     * @brief Destructor
     */
    ~Obstacles_UI() {}

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

    /**
     * @brief Set the obstacles board pointer
     * @param board Pointer to obstacles board
     */
    void set_obstacles_board(Obstacles_Board* board) { obsBoard = board; }
};

#endif