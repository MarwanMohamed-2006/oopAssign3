

#ifndef INFINITY_TICTACTOE_H
#define INFINITY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <queue>
using namespace std;


class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
    queue<pair<int, int>> move_history; 

public:
   
    Infinity_Board();

   
    bool update_board(Move<char>* move);

   
    bool is_win(Player<char>* player);

   
    bool is_lose(Player<char>*) { return false; }

   
    bool is_draw(Player<char>* player);

    
    bool game_is_over(Player<char>* player);
};


class Infinity_UI : public UI<char> {
public:
    
    Infinity_UI() : UI<char>("Welcome to FCAI Infinity Tic-Tac-Toe", 3) {
        cout << "\nGame Rules:\n";
        cout << "- Play on a 3x3 grid\n";
        cout << "- After every 3 moves, the OLDEST mark disappears!\n";
        cout << "- Win by getting 3 in a row before your marks vanish\n";
        cout << "- Strategy is key - timing matters!\n\n";
    }

   
    ~Infinity_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type);

  
    virtual Move<char>* get_move(Player<char>* player);
};

#endif