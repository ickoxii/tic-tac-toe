 /**
  * board.h
  *
  * Author: Icko Iben
  * Date Created: 01/29/2024
  * Date Last Modified: 01/29/2024
  *
  * Board for playing tic-tac-toe.
  * 
  * Supported Operations
  *     [x] Saves board state (which character played where)
  *     [x] Print board
  *     [x] Get player's input
  *     [x] Determine if game is over
  */
#include <iostream>

const int ROWS = 3;
const int COLS = 3;
const int LINE_WIDTH = 12;

class Board_t {
private:
    char **board;

public:
    // Initialize the board with '.'
    Board_t() {
        board = new char*[ROWS];
        for(int r = 0; r < ROWS; ++r) {
            board[r] = new char[COLS];
            for(int c = 0; c < COLS; ++c) {
                board[r][c] = '.';
            }
        }
    }

    // Copy constructor
    Board_t(const Board_t& newBoard) {
        board = new char*[ROWS];
        for(int r = 0; r < ROWS; ++r) {
            board[r] = new char[COLS];
            for(int c = 0; c < COLS; ++c) {
                board[r][c] = newBoard.board[r][c];
            }
        }
    }

    // Overloaded assignment operator
    Board_t& operator==(const Board_t& newBoard) {
        if(this == &newBoard) return *this;

        // Deallocate board if needed
        if(board) {
            for(int i = 0; i < ROWS; ++i) {
                delete[] board[i];
            }
            delete[] board;
        }

        board = new char*[ROWS];
        for(int r = 0; r < ROWS; ++r) {
            board[r] = new char[COLS];
            for(int c = 0; c < COLS; ++c) {
                board[r][c] = newBoard.board[r][c];
            }
        }

        return *this;
    }

    // Destroy the board
    ~Board_t() {
        for(int r = 0; r < ROWS; ++r) {
            delete[] board[r];
        }
        delete[] board;
    }

    // Return board
    char** getBoard() const {
        return board;
    }

    /*
     x | o | o
    ---|---|---
     o | x | x
    ---|---|---
     o | x | x
    */
    void print(std::ostream &os) {
        for(int r = 0; r < ROWS; ++r) {
            for(int c = 0; c < COLS; ++c) {
                os << " ";
                if(board[r][c] == 'x' || board[r][c] == 'o')
                    os << board[r][c];
                else
                    os << " ";
                os << " ";

                // Print cell dividers
                if(c+1 < COLS)
                    os << "|";
            }
            os << "\n";

            // Print buffer lines
            if(r+1 < ROWS)
                os << "---|---|---\n";
        }
    }

    // Get a player move and put it on the board
    // Return false if fails to insert
    bool playerMove(int r, int c, char move) {
        if(board[r][c] == 'x' || board[r][c] == 'o') return false;

        board[r][c] = move;
        return true;
    }

    // Only check rows and columns and/or diagonals that the move is played in
    // Returns 'x' or 'o' if that player has won
    // Otherwise returns '.'
    /*
       // NOT WORKING AS EXPECTED
    char optimizedGameOverCheck(int r, int c) {
        // Check the row 
        if(board[r][0] == board[r][1] && board[r][0] == board[r][2])
            return board[r][c];

        // Check the column
        if(board[0][c] == board[1][c] && board[0][c]  == board[2][c])
            return board[r][c];

        // Only check diagonals if in a cell that supports diagonals
        // This skips all cells not on the diagonal
        if((r+c)%2 == 0) {
            bool fd = false, sd = false;
            if(r == 1 && c == 1) {
                fd = true;
                sd = true;
            }
            if(r == 0) {
                if(c == 0)
                    fd = true;
                if(c == 2)
                    sd = true;
                // fd = (c == 0);
                // sd = (c == 2);
            }
            if(r == 2) {
                if(c == 2)
                    fd = true;
                if(c == 0)
                    sd = true;
                // fd = (c == 2);
                // sd = (c == 0);
            }

            // Increment rows, increment columns
            if(fd)
                return board[0][0] == board[1][1] && board[1][1] == board[2][2];
            // Decrement rows, increment columns
            if(sd)
                return board[2][0] == board[1][1] && board[1][1] == board[0][2];
        }

        return '.';
    }
    */
    // Game over?
    // Returns 'x' or 'o' if that player has won
    // Otherwise returns '.'
    char isGameOver() {
        // Check columns
        for(int c = 0; c < COLS; ++c)
            if((board[0][c] == board[1][c] && board[0][c] == board[2][c]) && board[1][c] != '.')
                return board[1][c];

        // Check rows
        for(int r = 0; r < ROWS; ++r)
            if((board[r][0] == board[r][1] && board[r][0] == board[r][2]) && board[r][1] != '.')
                return board[r][1];

        // Check diagonals
        if((board[0][0] == board[1][1] && board[0][0] == board[2][2]) && board[1][1] != '.')
            return board[1][1];
        if((board[0][2] == board[1][1] && board[0][0] == board[2][0]) && board[1][1] != '.')
            return board[1][1];

        return '.';
    }
};
