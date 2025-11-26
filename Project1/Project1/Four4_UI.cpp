
#include "Four4_UI.h"
#include <iostream>
using namespace std;

Four4_UI::Four4_UI() : UI<char>("4x4 Tic-Tac-Toe (move tokens)", 2) {}

Player<char>* Four4_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Four4_UI::get_move(Player<char>* player) {
    auto board_ptr = player->get_board_ptr();
    auto mat = board_ptr->get_board_matrix();
    int rows = board_ptr->get_rows();
    int cols = board_ptr->get_columns();

    if (player->get_type() == PlayerType::COMPUTER) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (mat[i][j] == '.') {
                    const int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dirs[d][0];
                        int nj = j + dirs[d][1];
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && mat[ni][nj] == player->get_symbol()) {
                            cout << player->get_name() << " (" << player->get_symbol() << ") moves to " << i << " " << j << endl;
                            return new Move<char>(i, j, player->get_symbol());
                        }
                    }
                }
            }
        }
    }
    else {
        int dstX, dstY;
        while (true) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter position (r c): ";
            cin >> dstX >> dstY;

            if (dstX < 0 || dstX >= rows || dstY < 0 || dstY >= cols) {
                cout << "Invalid coordinates. Try again.\n";
                continue;
            }

            if (mat[dstX][dstY] != '.') {
                cout << "Destination not empty. Try again.\n";
                continue;
            }
            break;
        }
        return new Move<char>(dstX, dstY, player->get_symbol());
    }

    return nullptr;
}
