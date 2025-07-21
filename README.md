Magic Square Game
=================
A two-player, turn-based competitive game based on the principles of a 3x3 magic square, implemented in C.

--------------------------------------------------------------------------------

🌟 PROJECT OVERVIEW
------------------

This project is a command-line, two-player game that implements the logic of a 3x3 magic square. Players take turns placing "pegs" (numbers 1 through 9) onto a 3x3 grid. The objective is to be the player who completes a row or column that sums to exactly 15. A player loses if their move completes a row or column that sums to any value other than 15. The game was developed as an exercise in translating formal logic and discrete mathematics concepts into a functional C program.


🎯 MOTIVATION
------------

The primary motivation for this project was to bridge the gap between theoretical concepts and practical application. It served to:

  * Translate Discrete Mathematics: Implement a system specified by formal logic into a working C program.
  * Practice C Fundamentals: Apply core C programming concepts, including functions, multi-dimensional arrays, pointers, and console I/O.
  * Implement Game Logic: Develop the state management and turn-based logic for a competitive two-player game.
  * Create an Interactive Application: Build a simple but complete command-line interface for user interaction.


🛠️ TECHNOLOGIES USED
-------------------

  * C: The sole programming language used for the entire application.
  * C Standard Library: Utilizes 'stdio.h' for all console input and output operations.


🚀 GETTING STARTED
-----------------

To get a local copy of this project up and running, you will need a C compiler.

### Prerequisites

  * A C compiler, such as GCC (GNU Compiler Collection), installed on your system.

### Project Structure

The entire application is contained within a single source file. The key functions are:
  * 'main()': The entry point and main game loop, which handles player turns and gets user input.
  * 'printBoard()': Renders the current state of the 3x3 grid to the console.
  * 'nextPlayerMove()': Contains the core game logic. It validates a move, places the peg, updates the sums of rows and columns, and checks for win/loss conditions.
  * 'gameOver()': Determines and prints the final winner based on the state of the game when it ends.

### Compilation

1.  Save the source code as `main.c`.
2.  Open your terminal and navigate to the directory where you saved the file.
3.  Compile the program using the following command:

        gcc main.c -o magic_square_game


🎮 USAGE
-------

After compiling the program, you can run it from your terminal.

1.  Execute the compiled file:

        ./magic_square_game

2.  How to Play:
    *   The game will announce whose turn it is (Player A or Player B).
    *   On your turn, you will be prompted to enter three numbers:
        *   Select Row (1-3)
        *   Select Column (1-3)
        *   Choose Peg (a unique number from 1-9)
    *   You must place your peg in an unoccupied cell.
    *   **Winning:** You win if your move completes a row or column that sums to exactly 15.
    *   **Losing:** You lose if your move completes a row or column that sums to any value *other than* 15. The other player wins.
