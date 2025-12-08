#include "diamond.h"
/// <summary>

diamond_board::diamond_board() : Board(7, 7)
{
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (val_pos(i, j)) {
                board[i][j] = blank_symbol;
            }
            else {
                board[i][j] = '#';
            }
        }
    }
}

bool diamond_board::val_pos(int x, int y)
{
    if (x == 0 || x == 6)
        return (y == 3);
    else if (x == 1 || x == 5)
        return (y >= 2 && y <= 4);
    else if (x == 2 || x == 4)
        return (y >= 1 && y <= 5);
    else if (x == 3)
        return true;

    return false;
}
bool diamond_board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (!val_pos(x, y))
        return false;

    if (mark == 0) 
    {
        if (board[x][y] != blank_symbol)
        {
            n_moves--;
            board[x][y] = blank_symbol;
            return true;
        }
        return false;
    }
    else  
    {
        if (board[x][y] == blank_symbol)
        {
            n_moves++;
            board[x][y] = toupper(mark);
            return true;
        }
        return false;
    }
}

bool diamond_board::is_lose(Player<char>* player)
{
    return false;
}

bool diamond_board::game_is_over(Player<char>* player)
{
    return is_win(player) || n_moves == 25;
}
bool diamond_board::is_draw(Player<char>* player)
{
    return (n_moves == 25 && !is_win(player));
}
bool diamond_board::is_win(Player<char>* player)
{
    return check_win(player->get_symbol());
}
bool diamond_board::check_win(char sym)
{
    vector<pair<int, int>> lines_of_3;  
    vector<pair<int, int>> lines_of_4; 


    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            if (j + 2 < 7) {
                if (val_pos(i, j) && val_pos(i, j + 1) && val_pos(i, j + 2) &&
                    board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym) {
                    lines_of_3.push_back({ 0, i * 10 + j });
                }
            }
        }
        for (int j = 0; j < 4; j++) {
            if (j + 3 < 7) {
                if (val_pos(i, j) && val_pos(i, j + 1) && val_pos(i, j + 2) && val_pos(i, j + 3) &&
                    board[i][j] == sym && board[i][j + 1] == sym &&
                    board[i][j + 2] == sym && board[i][j + 3] == sym) {
                    lines_of_4.push_back({ 0, i * 10 + j });
                }
            }
        }
    }

    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 5; i++) {
            if (i + 2 < 7) {
                if (val_pos(i, j) && val_pos(i + 1, j) && val_pos(i + 2, j) &&
                    board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym) {
                    lines_of_3.push_back({ 1, i * 10 + j });
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            if (i + 3 < 7) {
                if (val_pos(i, j) && val_pos(i + 1, j) && val_pos(i + 2, j) && val_pos(i + 3, j) &&
                    board[i][j] == sym && board[i + 1][j] == sym &&
                    board[i + 2][j] == sym && board[i + 3][j] == sym) {
                    lines_of_4.push_back({ 1, i * 10 + j });
                }
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i + 2 < 7 && j + 2 < 7) {
                if (val_pos(i, j) && val_pos(i + 1, j + 1) && val_pos(i + 2, j + 2) &&
                    board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym) {
                    lines_of_3.push_back({ 2, i * 10 + j }); 
                   }
                }
            }
            for (int j = 0; j < 4; j++) {
                if (i + 3 < 7 && j + 3 < 7) {
                    if (val_pos(i, j) && val_pos(i + 1, j + 1) && val_pos(i + 2, j + 2) && val_pos(i + 3, j + 3) &&
                        board[i][j] == sym && board[i + 1][j + 1] == sym &&
                        board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym) {
                        lines_of_4.push_back({ 2, i * 10 + j });
                    }
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 2; j < 7; j++) {
                if (i + 2 < 7 && j - 2 >= 0) {
                    if (val_pos(i, j) && val_pos(i + 1, j - 1) && val_pos(i + 2, j - 2) &&
                        board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym) {
                        lines_of_3.push_back({ 3, i * 10 + j }); 
                    }
                }
            }
            for (int j = 3; j < 7; j++) {
                if (i + 3 < 7 && j - 3 >= 0) {
                    if (val_pos(i, j) && val_pos(i + 1, j - 1) && val_pos(i + 2, j - 2) && val_pos(i + 3, j - 3) &&
                        board[i][j] == sym && board[i + 1][j - 1] == sym &&
                        board[i][j - 2] == sym && board[i + 3][j - 3] == sym) {
                        lines_of_4.push_back({ 3, i * 10 + j });
                    }
                }
            }
        }

        for (auto& line3 : lines_of_3) {
            for (auto& line4 : lines_of_4) {
                if (line3.first != line4.first) {  
                    return true;
                }
            }
        }

        return false;
    }
 
diamond_UI::diamond_UI() : UI<char>("Welcome to Fizz Diamond game", 3)
{
    cout << "Diamond game initialized with a 7x7 board.\n";
    cout << "Only the diamond-shaped positions are playable!\n";
    cout << "Get 3 in a row within the diamond pattern to win!\n";
    cout << "    0 1 2 3 4\n";
    cout << "0   . . . * . . .\n";
    cout << "1   . . * * * . .\n";
    cout << "2   . * * * * * .\n";
    cout << "3   * * * * * * *\n";
    cout << "4   . * * * * * .\n";
    cout << "5   . . * * * . .\n";
    cout << "6   . . . * . . .\n";
    cout << "\n";
}
Player<char>* diamond_UI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Move<char>* diamond_UI::get_move(Player<char>* player)
{
    int x, y;

    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "\nPlease enter your move x and y (0 to 6): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    diamond_board* board = dynamic_cast<diamond_board*>(player->get_board_ptr());
    char computer_symbol = player->get_symbol();
    char human_symbol = (computer_symbol == 'X') ? 'O' : 'X';

    Move<char>* move = board->find_best_move(computer_symbol, human_symbol);

    if (move)
    {
        cout << "\nComputer: (" << move->get_x() << "," << move->get_y() << ")\n";
        return move;
    }
    return new Move<char>(x, y, player->get_symbol());
}

int diamond_board::minimax(bool is_maximizing, char sym1, char sym2,int depth)
{
    if (check_win(sym1))    
        return 1;
    if (check_win(sym2))
        return -1;
    if (depth == 0 || n_moves == 25) {
        return 0; 
    }

    if (is_maximizing)
    {
        int best = -1000;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (board[i][j] == blank_symbol &&val_pos(i, j))
                {
                    board[i][j] = sym1;
					n_moves++;
                    int score = minimax(false, sym1, sym2, depth - 1);

                    board[i][j] = blank_symbol;
					n_moves--;
                    best = max(best, score);
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (board[i][j] == blank_symbol && val_pos(i, j)) {
                    board[i][j] = sym2;
                    n_moves++;
                    int score = minimax(true, sym1, sym2, depth - 1);
                    board[i][j] = blank_symbol;
                    n_moves--;
                    best = min(best, score);
                }
            }
        }
        return best;
    }
}
Move<char>* diamond_board::find_best_move(char sym1, char sym2)
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == blank_symbol && val_pos(i, j))
            {
                board[i][j] = sym1;
                if (!check_win(sym1))
                {
                    bool pl2_lose = false;
                    for (int x = 0; x < 7 && !pl2_lose; x++)
                    {
                        for (int y = 0; y < 7 && !pl2_lose; y++)
                        {
                            if (board[x][y] == blank_symbol && val_pos(x, y))
                            {
                                board[x][y] = sym2;
                                if (check_win(sym2))
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
    int best_row = -1;
    int best_col = -1;
    int depth = 3 ;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == blank_symbol && val_pos(i, j))
            {
                board[i][j] = sym1;
                n_moves++;
                int score = minimax(false, sym1, sym2, depth);
                board[i][j] = blank_symbol;
                n_moves--;
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
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == blank_symbol && val_pos(i, j)) {
                return new Move<char>(i, j, sym1);
            }
        }
    }


    return nullptr;
}