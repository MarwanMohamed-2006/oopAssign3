#ifndef ULTIMATE_XO_H
#define ULTIMATE_XO_H
#include "boardGame_Classes.h"

class Ultimate_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    // مصفوفة لتتبع الفائز في كل لوحة صغيرة (9 لوحات)
    char small_board_winners[3][3] = {};
    // رقم اللوحة الصغيرة التالية المطلوب اللعب فيها (-1 = أي لوحة)
    int next_board;

public:
    Ultimate_XO_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // دالة للتحقق من الفوز في لوحة صغيرة
    char check_small_board_winner(int board_row, int board_col);
    // دالة للتحقق من الفوز في اللوحة الرئيسية
    bool check_main_board_win(char symbol);
    // الحصول على رقم اللوحة التالية
    int get_next_board() const { return next_board; }
};

class Ultimate_XO_UI : public UI<char> {
public:
    Ultimate_XO_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif