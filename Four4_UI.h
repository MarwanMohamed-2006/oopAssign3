/**
 * @file Four4_UI.h
 * @brief User Interface for 4x4 Tic-Tac-Toe game
 * @author
 * @date 2024
 */

#ifndef FOUR4_UI_H
#define FOUR4_UI_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Four4_UI
 * @brief UI class for 4x4 Tic-Tac-Toe game
 *
 * Handles player creation and move input for the 4x4 Tic-Tac-Toe variant
 * where players move tokens instead of placing new ones
 */
class Four4_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    Four4_UI();

    /**
     * @brief Create a player for the game
     * @param name Player name
     * @param symbol Player symbol (X or O)
     * @param type Player type (HUMAN or COMPUTER)
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

#endif // FOUR4_UI_H