#include <iostream>
#include "GameObject.hpp"
#include <vector>



int main() {
    GameState game = GameState(10, 10);

    game.gameStart();
    
    std::vector<Position> g = game.grid();

    GridValue gridVals[10][10];

    for (Position p : g) {
        std::cout << p.row() << p.col() << std::endl;
    }
    
    return 0;
}