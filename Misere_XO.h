/**
 * @file Misere_XO.h
 * @brief Misère Tic-Tac-Toe game classes
 * @author
 * @date 2024
 *
 * Reverse rules: You LOSE if you make three in a row
 */

#ifndef Misere_XO_h
#define Misere_XO_h

#include "boardGame_Classes.h"
using namespace std;

/**
 * @class Misere_XO_Board
 * @brief Board class for Misère Tic-Tac-Toe
 */
class Misere_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol for empty cells

public:
    /**
     * @brief Constructor
     */
    Misere_XO_Board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has lost
     * @param player Pointer to the player
     * @return true if player has 3 in a row (loses), false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if board full with no loser, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game over (lose or draw), false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Check if player has won (not used in misère)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if symbol has 3 in a row
     * @param sym Symbol to check
     * @return true if 3 in a row, false otherwise
     */
    bool _3rows(char sym);

    /**
     * @brief Find best move for AI player
     * @param computer_symbol AI player symbol
     * @param human_symbol Opponent symbol
     * @return Pointer to best move
     */
    Move<char>* find_best_move(char computer_symbol, char human_symbol);

    /**
     * @brief Minimax algorithm for AI
     * @param is_maximizing Whether current player is maximizing
     * @param sym1 Symbol of player 1
     * @param sym2 Symbol of player 2
     * @return Score of the position
     */
    int minimax(bool is_maximizing, char sym1, char sym2);
};

/**
 * @class Misere_XO_UI
 * @brief UI class for Misère Tic-Tac-Toe
 */
class Misere_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    Misere_XO_UI();

    /**
     * @brief Create a player for the game
     * @param name Player name
     * @param symbol Player symbol
     * @param type Player type
     * @return Pointer to created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Get a move from the player
     * @param player Pointer to the current player
     * @return Pointer to the move made
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif