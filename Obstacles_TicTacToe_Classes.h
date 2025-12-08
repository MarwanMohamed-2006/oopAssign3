#ifndef OBSTACLES_TICTACTOE_CLASSES_H  
#define OBSTACLES_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

class Obstacles_Board : public Board<char> {
private:
    vector<pair<int, int>> obstaclePositions;

public:
    Obstacles_Board();
    ~Obstacles_Board() {}

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void add_random_obstacles();
    bool is_obstacle(int x, int y) const;
    bool is_valid_move(int x, int y) const;
    void display_with_obstacles() const;
};

class Obstacles_UI : public UI<char> {
private:
    Obstacles_Board* obsBoard;

public:
    Obstacles_UI();
    ~Obstacles_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    void set_obstacles_board(Obstacles_Board* board) { obsBoard = board; }
};

#endif
