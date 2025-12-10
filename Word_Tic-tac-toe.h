/**
 * @file Word_Tic-tac-toe.h
 * @brief Word Tic-Tac-Toe game classes
 * @author
 * @date 2024
 *
 * Players place letters to form English words from a dictionary
 * First player to form a valid 3-letter word wins
 */

#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <unordered_set>
#include <string>
using namespace std;

/**
 * @class WordTicTacToe_Board
 * @brief Board class for Word Tic-Tac-Toe
 */
class WordTicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';          ///< Symbol for empty cells
    vector<vector<char>> rb;          ///< Reference board (for display)

public:
    /**
     * @brief Constructor
     */
    WordTicTacToe_Board();

    /**
     * @brief Update board with a move
     * @param move Pointer to the move
     * @return true if move successful, false otherwise
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Check if player has formed a valid word
     * @param player Pointer to the player
     * @return true if player formed a dictionary word, false otherwise
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Check if player has lost (not used)
     * @param player Pointer to the player
     * @return Always returns false
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Check if game is a draw
     * @param player Pointer to the player
     * @return true if board full with no valid words, false otherwise
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Check if game is over
     * @param player Pointer to the player
     * @return true if game over (win or draw), false otherwise
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Load dictionary from file
     */
    static void loadDictionary();

    /**
     * @brief Dictionary of valid 3-letter words
     */
    static unordered_set<string> dictionary;

    /**
     * @brief Print current board state
     */
    void printBoard();
};

/**
 * @class WordTicTacToe_UI
 * @brief UI class for Word Tic-Tac-Toe
 */
class WordTicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructor
     */
    WordTicTacToe_UI() : UI<char>("Welcome to Word Tic-Tac-Toe!", 3) {}

    /**
     * @brief Destructor
     */
    ~WordTicTacToe_UI() {};

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