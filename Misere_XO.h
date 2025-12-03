#ifndef Misere_XO_h
#define Misere_XO_h
#include "boardGame_Classes.h"
using namespace std;

class Misere_XO_Board : public Board<char> {
private:
	char blank_symbol = '.';
public:
	Misere_XO_Board();
	bool update_board(Move<char>* move) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;
	bool is_win(Player<char>* player) override;
	bool _3rows(char sym);
	Move<char>* find_best_move(char computer_symbol, char human_symbol);
	int minimax(bool is_maximizing, char sym1, char sym2);
};
class Misere_XO_UI : public UI<char> {
	public:
	Misere_XO_UI();
	Player<char>* create_player(string& name, char symbol, PlayerType type);
	virtual Move<char>* get_move(Player<char>* player);
};

#endif
