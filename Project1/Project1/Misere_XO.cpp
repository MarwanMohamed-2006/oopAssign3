#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Misere_XO.h"
using namespace std;
//--------------------------------------- Misere_XO_Board Implementation
Misere_XO_Board::Misere_XO_Board() : Board<char>(3, 3) {
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}
bool Misere_XO_Board::update_board(Move<char>* move) {
	int x = move->get_x();
	int y = move->get_y();
	char mark = move->get_symbol();
	if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
		(board[x][y] == blank_symbol || mark == 0)) {
		if (mark == 0) { 
			n_moves--;
			board[x][y] = blank_symbol;
		}
		else {         // Apply move
			n_moves++;
			board[x][y] = toupper(mark);
		}
		return true;
	}
	return false;
}
bool Misere_XO_Board::three_in_a_row(char sym) {
	auto all_equal = [&](char a, char b, char c) {
		return a == b && b == c && a != blank_symbol;
	};
	for (int i = 0; i < rows; ++i) {
		if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
			(all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
			return true;
	}
	if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
		(all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
		return true;
	return false;
}

bool Misere_XO_Board::is_lose(Player<char>* player) {
	
	return three_in_a_row(player->get_symbol());
}
bool Misere_XO_Board::is_draw(Player<char>* player) {
	if (n_moves != 9)
		return false;

	return !three_in_a_row('X') && !three_in_a_row('O');
}
bool Misere_XO_Board::game_is_over(Player<char>* player) {
	return is_lose(player) || is_draw(player);
}
bool Misere_XO_Board::is_win(Player<char>* player) {
	return false;
}

//--------------------------------------- Misere_XO_UI Implementation

Misere_XO_UI::Misere_XO_UI() : UI<char>("Welcome to Fizz Misere Tic-Tac-Toe Game", 3)
{
	cout << "\n REVERSE RULES GAME! \n";
	cout << "========================\n";
	cout << "  WARNING: The rules are REVERSED!";
	cout << "- You lose if you make three in a row!\n";
	cout << "- Your goal is to AVOID making three in a row\n";
	cout << "- Think carefully before each move\n";
	cout << "- The last player to avoid making three in a row wins!\n";
	cout << "========================\n";
}
Player<char>* Misere_XO_UI::create_player(string& name, char symbol, PlayerType type) {
	cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
		<< " player: " << name << " (" << symbol << ")\n";

	return new Player<char>(name, symbol, type);
}
Move<char>* Misere_XO_UI::get_move(Player<char>* player) {
	int x, y;

	if (player->get_type() == PlayerType::HUMAN) {
		cout << "\nPlease enter your move x and y (0 to 2): ";
		cin >> x >> y;
	}
	else if (player->get_type() == PlayerType::COMPUTER) {
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();
	}
	return new Move<char>(x, y, player->get_symbol());
}