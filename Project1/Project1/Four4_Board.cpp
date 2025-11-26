
#include "Four4_Board.h"

Four4_Board::Four4_Board() : Board(4, 4) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            board[i][j] = '.';

    board[0][0] = 'X'; board[0][1] = 'O'; board[0][2] = 'X'; board[0][3] = 'O';
    board[3][0] = 'O'; board[3][1] = 'X'; board[3][2] = 'O'; board[3][3] = 'X';
}

bool Four4_Board::in_bounds(int x, int y) const {
    return x >= 0 && x < 4 && y >= 0 && y < 4;
}

bool Four4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (!in_bounds(x, y)) return false;
    if (board[x][y] != '.') return false;

    const int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    for (int d = 0; d < 4; ++d) {
        int nx = x + dirs[d][0];
        int ny = y + dirs[d][1];
        if (in_bounds(nx, ny) && board[nx][ny] == s) {
            board[x][y] = s;
            board[nx][ny] = '.';
            ++n_moves;
            return true;
        }
    }

    return false;
}


bool Four4_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j <= 1; ++j)
            if (board[i][j] == s && board[i][j + 1] == s && board[i][j + 2] == s) return true;

    for (int j = 0; j < 4; ++j)
        for (int i = 0; i <= 1; ++i)
            if (board[i][j] == s && board[i + 1][j] == s && board[i + 2][j] == s) return true;

    for (int i = 0; i <= 1; ++i)
        for (int j = 0; j <= 1; ++j)
            if (board[i][j] == s && board[i + 1][j + 1] == s && board[i + 2][j + 2] == s) return true;

    for (int i = 0; i <= 1; ++i)
        for (int j = 2; j <= 3; ++j)
            if (board[i][j] == s && board[i + 1][j - 1] == s && board[i + 2][j - 2] == s) return true;

    return false;
}

bool Four4_Board::has_legal_move_for_player(char s) const {
    const int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == s)
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dirs[d][0];
                    int nj = j + dirs[d][1];
                    if (in_bounds(ni, nj) && board[ni][nj] == '.') return true;
                }
    return false;
}

bool Four4_Board::is_draw(Player<char>* player) {
    char s1 = player->get_symbol();
    char s2 = (s1 == 'X') ? 'O' : 'X';
    return !has_legal_move_for_player(s1) && !has_legal_move_for_player(s2);
}

bool Four4_Board::game_is_over(Player<char>* player) {
    if (is_win(player)) return true;
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> tmpOpp("tmp", opp, PlayerType::HUMAN);
    if (is_win(&tmpOpp)) return true;
    if (is_draw(player)) return true;
    return false;
}
