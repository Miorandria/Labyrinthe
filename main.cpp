/*
  Jeu de labyrinthe
  ANDRIAMIADANJATO Mioraniaina 
 */

#include "./includes/Game.hpp"
#include <ctime>
#include <stdlib.h>
using namespace std;

int main(int argc, char const *argv[]) {
    srand(time(0));
    Game game;

    while (!game.getFinished()) {
        if (game.ask()) {
            game.play();
        }
    }

    printw("MERCI !");
    return 0;
}
