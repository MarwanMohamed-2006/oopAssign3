#ifndef NUMERICAL_TICTACTOE_CLASSES_H
#define NUMERICAL_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
using namespace std;



class Numerical_Board : public Board<int>
{

private:
    int blank_symbol = 0; ///< Value used to represent an empty cell on the board.
    set<int> player1_available; ///< Available odd numbers for Player 1: {1, 3, 5, 7, 9}
    set<int> player2_available; ///< Available even numbers for Player 2: {2, 4, 6, 8}

public:

    Numerical_Board();
    bool update_board(Move<int>* move);
    bool is_win(Player<int>* player);
    bool is_lose(Player<int>*) { return false; }
    bool is_draw(Player<int>* player);
    bool game_is_over(Player<int>* player);
    set<int> get_available_numbers(int symbol) const;
};

class Numerical_UI : public UI<int>
{
public:
    Numerical_UI();
    ~Numerical_UI() {}
    Player<int>* create_player(string& name, int symbol, PlayerType type);
    virtual Move<int>* get_move(Player<int>* player);

    Player<int>** setup_players() override;
};

#endif