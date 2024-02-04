#include "../include/ai.h"
    // #include "board.h"
#include <iostream>
#include <cassert>

int main(int argc, char*argv[]) {
    Board_t board;
    AI_t ai((argc > 1) ? true : false, 'o');
    char player = 'x';

    Move_t playerMove(1, 1, player);
    board.makeMove(playerMove);

    Move_t aiMove = ai.bestMove(board);
    board.makeMove(aiMove);

    playerMove.r = 0;
    playerMove.c = 2;
    board.makeMove(playerMove);

    aiMove = ai.bestMove(board);
    assert(aiMove.r != 0 && aiMove.c != 1);

    return 0;
}
