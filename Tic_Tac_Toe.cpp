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
	int count = 0;
	const char sym = player->get_symbol();
	auto all_equal = [&](char a, char b, char c) {
		return a == b && b == c && a != blank_symbol;
		};
	// Check rows 
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= 5 - 3; j++) {
			if (all_equal(board[i][j], board[i][j + 1], board[i][j + 2]))
				count++;
		}
	}
	// Check columns
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i <= 5 - 3; i++) {
			if (all_equal(board[i][j], board[i + 1][j], board[i + 2][j]))
				count++;
		}
	}

	// Check diagonals
	for (int i = 0; i <= 5 - 3; i++) {
		for (int j = 0; j <= 5 - 3; j++) {
			if (all_equal(board[i][j], board[i + 1][j + 1], board[i + 2][j + 2]))
				count++;
		}
	}
	// Check anti-diagonals
	for (int i = 0; i <= 5 - 3; i++) {
		for (int j = 2; j < 5; j++) {
			if (all_equal(board[i][j], board[i + 1][j - 1], board[i + 2][j - 2]))
				count++;
		}
	}


	return false;


}

int TicTacToe_Board::counting(Player<char>* player)
{
	int count = 0;
	const char sym = player->get_symbol();
	auto all_equal = [&](char a, char b, char c) {
		return a == b && b == c && a != blank_symbol;
		};
	// Check rows 
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= 5 - 3; j++) {
			if (all_equal(board[i][j], board[i][j + 1], board[i][j + 2]))
				count++;
		}
	}
	// Check columns
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i <= 5 - 3; i++) {
			if (all_equal(board[i][j], board[i + 1][j], board[i + 2][j]))
				count++;
		}
	}

	// Check diagonals
	for (int i = 0; i <= 5 - 3; i++) {
		for (int j = 0; j <= 5 - 3; j++) {
			if (all_equal(board[i][j], board[i + 1][j + 1], board[i + 2][j + 2]))
				count++;
		}
	}
	// Check anti-diagonals
	for (int i = 0; i <= 5 - 3; i++) {
		for (int j = 2; j < 5; j++) {
			if (all_equal(board[i][j], board[i + 1][j - 1], board[i + 2][j - 2]))
				count++;
		}
	}


	return count;


}



bool TicTacToe_Board::is_lose(Player<char>*)
{
	return false;
}







bool TicTacToe_Board::is_draw(Player<char>* player)
{
	return n_moves == 25;
	
}



bool TicTacToe_Board::game_is_over(Player<char>* player)
{
	return n_moves >= 25;
}

void TicTacToe_Board::winner(Player<char>* player1, Player<char>* player2)
{
	int count1 = counting(player1);
	int count2 = counting(player2);

	cout << "\nGame Over!\n";
	cout << player1->get_name() << " sequences: " << count1 << endl;
	cout << player2->get_name() << " sequences: " << count2 << endl;

	if (count1 > count2)
		cout << player1->get_name() << " wins!\n";
	else if (count2 > count1)
		cout << player2->get_name() << " wins!\n";
	else
		cout << "It's a draw!\n";
}



Player<char>* TicTacToe_UI::create_player(string& name, char symbol, PlayerType type)
{
	// Create player based on typee
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