#ifndef FOUR4_BOARD_H
#define FOUR4_BOARD_H

#include "BoardGame_Classes.h"
using namespace std;

class Four4_Board : public Board<char> {
public:
    Four4_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    bool in_bounds(int x, int y) const;
    bool has_legal_move_for_player(char s) const;
};

#endif // FOUR4_BOARD_H#pragma once
