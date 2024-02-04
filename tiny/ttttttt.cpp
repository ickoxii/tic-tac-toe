// The Tiny Tic-Tac-Toe Turing-complete Technoid

#include <iostream>
#include <string.h>

const int ROWS = 3;
const int COLS = 3;
const int CELLS = 9;

void draw(const int *board);
int gameOver(const int *board);
bool equals3(int a, int b, int c) {
    return a == b && b == c && a != 0;
}

int minimax(int *board, int player) {
    int winner = gameOver(board);

    if(winner != 0) {
        return winner * player;
    }

    int bestMove = -1;
    int bestScore = INT_MIN;

    for(int i = 0; i < CELLS; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int score = -1 * minimax(board, -1 * player);
            board[i] = 0;

            if(score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    if(bestMove == -1) return 0;

    return bestScore;
}

int hacks(int *board) {
    int bestMove = -1;
    int bestScore = INT_MIN;

    for(int i = 0; i < CELLS; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int score = -1 * minimax(board, -1);
            board[i] = 0;

            if(score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int main(int argc, char *argv[]) {
    std::cout << "   BOARD   \n";
    std::cout << " 1 | 2 | 3 \n";
    std::cout << "---|---|---\n";
    std::cout << " 4 | 5 | 6 \n";
    std::cout << "---|---|---\n";
    std::cout << " 7 | 8 | 9 \n\n";

    int DBG = (argc > 1 && (strcmp(argv[1], "--debug") == 0 || strcmp(argv[1], "-d") == 0)) ? true : false;

    int board[CELLS];
    for(int i = 0; i < CELLS; ++i) {
        board[i] = 0;
    }
    int moves = 0, ndx;
    const int player = -1, ai = 1;

    // Player = -1, Computer = 1
    while(moves < CELLS) {
        std::cout << "Enter your move\n";
        std::cin >> ndx;
        --ndx;

        // Make move if valid
        if(ndx >= 0 && ndx < 9 && board[ndx] == 0) {
            board[ndx] = player;
            ++moves;
            std::cout << "\n";
            draw(board);
            std::cout << "\n";

            if(DBG) {
                std::cerr << "board: ";
                for(int i = 0; i < CELLS; ++i) {
                    std::cerr << board[i] << " ";
                }
                std::cerr << "\n";
            }

            // Computers turn
            if(gameOver(board) == 0) {
                ndx = hacks(board);
                board[ndx] = ai;
                std::cout << "AI moves to cell " << ndx << "\n";
                draw(board);
                std::cout << "\n";

                if(DBG) {
                    std::cerr << "board: ";
                    for(int i = 0; i < CELLS; ++i) {
                        std::cerr << board[i] << " ";
                    }
                    std::cerr << "\n";
                }

                if(gameOver(board) != 0) {
                    break;
                }
            }
        } else {
            std::cout << "Invalid move, Enter a valid cell\n";
        }
    }

    switch(gameOver(board)) {
        case 0:
            std::cout << "Draw!\n";
            break;
        case 1:
            std::cout << "get rekt\n";
            break;
        case -1:
            std::cout << "computer got owned\n";
            break;
    }

    return 0;
}

/*
 x | o | o
---|---|---
 o | x | x
---|---|---
 o | x | x
*/
void draw(const int *board) {
    // Using rows and columns in this way gives a much more
    // native way to generate each row to print
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLS; ++c) {
            int ndx = r*3+c;

            std::cout << " ";
            if(board[ndx] == -1) {
                std::cout << "x";
            } else if(board[ndx] == 1) {
                std::cout << "o";
            } else {
                std::cout << " ";
            }
            std::cout << " ";

            // Print cell dividers
            if(c+1 < COLS)
                std::cout << "|";
        }
        std::cout << "\n";

        // Print buffer lines
        if(r+1 < ROWS) {
            std::cout << "---|---|---\n";
        }
    }
}

int gameOver(const int *board) {
    // Check rows
    for(int i = 0; i < ROWS; ++i) {
        int ndx1 = (ROWS*i)+0;
        int ndx2 = (ROWS*i)+1;
        int ndx3 = (ROWS*i)+2;

        if(equals3(board[ndx1], board[ndx2], board[ndx3])) {
            return board[ndx1];
        }
    }

    // Check columns
    for(int i = 0; i < COLS; ++i) {
        int ndx1 = (ROWS*0)+i;
        int ndx2 = (ROWS*1)+i;
        int ndx3 = (ROWS*2)+i;

        if(equals3(board[ndx1], board[ndx2], board[ndx3])) {
            return board[ndx1];
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
            return board[ndx1];
        }
    }

    return 0;
}
