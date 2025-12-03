#include <iostream>
#include "Misere_XO.h"
using namespace std;
Misere_XO_Board::Misere_XO_Board() : Board<char>(3, 3)
{
    for (auto &row : board)
        for (auto &cell : row)
            cell = blank_symbol;
}
bool Misere_XO_Board::update_board(Move<char> *move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0))
    {
        if (mark == 0)
        {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else
        {
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}



bool Misere_XO_Board::_3rows(char sym)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
    }
    
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
    
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;
    
    return false;
}

bool Misere_XO_Board::is_lose(Player<char> *player)
{
    return _3rows(player->get_symbol());
}
bool Misere_XO_Board::is_draw(Player<char> *player)
{
    if (n_moves != 9)
        return false;

    return !_3rows('X') && !_3rows('O');
}
bool Misere_XO_Board::game_is_over(Player<char> *player)
{
    return is_lose(player) || is_draw(player);
}

bool Misere_XO_Board::is_win(Player<char>* player)
{
    return false;
}


Misere_XO_UI::Misere_XO_UI() : UI<char>("Welcome to Fizz Misere Tic-Tac-Toe Game", 3)
{
    cout << "\n REVERSE RULES GAME! \n";
    cout << "========================\n";
    cout << "  WARNING: The rules are REVERSED!\n";
    cout << "- You lose if you make three in a row!\n";
    cout << "========================\n";
}
Player<char> *Misere_XO_UI::create_player(string &name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Move<char> *Misere_XO_UI::get_move(Player<char> *player)
{
    int x, y;

    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else
    {   
        Misere_XO_Board *board = dynamic_cast<Misere_XO_Board *>(player->get_board_ptr());
        char computer_symbol = player->get_symbol();
        char human_symbol = (computer_symbol == 'X') ? 'O' : 'X';

        Move<char> *move = board->find_best_move(computer_symbol, human_symbol);

        if (move)
        {
            cout << "\nComputer: (" << move->get_x() << "," << move->get_y() << ")\n";
            return move;
        }
        return new Move<char>(x, y, computer_symbol);
    }
}

Move<char> *Misere_XO_Board::find_best_move(char sym1, char sym2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == blank_symbol)
            {
                board[i][j] = sym1;
                if (!_3rows(sym1))
                {
                    bool pl2_lose = false;
                    for (int x = 0; x < 3 && !pl2_lose; x++)
                    {
                        for (int y = 0; y < 3 && !pl2_lose; y++)
                        {
                            if (board[x][y] == blank_symbol)
                            {
                                board[x][y] = sym2;
                                if (_3rows(sym2))
                                    pl2_lose = true;
                                board[x][y] = blank_symbol;
                            }
                        }
                    }
                    if (pl2_lose)
                    {
                        board[i][j] = blank_symbol;
                        return new Move<char>(i, j, sym1);
                    }
                }
                board[i][j] = blank_symbol;
            }
        }
    }

    int best_score = -1000;
    int best_row = -1, best_col = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == blank_symbol)
            {
                board[i][j] = sym1;
                int score = minimax(false, sym1, sym2);
                board[i][j] = blank_symbol;

                if (score > best_score)
                {
                    best_score = score;
                    best_row = i;
                    best_col = j;
                }
            }
        }
    }

    if (best_row != -1)
    {
        return new Move<char>(best_row, best_col, sym1);
    }

    return nullptr;
}

int Misere_XO_Board::minimax(bool is_maximizing, char sym1, char sym2)
{
    if (_3rows(sym1))
        return -1;
    if (_3rows(sym2))
        return 1;

    bool full = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == blank_symbol)
            {
                full = false;
                i = 3;
                break;
            }
        }
    }
    if (full)
        return 0;

    if (is_maximizing)
    {
        int best = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == blank_symbol)
                {   
                    board[i][j] = sym1;
                    best = max(best, minimax(false, sym1, sym2));
                    board[i][j] = blank_symbol;
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == blank_symbol)
                {
                    board[i][j] = sym2;
                    best = min(best, minimax(true, sym1, sym2));
                    board[i][j] = blank_symbol;
                }
            }
        }
        return best;
    }
}