//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include "SUS.h"
#include <vector>
#include <map>

using namespace std;

//--------------------------------------- SUS_Board Implementation

int SUS_Board::count_sus_sequences() {
    int count = 0;

    auto is_sus = [&](char a, char b, char c) {
        return a == 'S' && b == 'U' && c == 'S';
        };

    // Check Rows
    for (int i = 0; i < 3; ++i) {
        if (is_sus(board[i][0], board[i][1], board[i][2])) count++;
    }

    // Check Columns
    for (int j = 0; j < 3; ++j) {
        if (is_sus(board[0][j], board[1][j], board[2][j])) count++;
    }

    // Check Diagonals
    if (is_sus(board[0][0], board[1][1], board[2][2])) count++;
    if (is_sus(board[0][2], board[1][1], board[2][0])) count++;

    return count;
}

SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    player_scores['X'] = 0;
    player_scores['O'] = 0;
}

bool SUS_Board::update_board(Move<char>* move) {
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

    // Only allow 'S' or 'U' to be placed
    char upper_mark = toupper(mark);
    if (upper_mark != 'S' && upper_mark != 'U') {
        cout << "Invalid symbol! You must place either 'S' or 'U'.\n";
        return false;
    }

    // Count sequences before the move
    int sequences_before = count_sus_sequences();

    // Apply the move
    board[x][y] = upper_mark;
    n_moves++;

    // Count sequences after the move
    int sequences_after = count_sus_sequences();

    // Award points for new sequences created
    int new_sequences = sequences_after - sequences_before;
    if (new_sequences > 0) {
        // Determine which player made this move based on turn count
        char current_player = (n_moves % 2 == 1) ? 'X' : 'O';
        player_scores[current_player] += new_sequences;
        cout << ">>> Player " << current_player << " created " << new_sequences
            << " S-U-S sequence(s)! Score: " << player_scores[current_player] << "\n";
    }

    return true;
}

bool SUS_Board::is_win(Player<char>* player) {
    // Check if game is over first
    if (n_moves < 9) {
        return false;
    }

    // Game is over, check if this player won
    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    return player_scores[player_symbol] > player_scores[opponent_symbol];
}

bool SUS_Board::is_draw(Player<char>* player) {
    // Check if game is over first
    if (n_moves < 9) {
        return false;
    }

    // Game is over, check if scores are tied
    return player_scores['X'] == player_scores['O'];
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return (n_moves == 9);
}

map<char, int> SUS_Board::get_scores() const {
    return player_scores;
}

//--------------------------------------- SUS_UI Implementation

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ") - Can place S or U\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";

        // Display current scores
        SUS_Board* sus_board = dynamic_cast<SUS_Board*>(player->get_board_ptr());
        if (sus_board) {
            map<char, int> scores = sus_board->get_scores();
            cout << "Current Scores - X: " << scores['X'] << ", O: " << scores['O'] << "\n";
        }

        cout << "Enter your move:\n";
        cout << "  Row (0-2): ";
        cin >> x;
        cout << "  Column (0-2): ";
        cin >> y;
        cout << "  Letter (S or U): ";
        cin >> letter;

        return new Move<char>(x, y, letter);
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        SUS_Board* sus_board = dynamic_cast<SUS_Board*>(player->get_board_ptr());

        // Find empty cell
        vector<vector<char>> board_matrix = sus_board->get_board_matrix();
        vector<pair<int, int>> empty_cells;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board_matrix[i][j] == '.') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (empty_cells.empty()) {
            return new Move<char>(0, 0, 'S'); // Fallback
        }

        // Pick random empty cell
        int idx = rand() % empty_cells.size();
        x = empty_cells[idx].first;
        y = empty_cells[idx].second;

        // Randomly choose S or U
        letter = (rand() % 2 == 0) ? 'S' : 'U';

        cout << "\nComputer " << player->get_name() << " (" << player->get_symbol()
            << ") plays '" << letter << "' at position (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, letter);
}