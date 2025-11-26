#ifndef Misere_XO_h
#define Misere_XO_h
#include "boardGame_Classes.h"
using namespace std;

class Misere_XO_Board : public Board<char> {
private:
	char blank_symbol = '.';
public:
	Misere_XO_Board();
	bool update_board(Move<char>* move);
	bool is_lose(Player<char>* player);
	bool is_draw(Player<char>* player);
	bool game_is_over(Player<char>* player);
	bool three_in_a_row(char sym);
	bool is_win(Player<char>* player);
};
class Misere_XO_UI : public UI<char> {
public:
	Misere_XO_UI();
	Player<char>* create_player(string& name, char symbol, PlayerType type);
	virtual Move<char>* get_move(Player<char>* player);
};

#endif
