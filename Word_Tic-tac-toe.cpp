#include "Word_Tic-tac-toe.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
using namespace std;

unordered_set<string> WordTicTacToe_Board::dictionary;


WordTicTacToe_Board::WordTicTacToe_Board() : Board(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
	rb = vector<vector<char>>(3, vector<char>(3, blank_symbol));

}
bool WordTicTacToe_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
            rb[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            board[x][y] = toupper(mark);
            rb[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool WordTicTacToe_Board::is_win(Player<char>* player)
{
    string word;

    for (int i = 0; i < 3; i++) {
        word = "";
        for (int j = 0; j < 3; j++)
            word += board[i][j];
        if (dictionary.count(word)) return true;
    }

    for (int i = 0; i < 3; i++) {
        word = "";
        for (int j = 0; j < 3; j++)
            word += board[j][i];
        if (dictionary.count(word)) return true;
    }

    word = "";
    word += board[0][0]; word += board[1][1]; word += board[2][2];
    if (dictionary.count(word)) return true;

    word = "";
    word += board[0][2]; word += board[1][1]; word += board[2][0];
    if (dictionary.count(word)) return true;

    return false;
}

bool WordTicTacToe_Board::is_draw(Player<char>* player)
{
	return (n_moves == 9 && !is_win(player));
}

bool WordTicTacToe_Board::game_is_over(Player<char>* player)
{
	if (is_win(player) || is_draw(player))
		return true;
    return false;
}

void WordTicTacToe_Board::loadDictionary()
{
    ifstream file("dic.txt");
    string word;
    while (file >> word)
    {
		dictionary.insert(word);
		
    }
}



Player<char>* WordTicTacToe_UI::create_player(string& name, char symbol, PlayerType type)
{
	return new Player<char>(name, symbol, type);
}

Move<char>* WordTicTacToe_UI::get_move(Player<char>* player)
{
    int x, y;
    char letter;
    cout << player->get_name() << "'s turn. Enter row col letter: ";
    cin >> x >> y >> letter;
    return new Move<char>(x, y, toupper(letter));
}

void WordTicTacToe_Board::printBoard() {
    cout << "\nBoard:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}