#include "Pyramid_Board.h"

Pyramid_Board::Pyramid_Board() : Board(3, 5) {
    board = {
        {' ', ' ', '.', ' ', ' '},
        {' ', '.', '.', '.', ' '},
        {'.', '.', '.', '.', '.'}
    };
}

bool Pyramid_Board::valid_cell(int r, int c) const {
    if (r < 0 || r >= 3 || c < 0 || c >= 5) return false;
    return board[r][c] != ' ';
}

bool Pyramid_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (!valid_cell(r, c)) return false;
    if (board[r][c] != '.') return false;

    board[r][c] = s;
    ++n_moves;
    return true;
}

bool Pyramid_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 5; ++c) {
            if (!valid_cell(r, c)) continue;
            if (board[r][c] != s) continue;
            for (auto dir : directions) {
                int r1 = r + dir.first;
                int c1 = c + dir.second;
                int r2 = r + 2 * dir.first;
                int c2 = c + 2 * dir.second;
                if (valid_cell(r1, c1) && valid_cell(r2, c2)) {
                    if (board[r1][c1] == s && board[r2][c2] == s) return true;
                }
            }
        }
    }
    return false;
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 5; ++c)
            if (valid_cell(r, c) && board[r][c] == '.') return false;

    if (is_win(player)) return false;
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 5; ++c) {
            if (!valid_cell(r, c)) continue;
            if (board[r][c] != opp) continue;
            for (auto dir : directions) {
                int r1 = r + dir.first;
                int c1 = c + dir.second;
                int r2 = r + 2 * dir.first;
                int c2 = c + 2 * dir.second;
                if (valid_cell(r1, c1) && valid_cell(r2, c2)) {
                    if (board[r1][c1] == opp && board[r2][c2] == opp) return false;
                }
            }
        }
    }
    return true;
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    if (is_win(player)) return true;
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    auto opp_win = [&](char s)->bool {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 5; ++c) {
                if (!valid_cell(r, c)) continue;
                if (board[r][c] != s) continue;
                for (auto dir : directions) {
                    int r1 = r + dir.first;
                    int c1 = c + dir.second;
                    int r2 = r + 2 * dir.first;
                    int c2 = c + 2 * dir.second;
                    if (valid_cell(r1, c1) && valid_cell(r2, c2)) {
                        if (board[r1][c1] == s && board[r2][c2] == s) return true;
                    }
                }
            }
        }
        return false;
        };

    if (opp_win(opp)) return true;
    if (is_draw(player)) return true;
    return false;
}