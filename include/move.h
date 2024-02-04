#ifndef MOVE_H
#define MOVE_H

 /**
  * File: move.h
  * Author: Icko Iben
  * Date Created: 01/31/2024
  * Date Last Modified: 01/31/2024
  *
  * Standard move for a tic-tac-toe game. Stores an player, row, and column.
  */

struct Move_t {
public:
    int r, c;
    char player;
    
    Move_t() {
        r = c = 0;
        player = '.';
    }

    Move_t(int r_ = 0, int c_ = 0, char player_ = '.') {
        r = r_;
        c = c_;
        player = player_;
    }

    Move_t(char player_) : player(player_) {
        r = c = 0;
    }
};

#endif
