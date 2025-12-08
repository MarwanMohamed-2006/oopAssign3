
#include <iostream>
#include <iomanip>

#include "XO_Classes.h"

using namespace std;


X_O_Board::X_O_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    rb = vector<vector<char>>(3, vector<char>(3, blank_symbol));
}

bool X_O_Board::update_board(Move<char>* move) {
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
            board[x][y] = '#';
            rb[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool X_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    for (int i = 0; i < rows; ++i) {
        if ((all_equal(rb[i][0], rb[i][1], rb[i][2]) && rb[i][0] == sym) ||
            (all_equal(rb[0][i], rb[1][i], rb[2][i]) && rb[0][i] == sym))
            return true;
    }

    if ((all_equal(rb[0][0], rb[1][1], rb[2][2]) && rb[1][1] == sym) ||
        (all_equal(rb[0][2], rb[1][1], rb[2][0]) && rb[1][1] == sym))
        return true;

    return false;
}

bool X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


XO_UI::XO_UI() : UI<char>("Weclome to Memory X-O Game by Fizz", 3) {}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_UI::get_move(Player<char>* player) {
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