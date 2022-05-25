#include "./../includes/Game.hpp"

using namespace std;

//constructeur
Game::Game(){
    level = 1;
    finished = false;

    initscr();
    start_color();
    //initialisation des couleurs
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);
    //pour utiliser les directions du clavier
    keypad(stdscr, TRUE);
}

//destructeur
Game::~Game(){
    endwin();
    delete maze;
}

//proposition du menu
bool Game::ask(){ 

    init();

    char choice;
    //donner le choix entre jouer et quitter 
    if (level == 1)
        printw("\t1. commencer le jeu\n"); 
    else
        printw("\t1. continuer à jouer\n"); 
    printw("\t2. quitter le programme\n"); 
    printw("\t>> entrer votre choix : "); 
    choice = getch();
    if (choice == '2') 
        finished = true;
    return (choice == '1');
}

//getter de finished;
bool Game::getFinished(){
    return finished;
}

//appliquer les mouvements du joueur
void Game::play() {

    bool win(false);

    maze = new Maze(level);

    //position du joueur
    currentPosition[0] = 0;
    currentPosition[1] = 0;
    //position de la sortie
    finalPosition[0] = maze->getRow() - 1;
    finalPosition[1] = maze->getCol() - 1;

    
    while (1)
    {
        erase();
        //afficher le labyrinthe suivant chaque mouvements effectues par le joueur
        maze->display(currentPosition, finalPosition);

        if (win) break;

        //position temporaire pour le bon fonctionnement du deplacement du joueur
        tempPosition[0] = currentPosition[0];
        tempPosition[1] = currentPosition[1];

        int k = getch();
        //si le joueur appuie sur la direction haut du clavier
        if (k == KEY_UP)
            tempPosition[0] = currentPosition[0] - 1;
        //si le joueur appuie sur la direction bas du clavier
        else if (k == KEY_DOWN)
            tempPosition[0] = currentPosition[0] + 1;
        //si le joueur appuie sur la direction gauche du clavier
        else if (k == KEY_LEFT)
            tempPosition[1] = currentPosition[1] - 1;
        //si le joueur appuie sur la direction droite du clavier
        else if (k == KEY_RIGHT)
            tempPosition[1] = currentPosition[1] + 1;
            
        //si la position temporaire ne depasse pas la matrice 
        //et qu'elle soit sur le chemin du joueur
        if (maze->isValid(tempPosition[0], tempPosition[1]) && maze->getValue(tempPosition[0],tempPosition[1]) == 1)
        {
            //donc la position temporaire devient la position actuelle
            currentPosition[0] = tempPosition[0];
            currentPosition[1] = tempPosition[1];
        }
        //pour que le joueur ne puisse pas sortir en dehors du labyrinthe sans attendre l'arrivee 
        if (currentPosition[0] < 0)
        {
            currentPosition[0] = 0;
        }
        if (currentPosition[1] < 0)
        {
            currentPosition[1] = 0;
        }
        if (currentPosition[0] >= maze->getRow())
        {
            currentPosition[0] = maze->getRow()-1;
        }
        if (currentPosition[1] >= maze->getCol())
        {
            currentPosition[1] = maze->getCol()-1;
        }
        //en atteingnant le point d'arrivee, 
        //le joueur atteind l'objectif et quitte le stage
        if (currentPosition[0] == finalPosition[0] && currentPosition[1] == finalPosition[1])
            win = true;
    }

    attron(COLOR_PAIR(7));
	printw("*** Félicitation. ***");
	attroff(COLOR_PAIR(7));
    printw("\n\n");
    printw("\nAppuyer sur une touche pour continuer");
    getch();
    nextLevel();
    clear();
}

void Game::init() {
    printw("\n\n\t");
    attron(COLOR_PAIR(6) | A_BOLD);
    printw("MaZe.");
	attroff(COLOR_PAIR(6) | A_BOLD);
    printw("\n\n\n\n");
}

//passer au level suivant
void Game::nextLevel(){
    level++;
    delete maze;
}