#include "../include/board.h"
#include "../include/ai.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Board_t board;
    char choice = 'y';
    int r, c;

    while(choice != 'q') {
        std::cout << "m to move, r to remove: ";
        std::cin >> choice;
        switch(choice) {
            case 'm': {
                std::cin >> r >> c;
                Move_t move(r, c, 'x');
                board.makeMove(move);
                board.print(std::cout);
                break;
            }
            case 'r': {
                std::cin >> r >> c;
                Move_t move(r, c, 'x');
                board.reMove(move);
                board.print(std::cout);
                break;
            }
            default: {
                choice = 'q';
                break;
            }
        }
    }

    return 0;
}
