#ifndef DIAMOND_h
#define DIAMOND_h
#include <iostream>
#include "boardGame_Classes.h"
using namespace std;

class diamond_board : public Board<char> {
private:
    char blank_symbol = '.';
    bool val_pos(int x, int y);
    int minimax(bool is_maximizing, char sym1, char sym2,int depth);
public:
    diamond_board();
    bool update_board(Move<char>* move) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_win(Player<char>* player) override;
    bool check_win(char sym);
    Move<char>* find_best_move(char sym1, char sym2);
};

class diamond_UI : public UI<char> {
public:
    diamond_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};
#endif