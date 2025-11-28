//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include "infinity-tictactoe.h"

using namespace std;

//--------------------------------------- Infinity_Board Implementation

Infinity_Board::Infinity_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid coordinates! Must be between 0 and 2.\n";
        return false;
    }

    // Check if cell is already occupied
    if (board[x][y] != blank_symbol) {
        cout << "Cell already occupied!\n";
        return false;
    }

    // Apply the move first
    board[x][y] = toupper(mark);

    // Apply the move
    n_moves++;
    move_history.push({ x, y });

    cout << "Move " << n_moves << ": '" << toupper(mark)
        << "' placed at (" << x << ", " << y << ")\n";

    // After every 3 moves, remove the oldest mark
    if (move_history.size() > 3) {
        auto oldest = move_history.front();
        move_history.pop();

        int old_x = oldest.first;
        int old_y = oldest.second;
        char removed_symbol = board[old_x][old_y];

        board[old_x][old_y] = blank_symbol;

        cout << ">>> Oldest mark '" << removed_symbol
            << "' at (" << old_x << ", " << old_y << ") has vanished!\n";
    }

    return true;
}

bool Infinity_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a == sym;
        };

    // Check rows
    for (int i = 0; i < rows; ++i) {
        if (all_equal(board[i][0], board[i][1], board[i][2]))
            return true;
    }

    // Check columns
    for (int j = 0; j < columns; ++j) {
        if (all_equal(board[0][j], board[1][j], board[2][j]))
            return true;
    }

    // Check diagonals
    if (all_equal(board[0][0], board[1][1], board[2][2]))
        return true;
    if (all_equal(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}

bool Infinity_Board::is_draw(Player<char>* player) {
    // In Infinity Tic-Tac-Toe, the game can theoretically go on forever
    // We'll call it a draw after 50 moves if no one has won
    // (This is a practical limit to prevent infinite games)
    if (n_moves >= 50) {
        cout << "\n=== Game reached move limit (50 moves). It's a draw! ===\n";
        return true;
    }
    return false;
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- Infinity_UI Implementation

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn ("
            << player->get_symbol() << ")\n";
        cout << "Enter row (0-2): ";
        cin >> x;
        cout << "Enter column (0-2): ";
        cin >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Computer strategy: Find an empty cell
        vector<vector<char>> board_matrix = player->get_board_ptr()->get_board_matrix();
        vector<pair<int, int>> empty_cells;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board_matrix[i][j] == '.') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (!empty_cells.empty()) {
           
            int idx = rand() % empty_cells.size();
            x = empty_cells[idx].first;
            y = empty_cells[idx].second;
        }
        else {
            // Fallback: try random positions
            x = rand() % 3;
            y = rand() % 3;
        }

        cout << "\nComputer " << player->get_name() << " ("
            << player->get_symbol() << ") plays at (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

 