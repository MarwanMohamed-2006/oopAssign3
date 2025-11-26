#ifndef FOUR4_UI_H
#define FOUR4_UI_H

#include "BoardGame_Classes.h"
using namespace std;

class Four4_UI : public UI<char> {
public:
    Four4_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FOUR4_UI_H#pragma once

