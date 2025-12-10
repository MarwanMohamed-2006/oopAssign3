#include <iostream>
#include <iomanip>
#include "ConnectFour_Classes.h"

using namespace std;

ConnectFour_Board::ConnectFour_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool ConnectFour_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    // Validate column
    if (col < 0 || col >= columns) {
        return false;
    }

    // Find the lowest available row in the column (gravity effect)
    int target_row = -1;
    for (int row = rows - 1; row >= 0; --row) {
        if (board[row][col] == blank_symbol) {
            target_row = row;
            break;
        }
    }

    // If column is full, move is invalid
    if (target_row == -1) {
        return false;
    }

    // Place the mark
    board[target_row][col] = toupper(mark);
    n_moves++;
    return true;
}

bool ConnectFour_Board::check_line(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4, char symbol) {
    return board[r1][c1] == symbol &&
        board[r2][c2] == symbol &&
        board[r3][c3] == symbol &&
        board[r4][c4] == symbol;
}

bool ConnectFour_Board::is_win(Player<char>* player) {
    char sym = toupper(player->get_symbol());

    // Check horizontal wins
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (check_line(r, c, r, c + 1, r, c + 2, r, c + 3, sym)) {
                return true;
            }
        }
    }

    // Check vertical wins
    for (int r = 0; r <= rows - 4; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (check_line(r, c, r + 1, c, r + 2, c, r + 3, c, sym)) {
                return true;
            }
        }
    }

    // Check diagonal wins (bottom-left to top-right)
    for (int r = 3; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (check_line(r, c, r - 1, c + 1, r - 2, c + 2, r - 3, c + 3, sym)) {
                return true;
            }
        }
    }

    // Check diagonal wins (top-left to bottom-right)
    for (int r = 0; r <= rows - 4; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            if (check_line(r, c, r + 1, c + 1, r + 2, c + 2, r + 3, c + 3, sym)) {
                return true;
            }
        }
    }

    return false;
}

bool ConnectFour_Board::is_draw(Player<char>* player) {
    return (n_moves == rows * columns && !is_win(player));
}

bool ConnectFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

ConnectFour_UI::ConnectFour_UI() : UI<char>("Welcome to Connect Four (Four-in-a-Row) Game", 7) {}

Player<char>* ConnectFour_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* ConnectFour_UI::get_move(Player<char>* player) {
    int col;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlayer " << player->get_name() << " (" << player->get_symbol()
            << "), enter column number (0 to 6): ";
        cin >> col;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Computer randomly selects a column
        col = rand() % player->get_board_ptr()->get_columns();
        cout << "\nComputer selects column: " << col << endl;
    }

    // Row doesn't matter as the piece will fall to the lowest available position
    return new Move<char>(0, col, player->get_symbol());
}