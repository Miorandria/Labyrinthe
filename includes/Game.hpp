#ifndef GAME_HPP
#define GAME_HPP

#include "./../includes/Maze.hpp"

class Game {

    public:
        Game();
        ~Game();
        //demander si l'utilisateur veut jouer ou pas
        bool ask();
        //getter de finished;
        bool getFinished();
        //jouer jusqu'a ce que l'utilisateur trouve la sortie
        void play();
        //passer au labyrinthe suivant
        void nextLevel();
        //ce que l'on affiche au debut
        void init();

    private:
        //niveau actuel
        int level;
        //le labyrinthe actuel
        Maze *maze;
         //pour indiquer que le jeux s'arrete
        bool finished;
        //position du joueur actuelle
        int currentPosition[2];
        //position temporaire, encore à tester 
        int tempPosition[2];
        //position finale
        int finalPosition[2];
};

#endif
