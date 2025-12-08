
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Numerical_TicTacToe_Classes.h"

using namespace std;

Numerical_Board::Numerical_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    player1_available = { 1, 3, 5, 7, 9 }; 
    player2_available = { 2, 4, 6, 8 };  
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid coordinates! Must be between 0 and 2.\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Cell already occupied!\n";
        return false;
    }

    bool is_odd = (number % 2 == 1);
    set<int>& available = is_odd ? player1_available : player2_available;

    if (available.find(number) == available.end()) {
        cout << "Number " << number << " is not available or already used!\n";
        return false;
    }

    board[x][y] = number;
    available.erase(number);
    n_moves++;
    return true;
}

bool Numerical_Board::is_win(Player<int>* player) {
    for (int i = 0; i < rows; ++i) {
        if (board[i][0] != blank_symbol &&
            board[i][1] != blank_symbol &&
            board[i][2] != blank_symbol) {
            if (board[i][0] + board[i][1] + board[i][2] == 15) {
                return true;
            }
        }
    }

    for (int j = 0; j < columns; ++j) {
        if (board[0][j] != blank_symbol &&
            board[1][j] != blank_symbol &&
            board[2][j] != blank_symbol) {
            if (board[0][j] + board[1][j] + board[2][j] == 15) {
                return true;
            }
        }
    }

    if (board[0][0] != blank_symbol &&
        board[1][1] != blank_symbol &&
        board[2][2] != blank_symbol) {
        if (board[0][0] + board[1][1] + board[2][2] == 15) {
            return true;
        }
    }

    if (board[0][2] != blank_symbol &&
        board[1][1] != blank_symbol &&
        board[2][0] != blank_symbol) {
        if (board[0][2] + board[1][1] + board[2][0] == 15) {
            return true;
        }
    }

    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

set<int> Numerical_Board::get_available_numbers(int symbol) const {
    return (symbol == 1) ? player1_available : player2_available;
}


Numerical_UI::Numerical_UI() : UI<int>("Welcome to FCAI Numerical Tic-Tac-Toe Game", 3) {
    cout << "\nGame Rules:\n";
    cout << "- Player 1 uses odd numbers: 1, 3, 5, 7, 9\n";
    cout << "- Player 2 uses even numbers: 2, 4, 6, 8\n";
    cout << "- Players alternate placing one number in an empty cell\n";
    cout << "- Each number can only be used once\n";
    cout << "- Win by placing 3 numbers in a line that sum to exactly 15\n";
    cout << "- Draw if all cells filled with no line summing to 15\n\n";
}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (uses "
        << (symbol == 1 ? "odd" : "even") << " numbers)\n";

    return new Player<int>(name, symbol, type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y, number;
    Numerical_Board* num_board = dynamic_cast<Numerical_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        set<int> available = num_board->get_available_numbers(player->get_symbol());
        cout << "\n" << player->get_name() << "'s turn\n";
        cout << "Available numbers: ";
        for (int num : available) {
            cout << num << " ";
        }
        cout << "\n";

        cout << "Enter your move:\n";
        cout << "  Row (0-2): ";
        cin >> x;
        cout << "  Column (0-2): ";
        cin >> y;
        cout << "  Number to place: ";
        cin >> number;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        set<int> available = num_board->get_available_numbers(player->get_symbol());

        auto it = available.begin();
        advance(it, rand() % available.size());
        number = *it;

        do {
            x = rand() % num_board->get_rows();
            y = rand() % num_board->get_columns();
        } while (num_board->get_board_matrix()[x][y] != 0);

        cout << "\nComputer " << player->get_name()
            << " plays number " << number
            << " at position (" << x << ", " << y << ")\n";
    }


    return new Move<int>(x, y, number);
}

Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1 (Odd numbers)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);  // Symbol 1 for odd numbers

    string name2 = get_player_name("Player 2 (Even numbers)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);  // Symbol 2 for even numbers

    return players;
}

