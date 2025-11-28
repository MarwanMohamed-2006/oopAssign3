/**
 * @file Infinity_TicTacToe.h
 * @brief Defines the Infinity Tic-Tac-Toe game classes.
 */

#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <queue>
using namespace std;

/**
 * @class Infinity_Board
 * @brief Represents the 3x3 Infinity Tic-Tac-Toe game board.
 *
 * In this variant, after every 3 moves, the oldest mark on the board disappears.
 * The first player to align three marks in a row before any vanish wins.
 */
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
    queue<pair<int, int>> move_history; // Track order of moves (row, col)

public:
    /**
     * @brief Initializes a 3x3 Infinity Tic-Tac-Toe board.
     */
    Infinity_Board();

    /**
     * @brief Updates the board with a player's move and removes oldest move if needed.
     * @param move Pointer to a Move<char> object containing coordinates and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has three in a row, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks for a loss condition (not used in this game).
     */
    bool is_lose(Player<char>*) { return false; }

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player to evaluate.
     * @return true if no more valid moves exist and no one won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to the player.
     * @return true if someone won or it's a draw, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class Infinity_UI
 * @brief User Interface class for the Infinity Tic-Tac-Toe game.
 */
class Infinity_UI : public UI<char> {
public:
    /**
     * @brief Constructs an Infinity_UI object with the game welcome message.
     */
    Infinity_UI() : UI<char>("Welcome to FCAI Infinity Tic-Tac-Toe", 3) {
        cout << "\nGame Rules:\n";
        cout << "- Play on a 3x3 grid\n";
        cout << "- After every 3 moves, the OLDEST mark disappears!\n";
        cout << "- Win by getting 3 in a row before your marks vanish\n";
        cout << "- Strategy is key - timing matters!\n\n";
    }

    /**
     * @brief Destructor for Infinity_UI.
     */
    ~Infinity_UI() {}

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') for the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new Move<char> object.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // INFINITY_TICTACTOE_H