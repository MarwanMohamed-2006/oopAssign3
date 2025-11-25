#include <iostream>
#include <iomanip>
#include <cctype>
#include "Tic_Tac_Toe.h"
using namespace std;

TicTacToe_Board::TicTacToe_Board() : Board(5, 5)
{
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}

bool TicTacToe_Board::update_board(Move<char>* move)
{
	int x = move->get_x();
	int y = move->get_y();
	char mark = move->get_symbol();


	if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
		(board[x][y] == blank_symbol || mark == 0)) {
		if (mark == 0) {
			n_moves--;
			board[x][y] = blank_symbol;
		}
		else {
			n_moves++;
			board[x][y] = toupper(mark);
		}
		return true;
	}

	return false;
}

bool TicTacToe_Board::is_win(Player<char>* player)
{
	return false;
}




bool TicTacToe_Board::is_lose(Player<char>*)
{
	return false;
}







bool TicTacToe_Board::is_draw(Player<char>* player)
{
	return false;
}



bool TicTacToe_Board::game_is_over(Player<char>* player)
{
	return false;
}



Player<char>* TicTacToe_UI::create_player(string& name, char symbol, PlayerType type)
{
	// Create player based on type
	cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
		<< " player: " << name << " (" << symbol << ")\n";

	return new Player<char>(name, symbol, type);

}

Move<char>* TicTacToe_UI::get_move(Player<char>* player)
{
	int x, y;

	if (player->get_type() == PlayerType::HUMAN) {
		cout << "\nPlease enter your move x and y : ";
		cin >> x >> y;
	}
	else if (player->get_type() == PlayerType::COMPUTER) {
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();
	}
	return new Move<char>(x, y, player->get_symbol());
}