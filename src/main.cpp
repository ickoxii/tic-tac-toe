#include "../include/ai.h"
    // #include "board.h"
        // #include "move.h"
#include <iostream>
#include <fstream>
#include <cassert>

void logmove(std::fstream& of, Move_t move) {
    of << "Player " << move.player << " [" << move.r << ", " << move.c << "]\n";
}

int main(int argc, char*argv[]) {
    Board_t board;
    bool gameOver = false;
    bool playerFirst = true;
    char player = 'x';
    char winner = '.';
    char choice;
    int turn = 0;

    bool DBG = (argc > 1) ? true : false;
    AI_t ai(DBG, 'o');

    std::fstream of("logs/moves.log", std::ios::out);
    
    // Check if player goes first
    std::cout << "New game!\n";
    std::cout << "Would you like to go first? (y/n)\n";
    std::cin >> choice;
    if(choice == 'n' || choice == 'N') {
        playerFirst = false;
    } else {
        board.print(std::cout);
    }
    std::cout << "You are player x\n";

    while(!gameOver) {
        if(!playerFirst) {
            Move_t move = ai.bestMove(board);
            logmove(of, move);
            if(!board.makeMove(move)) {
                std::cout << "AI failed to make move on turn " << turn << "\n";
                std::cout << "Move [r,c]: [" << move.r << ", " << move.c << "\n";
                return 69;
            }
            board.print(std::cout);
            gameOver = board.checkGameOver();
            if(!gameOver) ++turn;
            else winner = 'o';
        }

        if(!gameOver) {
            bool valid = false;
            do {
                std::cout << "Enter a row and column to move (i.e. 1 2): ";
                int r, c;
                std::cin >> r >> c;
                Move_t move(r, c, player);
                valid = board.makeMove(move);
                if(valid) {
                    logmove(of, move);
                }
            } while(!valid);

            gameOver = board.checkGameOver();
            if(!gameOver) ++turn;
            else winner = 'x';
        }

        if(playerFirst && !gameOver) {
            Move_t move = ai.bestMove(board);
            logmove(of, move);
            if(!board.makeMove(move)) {
                std::cout << "AI failed to make move on turn " << turn << "\n";
                std::cout << "Move [r,c]: [" << move.r << ", " << move.c << "\n";
                return 69;
            }
            board.print(std::cout);
            gameOver = board.checkGameOver();
            if(!gameOver) ++turn;
            else winner = 'o';
        }
    }

   
    if(gameOver) {
        of << "winner: " << ((winner == 'x') ? "player" : "ai") << "\n";
        if(winner == 'x') {
            board.print(std::cout);
            std::cout << "Congrats! You won!\n";
        } else {
            std::cout << "You lost... you loser\n";
        }
    } else {
        std::cout << "Uh oh! tie game!\n";
    }

    of.close();

    return 0;
}
