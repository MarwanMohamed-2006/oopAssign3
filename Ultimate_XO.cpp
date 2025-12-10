#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ultimate_XO.h"
using namespace std;


Ultimate_XO_Board::Ultimate_XO_Board() : Board<char>(9, 9) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            small_board_winners[i][j] = blank_symbol;

    next_board = -1;
}

bool Ultimate_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= 9 || y < 0 || y >= 9)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    int board_num = (x / 3) * 3 + (y / 3);

    if (next_board != -1 && next_board != board_num)
        return false;

    int board_row = x / 3;
    int board_col = y / 3;

    if (small_board_winners[board_row][board_col] != blank_symbol)
        return false;

    board[x][y] = mark;
    n_moves++;

    char winner = check_small_board_winner(board_row, board_col);
    if (winner != blank_symbol) {
        small_board_winners[board_row][board_col] = winner;
    }

    int next_row = x % 3;
    int next_col = y % 3;
    int next_board_num = next_row * 3 + next_col;

    int next_board_row = next_row;
    int next_board_col = next_col;

    if (small_board_winners[next_board_row][next_board_col] != blank_symbol) {
        next_board = -1;
    }
    else {
        next_board = next_board_num;
    }

    return true;
}

char Ultimate_XO_Board::check_small_board_winner(int board_row, int board_col) {
    int start_x = board_row * 3;
    int start_y = board_col * 3;

    for (int i = 0; i < 3; i++) {
        if (board[start_x + i][start_y] != blank_symbol &&
            board[start_x + i][start_y] == board[start_x + i][start_y + 1] &&
            board[start_x + i][start_y] == board[start_x + i][start_y + 2]) {
            return board[start_x + i][start_y];
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[start_x][start_y + j] != blank_symbol &&
            board[start_x][start_y + j] == board[start_x + 1][start_y + j] &&
            board[start_x][start_y + j] == board[start_x + 2][start_y + j]) {
            return board[start_x][start_y + j];
        }
    }

    if (board[start_x][start_y] != blank_symbol &&
        board[start_x][start_y] == board[start_x + 1][start_y + 1] &&
        board[start_x][start_y] == board[start_x + 2][start_y + 2]) {
        return board[start_x][start_y];
    }

    if (board[start_x][start_y + 2] != blank_symbol &&
        board[start_x][start_y + 2] == board[start_x + 1][start_y + 1] &&
        board[start_x][start_y + 2] == board[start_x + 2][start_y]) {
        return board[start_x][start_y + 2];
    }

    return blank_symbol;
}

bool Ultimate_XO_Board::check_main_board_win(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (small_board_winners[i][0] == symbol &&
            small_board_winners[i][1] == symbol &&
            small_board_winners[i][2] == symbol) {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (small_board_winners[0][j] == symbol &&
            small_board_winners[1][j] == symbol &&
            small_board_winners[2][j] == symbol) {
            return true;
        }
    }

    if (small_board_winners[0][0] == symbol &&
        small_board_winners[1][1] == symbol &&
        small_board_winners[2][2] == symbol) {
        return true;
    }

    if (small_board_winners[0][2] == symbol &&
        small_board_winners[1][1] == symbol &&
        small_board_winners[2][0] == symbol) {
        return true;
    }

    return false;
}

bool Ultimate_XO_Board::is_win(Player<char>* player) {
    return check_main_board_win(player->get_symbol());
}

bool Ultimate_XO_Board::is_lose(Player<char>* player) {
    return false;
}

bool Ultimate_XO_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (small_board_winners[i][j] == blank_symbol) {
                int start_x = i * 3;
                int start_y = j * 3;
                for (int x = start_x; x < start_x + 3; x++) {
                    for (int y = start_y; y < start_y + 3; y++) {
                        if (board[x][y] == blank_symbol)
                            return false;
                    }
                }
            }
        }
    }

    return !is_win(player);
}

bool Ultimate_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


Ultimate_XO_UI::Ultimate_XO_UI() : UI<char>("Welcome to Ultimate Tic-Tac-Toe!", 3) {
    cout << "\n================================\n";
    cout << "  ULTIMATE TIC-TAC-TOE RULES\n";
    cout << "================================\n";
    cout << "- 3x3 grid of 3x3 boards\n";
    cout << "- Win 3 small boards in a row to win!\n";
    cout << "- Your move sends opponent to that board\n";
    cout << "- Enter: row (0-8) and column (0-8)\n";
    cout << "================================\n\n";
}

Player<char>* Ultimate_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Ultimate_XO_UI::get_move(Player<char>* player) {
    Ultimate_XO_Board* board = dynamic_cast<Ultimate_XO_Board*>(player->get_board_ptr());

    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        int next = board->get_next_board();
        if (next != -1) {
            cout << "\nYou must play in board " << next << "\n";
        }
        else {
            cout << "\nYou can play in any available board\n";
        }

        cout << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Enter row and column (0-8): ";
        cin >> x >> y;
    }
    else {
        do {
            x = rand() % 9;
            y = rand() % 9;
        } while (board->get_board_matrix()[x][y] != '.');

        cout << "\nComputer plays: (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}