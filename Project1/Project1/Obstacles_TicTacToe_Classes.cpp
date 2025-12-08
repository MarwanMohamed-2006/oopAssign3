#include "Obstacles_TicTacToe_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

// ====================== BOARD IMPLEMENTATION ======================

Obstacles_Board::Obstacles_Board() : Board(6, 6) {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            board[i][j] = '.';
    n_moves = 0;
}

bool Obstacles_Board::is_obstacle(int x, int y) const {
    for (const auto& pos : obstaclePositions)
        if (pos.first == x && pos.second == y)
            return true;
    return false;
}

bool Obstacles_Board::is_valid_move(int x, int y) const {
    if (x < 0 || x >= 6 || y < 0 || y >= 6) return false;
    if (is_obstacle(x, y)) return false;
    if (board[x][y] != '.') return false;
    return true;
}

bool Obstacles_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (!is_valid_move(x, y)) return false;

    board[x][y] = symbol;
    n_moves++;

    // Add obstacles after every 2 moves (one full round)
    if (n_moves % 2 == 0)
        add_random_obstacles();

    return true;
}

void Obstacles_Board::add_random_obstacles() {
    int added = 0;
    srand(static_cast<unsigned int>(time(nullptr)));

    while (added < 2) {
        int x = rand() % 6;
        int y = rand() % 6;

        if (board[x][y] == '.' && !is_obstacle(x, y)) {
            obstaclePositions.push_back({x, y});
            board[x][y] = '#';  // Mark as obstacle
            added++;
        }
    }
}

bool Obstacles_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    // Check horizontal (4 in a row)
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j <= 2; ++j)
            if (board[i][j] == s && board[i][j+1] == s &&
                board[i][j+2] == s && board[i][j+3] == s)
                return true;

    // Check vertical
    for (int j = 0; j < 6; ++j)
        for (int i = 0; i <= 2; ++i)
            if (board[i][j] == s && board[i+1][j] == s &&
                board[i+2][j] == s && board[i+3][j] == s)
                return true;

    // Check main diagonal (\)
    for (int i = 0; i <= 2; ++i)
        for (int j = 0; j <= 2; ++j)
            if (board[i][j] == s && board[i+1][j+1] == s &&
                board[i+2][j+2] == s && board[i+3][j+3] == s)
                return true;

    // Check anti-diagonal (/)
    for (int i = 0; i <= 2; ++i)
        for (int j = 3; j < 6; ++j)
            if (board[i][j] == s && board[i+1][j-1] == s &&
                board[i+2][j-2] == s && board[i+3][j-3] == s)
                return true;

    return false;
}

bool Obstacles_Board::is_draw(Player<char>* player) {
    // If player wins, not a draw
    if (is_win(player)) return false;

    // If opponent wins, not a draw
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> tmp("TempOpponent", opp, PlayerType::HUMAN);
    if (is_win(&tmp)) return false;

    // Check if any empty cell exists (not obstacle)
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (board[i][j] == '.' && !is_obstacle(i, j))
                return false;  // Still have empty cells

    return true;  // Board is full, no winner
}

bool Obstacles_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void Obstacles_Board::display_with_obstacles() const {
    cout << "\n     ";
    for (int j = 0; j < 6; ++j)
        cout << setw(2) << j;
    cout << "\n    " << string(13, '-') << "\n";

    for (int i = 0; i < 6; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < 6; ++j) {
            cout << " ";
            if (is_obstacle(i, j))
                cout << "#";
            else
                cout << board[i][j];
            cout << "|";
        }
        cout << "\n    " << string(13, '-') << "\n";
    }
}

// ====================== UI IMPLEMENTATION ======================

Obstacles_UI::Obstacles_UI() : UI<char>("Obstacles Tic-Tac-Toe (6x6)", 2), obsBoard(nullptr) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_UI::get_move(Player<char>* player) {
    if (!player->get_board_ptr()) {
        cout << "Error: Board pointer is null!\n";
        return nullptr;
    }

    Obstacles_Board* board_ptr = obsBoard;

    if (!board_ptr) {
        board_ptr = dynamic_cast<Obstacles_Board*>(player->get_board_ptr());
        if (!board_ptr) {
            cout << "Error: Cannot access board!\n";
            return nullptr;
        }
        obsBoard = board_ptr;
    }

    if (player->get_type() == PlayerType::COMPUTER) {
        int x, y, tries = 0;
        do {
            x = rand() % 6;
            y = rand() % 6;
            tries++;
            if (tries > 50) {
                cout << "Computer cannot find valid move!\n";
                return nullptr;
            }
        } while (!board_ptr->is_valid_move(x, y));

        cout << player->get_name() << " (Computer) plays at: "
             << x << " " << y << endl;

        return new Move<char>(x, y, player->get_symbol());
    }

    int x, y;
    while (true) {
        cout << player->get_name() << " (" << player->get_symbol()
             << ") enter row and column (0-5): ";

        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter numbers only.\n";
            continue;
        }

        if (board_ptr->is_valid_move(x, y)) break;

        if (x < 0 || x >= 6 || y < 0 || y >= 6)
            cout << "Out of bounds! (0-5 only)\n";
        else if (board_ptr->is_obstacle(x, y))
            cout << "Obstacle at that cell! (#)\n";
        else if (board_ptr->get_board_matrix()[x][y] != '.')
            cout << "Cell already occupied!\n";
        else
            cout << "Invalid move!\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}
