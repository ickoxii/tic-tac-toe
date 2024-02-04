#ifndef BOARD_H
#define BOARD_H

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
#include "move.h"
#include <iostream>

const int ROWS = 3;
const int COLS = 3;
const int CELLS = 9;
const int LINE_WIDTH = 12;

class Board_t {
private:
    char *board;
    char winner;

    bool equals3(char a, char b, char c) {
        return a == b && a == c && a != '.';
    }

    void set(int ndx, char move) { board[ndx] = move; }
    char at(int ndx) { return board[ndx]; }

    friend class AI_t;
    
public:
    // Initialize the board with '.'
    Board_t() {
        board = new char[CELLS];
        for(int i = 0; i < CELLS; ++i) {
            board[i] = '.';
        }
        winner = '.';
    }

    // Copy constructor
    Board_t(const Board_t& newBoard) {
        board = new char[CELLS];
        for(int i = 0; i < CELLS; ++i) {
            board[i] = newBoard.board[i];
        }
        winner = newBoard.winner;
    }

    // Overloaded assignment operator
    Board_t& operator==(const Board_t& newBoard) {
        if(this == &newBoard) return *this;

        // Deallocate board if needed
        if(board) delete[] board;

        board = new char[CELLS];
        for(int i = 0; i < CELLS; ++i) {
            board[i] = newBoard.board[i];
        }

        winner = newBoard.winner;

        return *this;
    }

    // Destroy the board
    ~Board_t() {
        delete[] board;
    }

    // Return board
    char* getBoard() const {
        return board;
    }

    char getWinner() const {
        return winner;
    }

    /*
     x | o | o
    ---|---|---
     o | x | x
    ---|---|---
     o | x | x
    */
    void print(std::ostream &os) const {
        // Using rows and columns in this way gives a much more
        // native way to generate each row to print
        os << "   0   1   2 \n";
        for(int r = 0; r < ROWS; ++r) {
            os << r << " ";
            for(int c = 0; c < COLS; ++c) {
                int ndx = r*3+c;
                os << " ";
                if(board[ndx] == 'x' || board[ndx] == 'o')
                    os << board[ndx];
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
                os << "  ---|---|---\n";
        }
    }

    // Get a player move and put it on the board
    // Return false if fails to insert
    bool makeMove(const Move_t& move) {
        int ndx = move.r*3+move.c;
        if(board[ndx] == 'x' || board[ndx] == 'o') return false;
        board[ndx] = move.player;
        return true;
    }

    // Game over?
    // Returns 'x' or 'o' if that player has won
    // Otherwise returns '.'
    bool checkGameOver() {
        // Check rows
        for(int i = 0; i < ROWS; ++i) {
            int ndx1 = (3*i)+0;
            int ndx2 = (3*i)+1;
            int ndx3 = (3*i)+2;

            if(equals3(board[ndx1], board[ndx2], board[ndx3])) {
                winner = board[ndx1];
                return true;
            }
        }

        // Check columns
        for(int i = 0; i < COLS; ++i) {
            int ndx1 = (3*0)+i;
            int ndx2 = (3*1)+i;
            int ndx3 = (3*2)+i;

            if(equals3(board[ndx1], board[ndx2], board[ndx3])) {
                winner = board[ndx1];
                return true;
            }
        }

        // Check diagonals
        for(int i = 0; i < 2; ++i) {
            // Gives top-left to bottom-right diagonal on the first iteration
            // and bottom-left to top-right diagonal on the second iteration
            int ndx1 = (4 / (i+1)) * (i+0);
            int ndx2 = (4 / (i+1)) * (i+1);
            int ndx3 = (4 / (i+1)) * (i+2);

            if(equals3(board[ndx1], board[ndx2], board[ndx3])) {
                // return board[ndx1];
                winner = board[ndx1];
                return true;
            }
        }

        int open = 0;
        for(int i = 0; i < CELLS; ++i) {
            if(board[i] == '.') {
                ++open;
            }
        }

        // Game is over but no winner, tie
        if(open == 0) {
            return true;
        }

        return false;
    }
};

#endif
