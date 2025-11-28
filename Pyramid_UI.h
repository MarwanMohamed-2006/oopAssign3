#pragma once
#ifndef PYRAMID_UI_H
#define PYRAMID_UI_H

#include "BoardGame_Classes.h"
using namespace std;

class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // PYRAMID_UI_H