/**
 * @file Pyramid_UI.h
 * @brief User Interface for Pyramid Tic-Tac-Toe game
 * @author
 * @date 2024
 */

#pragma once
#ifndef PYRAMID_UI_H
#define PYRAMID_UI_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Pyramid_UI
 * @brief UI class for Pyramid-shaped Tic-Tac-Toe
 */
class Pyramid_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    Pyramid_UI();

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

#endif // PYRAMID_UI_H