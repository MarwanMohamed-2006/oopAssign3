/**
 * @file SUS.h
 * @brief Defines the SUS game specific classes.
 */

#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
#include <map>
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the 3x3 SUS game board.
 *
 * The game objective is to form the sequence "S-U-S".
 * Both players can place either 'S' or 'U' on their turn.
 * A player scores 1 point for each S-U-S sequence they complete.
 * The winner is the player with the most points when the board is full.
 */
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';
    map<char, int> player_scores; // Track scores for 'X' and 'O'
    int count_sus_sequences();

public:
    /**
     * @brief Initializes a 3x3 SUS board.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing coordinates and letter ('S' or 'U').
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won.
     * @param player Pointer to the player being checked.
     * @return true if game is over and this player has more points, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks for a loss condition.
     */
    bool is_lose(Player<char>*) { return false; }

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player to evaluate.
     * @return true if the board is full and scores are tied, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to the player.
     * @return true if the board is full (9 moves), false otherwise.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Get the current scores for both players.
     * @return Map with player symbols as keys and scores as values.
     */
    map<char, int> get_scores() const;
};

/**
 * @class SUS_UI
 * @brief User Interface class for the SUS game.
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructs a SUS_UI object with the game welcome message.
     */
    SUS_UI() : UI<char>("Welcome to FCAI SUS Game (S-U-S Sequences)", 3) {
        cout << "\nGame Rules:\n";
        cout << "- Players X and O take turns placing either 'S' or 'U'\n";
        cout << "- Score 1 point for each S-U-S sequence you complete\n";
        cout << "- Sequences can be horizontal, vertical, or diagonal\n";
        cout << "- Player with most points when board is full wins!\n\n";
    }

    /**
     * @brief Destructor for SUS_UI.
     */
    ~SUS_UI() {}

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') for turn tracking.
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

#endif // SUS_CLASSES_H