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
#include <climits>

class AI_t {
private:
    char player;
    bool DBG;
    char opponent;
    std::fstream of;

    int minimax(Board_t& board_, char player_) {
        Move_t bestMove(-1, -1, player_);
        int bestScore = INT_MIN;

        if(board_.checkGameOver()) {
            char winner = board_.getWinner();
            if(winner == player) {
                return 10;
            } else if(winner == opponent) {
                return -10;
            }
            return 0;
        }
        
        for(int i = 0; i < CELLS; ++i) {
            if(board_.at(i) != player && board_.at(i) != opponent) {
                board_.set(i, player_);
                int score = minimax(board_, (player_ == player) ? opponent : player);

                if(score > bestScore) {
                    bestMove.r = i/3;
                    bestMove.c = i%3;
                    bestScore = score;
                }

                board_.set(i, '.');
            }
        }

        if(bestMove.r == -1 || bestMove.c == -1) return 0;

        return bestScore;
    }

public:
    AI_t(bool DBG_, char player_ = 'o') : player(player_), DBG(DBG_) {
        opponent = (player_ == 'o') ? 'x' : 'o';
        if(DBG) std::cerr << "debugging\n";
    }

    Move_t bestMove(const Board_t& board_) {
        Board_t board(board_);                
        Move_t bestMove(-1, -1, player);
        int bestScore = INT_MIN;

        for(int i = 0; i < CELLS; ++i) {
            if(board.board[i] == '.') {
                // Get coordinates
                Move_t move(i/3, i%3, player);

                board.set(i, player);
                int score = minimax(board, opponent);
                board.set(i, '.');

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
