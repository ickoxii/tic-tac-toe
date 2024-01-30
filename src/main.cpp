#include "ai.h"
    //#include "board.h"
#include <iostream>
#include <cassert>

int main(int argc, char*argv[]) {
    Board_t board;
    bool gameOver = false;
    bool playerx = true;
    char avatar = 'x';
    char winner = '.';
    int turnCount = 0;
    const int MAX_TURNS = 9;
    int r = 0, c = 0;

    std::cout << "New game!\n";
    std::cout << "Player 'x' and Player 'o'\n";
    std::cout << "Player 'x' will begin!\n";
    std::cout << "Please enter the row and column (0-indexed)\n";
    board.print(std::cout);

    while(!gameOver && turnCount < MAX_TURNS) {
        bool iofail = false;
        // Set whoever is playing this turn
        avatar = (playerx) ? 'x' : 'o';

        ++turnCount;

        // Get player input
        do {
            iofail = false;
            std::cout << "Turn " << turnCount << "\n";
            std::cout << "Player " << ((playerx) ? "x" : "o") << " enter row and column\n";
            std::cin >> r >> c;
            if(!board.playerMove(r, c, avatar)) {
                iofail = true;
                std::cout << "Player has already played at " << r << " " << c << "\n\n";
                board.print(std::cout);
            }
        } while(iofail);
        
        // Check if game over
        winner = board.isGameOver();
        std::cout << "winner: " << winner << "\n";
        gameOver = (winner == 'x' || winner == 'o') ? true : false;

        // Print board
        board.print(std::cout);

        // Toggle current player
        playerx = !playerx;
    }

    winner = board.isGameOver();
    if(gameOver) {
        std::cout << "Congratulations! Player '" << winner << "' won!\n";
    } else {
        std::cout << "Uh oh! tie game!\n";
    }

    return 0;
}
