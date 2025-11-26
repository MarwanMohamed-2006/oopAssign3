#pragma once
#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include "BoardGame_Classes.h"
using namespace std;

class Pyramid_Board : public Board<char> {
public:
    Pyramid_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    bool valid_cell(int r, int c) const;
    const vector<pair<int, int>> directions = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1} };
};

#endif // PYRAMID_BOARD_H