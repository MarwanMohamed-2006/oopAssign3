#ifndef NUMERICAL_TICTACTOE_CLASSES_H
#define NUMERICAL_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
using namespace std;



class Numerical_Board : public Board<int>
{

private:
    int blank_symbol = 0; ///< Value used to represent an empty cell on the board.
    set<int> player1_available; ///< Available odd numbers for Player 1: {1, 3, 5, 7, 9}
    set<int> player2_available; ///< Available even numbers for Player 2: {2, 4, 6, 8}

public:
    /**
     * @brief Default constructor that initializes a 3x3 Numerical board.
     */
    Numerical_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<int> object containing move coordinates and number.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a line summing to 15, false otherwise.
     */
    bool is_win(Player<int>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in this game logic).
     */
    bool is_lose(Player<int>*) { return false; }

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<int>* player);

    /**
     * @brief Get available numbers for a specific player.
     * @param symbol The player's symbol (1 for odd numbers, 2 for even numbers).
     * @return Set of available numbers.
     */
    set<int> get_available_numbers(int symbol) const;
};

class Numerical_UI : public UI<int>
{
public:
    /**
     * @brief Constructs a Numerical_UI object.
     *
     * Initializes the base `UI<int>` class with the welcome message.
     */
    Numerical_UI();

    /**
     * @brief Destructor for Numerical_UI.
     */
    ~Numerical_UI() {}

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Number identifier (1 for odd player, 2 for even player).
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<int> instance.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<int>` object representing the player's action.
     */
    virtual Move<int>* get_move(Player<int>* player);

    Player<int>** setup_players() override;
};

#endif