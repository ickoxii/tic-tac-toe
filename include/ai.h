 /**
  * ai.h
  * 
  * Author: Icko Iben
  * Date Created: 01/29/2024
  * Date Last Modified: 01/29/2024
  *
  * AI that plays with most optimal move for the solved game tic-tac-toe
  */
#ifndef AI_H
#define AI_H
#include "board.h"
#include "move.h"
    // #include "move.h"
#include <fstream>

class AI_t {
private:
    char player;
    bool DBG;
    char opponent;
    std::fstream of;

    int minimax(Board_t& board_, int depth_, bool isMaxPlayer_) {
        // base case: game over
        // Scores: [ai.player = 10], [player = -10], [tie = 0]
        if(board_.checkGameOver()) {
            char winner = board_.getWinner();
            if(winner == player) return 10;
            if(winner == opponent) return -10;
            return 0;
        }

        // If we are the AI, we want to choose moves that maximizes the AI's score
        // 
        // If we are not the AI, we want to choose the moves the minimizes the AI's score
        if(isMaxPlayer_) { // we want to maximize
            if(DBG) {
                std::cout << "minimax depth_ " << depth_ << " maximizer ";
            }
            int bestScore = INT_MIN;
            for(int i = 0; i < CELLS; ++i) {
                Move_t move(i/3, i%3, player);
                if(board_.board[i] == '.') {
                    if(DBG) {
                        std::cout << "testing ndx [" << move.r << ", " << move.c << "]\n";
                    }
                    board_.board[i] = player;
                    int score = minimax(board_, depth_+1, false);
                    board_.board[i] = '.';
                    bestScore = std::max(score, bestScore);
                }
            }
            return bestScore;
        } else { // we want to minimize
            if(DBG) {
                std::cout << "minimax depth_ " << depth_ << " minimizer\n";
            }
            int bestScore = INT_MAX;
            for(int i = 0; i < CELLS; ++i) {
                Move_t move(i/3, i%3, opponent);
                if(board_.board[i] == '.') {
                    if(DBG) {
                        std::cout << "testing ndx [" << move.r << ", " << move.c << "]\n";
                    }                    
                    board_.board[i] = opponent;
                    int score = minimax(board_, depth_+1, true);
                    board_.board[i] = '.';
                    bestScore = std::min(score, bestScore);
                }
            }
            return bestScore;
        }
    }

public:
    AI_t(bool DBG_, char player_ = 'o') : player(player_), DBG(DBG_) {
        opponent = (player_ == 'o') ? 'x' : 'o';
        if(DBG) std::cout << "debugging\n";
    }

    Move_t bestMove(const Board_t& board_) {
        Board_t board(board_);                
        Move_t bestMove(player);
        int bestScore = INT_MIN;

        for(int i = 0; i < CELLS; ++i) {
            if(board.board[i] == '.') {
                // Get coordinates
                Move_t move(i/3, i%3, player);

                // board.makeMove(move);
                board.board[i] = 'x';
                int score = minimax(board, 0, false);
                // board.reMove(move);
                board.board[i] = '.';

                // Is best move?
                if(score > bestScore) {
                    bestScore = score;
                    bestMove.r = move.r;
                    bestMove.c = move.c;
                }
            }
        }

        return bestMove;
    }
};

#endif
