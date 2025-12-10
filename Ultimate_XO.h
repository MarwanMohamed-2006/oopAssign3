#ifndef ULTIMATE_XO_H
#define ULTIMATE_XO_H
#include "boardGame_Classes.h"

class Ultimate_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char small_board_winners[3][3];
    int next_board;

public:
    Ultimate_XO_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    char check_small_board_winner(int board_row, int board_col);
    bool check_main_board_win(char symbol);
    int get_next_board() const { return next_board; }
};

class Ultimate_XO_UI : public UI<char> {
public:
    Ultimate_XO_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif