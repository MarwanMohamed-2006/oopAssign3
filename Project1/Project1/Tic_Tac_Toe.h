#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;


class TicTacToe_Board : public Board<char> {
private:
	char blank_symbol = '.';
public:
	TicTacToe_Board();
	bool update_board(Move<char>* move);
	bool is_win(Player<char>* player);
	int counting(Player<char>* player);
	bool is_lose(Player<char>*);
	bool is_draw(Player<char>* player);
	bool game_is_over(Player<char>* player);
	void winner(Player<char>* player1, Player<char>* player2);


};

class TicTacToe_UI : public UI<char> {
public:
	TicTacToe_UI() : UI<char>("Welcome to FCAI Tic-Tac-Toe Game", 3) {}
	~TicTacToe_UI() {};
	Player<char>* create_player(string& name, char symbol, PlayerType type);
	Move<char>* get_move(Player<char>* player);

};
#endif

