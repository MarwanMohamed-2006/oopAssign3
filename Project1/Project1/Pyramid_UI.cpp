#include "Pyramid_UI.h"
#include <iostream>
using namespace std;

Pyramid_UI::Pyramid_UI() : UI<char>("Pyramid Tic-Tac-Toe", 2) {}

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}



Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    auto board_ptr = player->get_board_ptr();
    auto mat = board_ptr->get_board_matrix();
    int rows = board_ptr->get_rows();
    int cols = board_ptr->get_columns();

    if (player->get_type() == PlayerType::COMPUTER) {
        int r, c;
        do {
            r = rand() % rows;
            c = rand() % cols;
        } while (mat[r][c] != '.');

        cout << player->get_name() << " (" << player->get_symbol()
            << ") played at position: " << r << " " << c << endl;
        return new Move<char>(r, c, player->get_symbol());
    }
    else {
        int r, c;
        while (true) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter position (r c): ";
            cin >> r >> c;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter numbers only.\n";
                continue;
            }

            if (r < 0 || r >= rows || c < 0 || c >= cols) {
                cout << "Invalid coordinates. Try again.\n";
                continue;
            }
            if (mat[r][c] == ' ') {
                cout << "This cell is blocked. Try another.\n";
                continue;
            }
            if (mat[r][c] != '.') {
                cout << "This cell is already occupied. Try again.\n";
                continue;
            }
            break;
        }
        return new Move<char>(r, c, player->get_symbol());
    }
}
