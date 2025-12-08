//--------------------------------------- //
#include <iostream>
#include <ctime>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Numerical_TicTacToe_Classes.h"
#include "Tic_Tac_Toe.h"
#include "Four4_Board.h"
#include "Four4_UI.h"
#include "Pyramid_Board.h"
#include "Pyramid_UI.h"
#include "Misere_XO.h"

using namespace std;

int main() {
    system("cls");

    srand(static_cast<unsigned int>(time(0)));

    int choice = 0;

    do {
        cout << "\n==============================\n";
        cout << " FCAI Board Games Menu \n";
        cout << "==============================\n";
        cout << "1. Tic-Tac-Toe (X-O)\n";
        cout << "2. SUS\n";
        cout << "3. Four-in-a-Row\n";
        cout << "4. 5x5 Tic-Tac-Toe\n";
        cout << "5. Word Tic-Tac-Toe\n";
        cout << "6. Misere Tic-Tac-Toe\n";
        cout << "7. Diamond Tic-Tac-Toe\n";
        cout << "8. 4x4 Tic-Tac-Toe\n";
        cout << "9. Pyramid Tic-Tac-Toe\n";
        cout << "10. Numerical Tic-Tac-Toe (Group)\n";
        cout << "11. Obstacles Tic-Tac-Toe (Group)\n";
        cout << "12. Infinity Tic-Tac-Toe (Group)\n";
        cout << "13. Ultimate Tic-Tac-Toe (Bonus)\n";
        cout << "14. Memory Tic-Tac-Toe (Bonus)\n";
        cout << "15. Exit\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1: {
            UI<char>* game_ui = new XO_UI();
            Board<char>* xo_board = new X_O_Board();
            Player<char>** players = game_ui->setup_players();
            GameManager<char> x_o_game(xo_board, players, game_ui);
            x_o_game.run();

            delete xo_board;
            for (int i = 0; i < 2; ++i)
                delete players[i];
            delete[] players;
            break;
        }
        case 2:
            cout << "\n=== SUS Game ===\n";
            break;

        case 3:
            cout << "\n=== Four-in-a-Row ===\n";
            break;

        case 4:
        {
            UI<char>* game_ui = new TicTacToe_UI();
            Board<char>* tic5_board = new TicTacToe_Board();
            Player<char>** players = game_ui->setup_players();
            GameManager<char> tic5_game(tic5_board, players, game_ui);
            tic5_game.run();

            delete tic5_board;
            for (int i = 0; i < 2; ++i)
                delete players[i];
            delete[] players;
            break;
        }
        case 5:
            cout << "\n=== Word Tic-Tac-Toe ===\n";
            break;

        case 6:
        {
			UI<char>* game_ui = new Misere_XO_UI();
			Board<char>* misere_board = new Misere_XO_Board();
			Player<char>** players = game_ui->setup_players();
			GameManager<char> misere_game(misere_board, players, game_ui);
            misere_game.run();

        }
        case 7:
           /*UI<char>*game_ui = new ();
            Board<char>* diamond_board = new ();
            Player<char>** players = game_ui->setup_players();
            GameManager<char> diamond_game(diamond_board, players, game_ui);
            diamond_game.run();*/


        case 8:
            {
             UI<char>* game_ui = new Four4_UI();
             Board<char>* four4_board = new Four4_Board();
             Player<char>** players = game_ui->setup_players();
             GameManager<char> four4_game(four4_board, players, game_ui);
             four4_game.run();

              delete four4_board;
              for (int i = 0; i < 2; ++i) delete players[i];
              delete[] players;
              delete game_ui;
         break;
            
        }
        case 9:
            {
         UI<char>* game_ui = new Pyramid_UI();
         Board<char>* pyr_board = new Pyramid_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> pyr_game(pyr_board, players, game_ui);
         pyr_game.run();

        delete pyr_board;
        for (int i = 0; i < 2; ++i) delete players[i];
         delete[] players;
         delete game_ui;
         break;
            
        }
        case 10:
        {
            UI<int>* game_ui = new Numerical_UI();
            Board<int>* num_board = new Numerical_Board();
            Player<int>** players = game_ui->setup_players();
            GameManager<int> num_game(num_board, players, game_ui);
            num_game.run();

            delete num_board;
            for (int i = 0; i < 2; ++i)
                delete players[i];
            delete[] players;
            delete game_ui;
            break;
        }
        case 11:
		{
            cout << "\n=== Obstacles Tic-Tac-Toe (Group) ===\n";
    
            Obstacles_UI* ui = new Obstacles_UI();
            Obstacles_Board* board = new Obstacles_Board();
    
            ui->set_obstacles_board(board);
    
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();
    
           delete board;
           for (int i = 0; i < 2; ++i) delete players[i];
           delete[] players;
           delete ui;
           break;
       }

        case 12:
            cout << "\n=== Infinity Tic-Tac-Toe (Group) ===\n";
            break;

        case 13:
            cout << "\n=== Ultimate Tic-Tac-Toe (Bonus) ===\n";
            break;

        case 14:
            cout << "\n=== Memory Tic-Tac-Toe (Bonus) ===\n";
            break;

        case 15:
            cout << "GoodBye\n";
            break;

        default:
            cout << "Invalid choice, try again!\n";
            break;
        }
    } while (choice != 15);
    return 0;
}
