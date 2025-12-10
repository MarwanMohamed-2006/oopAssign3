# 🎮 Board Games Collection

A comprehensive C++ implementation of 13 different board game variants using Object-Oriented Programming principles, developed as part of CS213: Object Oriented Programming course at Cairo University, Faculty of Computers and Artificial Intelligence.


## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Games Included](#games-included)
- [Architecture](#architecture)
- [Getting Started](#getting-started)
- [How to Play](#how-to-play)
- [AI Implementation](#ai-implementation)
- [Team Members](#team-members)
- [Documentation](#documentation)
- [Screenshots](#screenshots)

## 🎯 Overview

This project showcases the power of Object-Oriented Programming (OOP) by implementing a flexible, extensible framework for board games. The framework demonstrates key OOP principles including:
- **Abstraction**: Generic base classes for Board, Player, and UI
- **Polymorphism**: Virtual functions for game-specific behavior
- **Inheritance**: Specialized game classes extending the framework
- **Encapsulation**: Protected game state and public interfaces

## ✨ Features

- 🎲 **13 Unique Games**: From classic Tic-Tac-Toe variants to complex games like Ultimate Tic-Tac-Toe
- 🤖 **AI Players**: Smart computer opponents using Minimax and strategic algorithms
- 🎨 **Clean UI**: Console-based interface with clear board visualization
- 🔧 **Extensible Framework**: Easy to add new games by inheriting base classes
- 👥 **Multiplayer Support**: Play against friends or challenge the computer
- 📊 **Comprehensive Documentation**: Full Doxygen-generated API documentation

## 🎮 Games Included

### Individual Games (1-8)
1. **SUS** - Form "S-U-S" sequences on a 3×3 grid
2. **Four-in-a-Row** - Connect four marks in a 6×7 grid
3. **5×5 Tic-Tac-Toe** - Score the most three-in-a-row patterns
4. **Word Tic-Tac-Toe** - Create valid 3-letter words to win
5. **Misère Tic-Tac-Toe** - Inverse rules - avoid three in a row!
6. **Diamond Tic-Tac-Toe** - Win by completing two lines simultaneously
7. **4×4 Tic-Tac-Toe** - Move tokens to align three in a row
8. **Pyramid Tic-Tac-Toe** - Play on a pyramid-shaped board

### Group Games (9-11)
9. **Numerical Tic-Tac-Toe** - Use numbers that sum to 15
10. **Obstacles Tic-Tac-Toe** - Dynamic obstacles appear each round
11. **Infinity Tic-Tac-Toe** - Oldest marks disappear after 3 moves

### Bonus Games (12-13)
12. **Ultimate Tic-Tac-Toe** - A meta-game with 9 sub-boards
13. **Memory Tic-Tac-Toe** - Hidden marks test your memory

## 🏗️ Architecture

The project uses a template-based framework with the following core classes:

```
BoardGame_Classes.h
├── Board<T>           (Abstract base class)
├── Move<T>            (Concrete move representation)
├── Player<T>          (Player management)
├── UI<T>              (Abstract user interface)
└── GameManager<T>     (Game flow controller)
```

### Class Hierarchy

```cpp
// Each game extends the framework
class SUS_Board : public Board<char>
class Diamond_Board : public Board<char>
class Numerical_Board : public Board<int>
// ... and so on
```

### Design Patterns Used
- **Template Method Pattern**: Base classes define game flow
- **Strategy Pattern**: Different AI algorithms for different games
- **Factory Pattern**: Player and UI creation

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++11 support or higher (GCC, Clang, MSVC)
- Standard Template Library (STL)

### Compilation

```bash
# Compile all source files
g++ -std=c++11 main.cpp SUS.cpp Tic_Tac_Toe.cpp Misere_XO.cpp \
    Word_Tic-tac-toe.cpp diamond.cpp Four4_Board.cpp Four4_UI.cpp \
    Pyramid_Board.cpp Pyramid_UI.cpp Numerical_TicTacToe_Classes.cpp \
    Obstacles_TicTacToe_Classes.cpp Infinity_UI.cpp Ultimate_XO.cpp \
    XO_Classes.cpp -o BoardGames

# Run the program
./BoardGames
```

### File Structure

```
project/
│
├── main.cpp                              # Main menu and game launcher
├── BoardGame_Classes.h                   # Core framework
│
├── Game Implementations/
│   ├── SUS.cpp / SUS.h
│   ├── Tic_Tac_Toe.cpp / Tic_Tac_Toe.h
│   ├── Misere_XO.cpp / Misere_XO.h
│   ├── Word_Tic-tac-toe.cpp / Word_Tic-tac-toe.h
│   ├── diamond.cpp / diamond.h
│   ├── Four4_Board.cpp / Four4_Board.h / Four4_UI.cpp / Four4_UI.h
│   ├── Pyramid_Board.cpp / Pyramid_Board.h / Pyramid_UI.cpp / Pyramid_UI.h
│   ├── Numerical_TicTacToe_Classes.cpp / .h
│   ├── Obstacles_TicTacToe_Classes.cpp / .h
│   ├── Infinity_Board.h / Infinity_UI.cpp
│   ├── Ultimate_XO.cpp / Ultimate_XO.h
│   └── XO_Classes.cpp / XO_Classes.h
│
├── dic.txt                               # Dictionary for Word Tic-Tac-Toe
└── README.md
```

## 🎲 How to Play

1. **Launch the Program**: Run the executable to see the main menu
2. **Select a Game**: Choose from 13 available games (0-13)
3. **Set Up Players**: Enter player names and choose Human or Computer opponent
4. **Play**: Follow on-screen instructions for move input
5. **Win Conditions**: Each game has unique winning rules displayed at start

### Input Format
- Most games use row and column coordinates (e.g., `0 2` for row 0, column 2)
- Numerical Tic-Tac-Toe uses number selection
- 4×4 Tic-Tac-Toe uses destination coordinates for token movement

## 🤖 AI Implementation

### Games with Smart AI
- **Diamond Tic-Tac-Toe**: Minimax algorithm with depth-limited search
- **Infinity Tic-Tac-Toe**: Strategic positioning with win/block detection
- **Additional AI Players**: Available for individual game assignments

### AI Strategies
1. **Winning Move Detection**: Prioritize immediate wins
2. **Block Opponent**: Prevent opponent victories
3. **Strategic Positioning**: Center control and corner preference
4. **Minimax Algorithm**: Look-ahead game tree search (depth 3-5)

## 👥 Team Members :
Marwan Mohamed Ahmed Awad
Marwan Tarek Hegazy 
Ali Samy Mohamed
Mohamed hassan Moussa 


### Key Classes Documentation

- **Board\<T\>**: Abstract base class for all game boards
- **Player\<T\>**: Manages player information and board access
- **UI\<T\>**: Handles user interaction and display
- **GameManager\<T\>**: Controls game flow and turn management


### Adding a New Game

1. Create board class inheriting from `Board<T>`
2. Implement required virtual methods:
   - `update_board()`
   - `is_win()`
   - `is_draw()`
   - `game_is_over()`
3. Create UI class inheriting from `UI<T>`
4. Implement `get_move()` and `create_player()`
5. Add game case to main menu

### Code Quality
- ✅ Follows OOP principles (A PIE)
- ✅ Well-commented and documented
- ✅ Memory management with proper cleanup
- ✅ Input validation and error handling

## 📜 License

This project is part of academic coursework for CS213 at Cairo University, Faculty of Computers and Artificial Intelligence.

**Academic Integrity**: This code is for educational purposes. Copying or using this code for your own assignments violates academic integrity policies.

## 🙏 Acknowledgments

- **Dr. Mohammad El-Ramly** - Course Instructor
- Cairo University, Faculty of Computers and Artificial Intelligence
- CS213: Object Oriented Programming Course

**Note**: This project demonstrates advanced C++ programming concepts including templates, inheritance, polymorphism, and AI algorithms. All code is original work completed as part of academic requirements.
