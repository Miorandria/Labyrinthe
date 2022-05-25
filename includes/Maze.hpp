#ifndef MAZE_HPP
#define MAZE_HPP
#include <ncurses.h>
#include <vector>
#include <ncurses.h>
#include <limits.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

enum ColorCase { TEMP, WALL, PATH, PLAYER, EXIT };

int **createArray2D(int row, int col);

class Maze {
	public:
		Maze(int plevel);
		~Maze();
		//donner une couleur a un case 		
		void color(int index);
		// génère le labyrinthe étant donné les row et col définies
		void generate();
		// ce que l'on affiche au debut de chaque partie
		void initShow();
		// affiche le labyrinthe et les objets passés en paramètre
		void display(int player[2], int out[2]);
		// getter pour la valeur en i,j
		int getValue(int i, int j) {
			return maze[i][j];
		}
		// getter pour row
		int getRow() { return row; }
		// getter pour col
		int getCol() { return col; }

		/// methodes liées à la génération
		// teste si les coordonnées ne dépassent pas
		bool isValid(int x, int y);
		// determination de la valeur minimum des voisins de la position donnée
		int minValue(int x, int y);
		// changer les valeurs qui suivent la position donnee en min
		void changeValueToMin(int x, int y);
		// si tous les valeurs dans la matrice ne sont plus que des 0 ou des 1
		bool mazeCreationDone();
		// determiner si le mur est utile
		int isUsefullWall(int x, int y);
		// choisir aleatoirement un mur utile
		void chooseUsefullWall(int chosen[2]);

	private:
		// le labyrinthe actuel
		int **maze;
		// taille du labyrinthe(row=nombre de ligne)(col=nombre de colonne)
		int row, col;
		// le level courant
		int level;
};

#endif
