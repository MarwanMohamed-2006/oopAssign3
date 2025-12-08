
#include <unordered_set>
#include <string>

#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H


#include "BoardGame_Classes.h"
using namespace std;

class WordTicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<vector<char>> rb;
public:
    WordTicTacToe_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; };

    bool is_draw(Player<char>* player);
	bool game_is_over(Player<char>* player);
	static void loadDictionary();

    static unordered_set<string> dictionary;

    void printBoard();


};

class WordTicTacToe_UI : public UI<char> {
public:
	WordTicTacToe_UI() : UI<char>("Welcome to Word Tic-Tac-Toe!", 3) {}
	~WordTicTacToe_UI() {};
	Player<char>* create_player(string& name, char symbol, PlayerType type);
	virtual Move<char>* get_move(Player<char>* player);
};
#endif