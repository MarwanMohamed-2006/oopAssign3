#ifndef CONNECTFOUR_CLASSES_H
#define CONNECTFOUR_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

class ConnectFour_Board : public Board<char> {
private:
    char blank_symbol = '.';

    // Helper function to check if four marks in a row match the player's symbol
    bool check_line(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4, char symbol);

public:
    ConnectFour_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; }

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
};

class ConnectFour_UI : public UI<char> {
public:
    ConnectFour_UI();

    ~ConnectFour_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);
};

#endif
