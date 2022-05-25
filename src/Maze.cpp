#include "./../includes/Maze.hpp"


//row=nombre de ligne
//col=nombre de colonne
int** createArray2D(int row, int col) {
    int** tab;
    tab = new int* [row];
    for (int i=0; i<row; i++){
        tab[i] = new int [col];
    }
    return tab;  
}

//constructeur
Maze::Maze(int plevel) {
    //taille du labyrinthe pour chaque level
    
    level = plevel;

	maze = nullptr;
    switch (level) {
        case(1) :
        row = 11; col =11;
        break;
        case(2) :
        row = 21; col =31;
        break;
        case(3) :
        row = 25; col =41;
        break;
        default :
        break;
    }
   
    //generer le labyrinthe
	generate();
}

//destructeur
Maze::~Maze() {
	for (int i = 0; i < row; i++) {
        delete[] maze[i];
    }
}

//donner une couleur a un case 
void Maze::color(int index) {
	attron(COLOR_PAIR(index));
	printw("  ");
	attroff(COLOR_PAIR(index));
}


//generer automatiquement un labyrinthe
void Maze::generate(){
    int max(1);
    //pour stocker les coordonnees des murs utiles au hazard
    int random[2];

	maze = createArray2D(row, col);

    //creer une matrice tel que le nombre zero(mur) forme une grille
    //le reste sont des nombres allant de 1
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i % 2 == 1 || j % 2 == 1) {
                maze[i][j] = 0;
            } else {
                maze[i][j] = max;
                max++;
            }
        }
    }

	//jusqu'a ce que tous les valeurs dans la matrice sois 0 et 1 uniquement
    while (!mazeCreationDone()) {
        //choisir aleatoirement un mur utile
        chooseUsefullWall(random);

        int typeMur = isUsefullWall(random[0], random[1]);

        if (typeMur == 2) {
            changeValueToMin(random[0], random[1]);
        } else if(typeMur == 1) {
            maze[random[0]][random[1]] = max;
            max++;
        }
        
        erase();
    }

}

// ce que l'on affiche au debut de chaque partie
void Maze::initShow() {
    printw("\n\n\t");
    attron(COLOR_PAIR(6) | A_BOLD);
    printw("MaZe.[Level %d]", level);
	attroff(COLOR_PAIR(6) | A_BOLD);
    printw("\n\n\n\n");
}

//afficher le labyrinthe ,le joueur et la sortie
void Maze::display(int player[2], int out[2]) {

    initShow();

    //pour afficher les mur exterieurs
    printw("\t");
    for (int j = 0; j < col+2; j++) {
        color(WALL);
    }
    printw("\n");
	for (int i = 0; i < row; i++) {
        printw("\t");
        color(WALL);
		for (int j = 0; j < col; j++) {
			//change la couleur de l'emplacement du joueur en sa couleur
			if (player[0] == i && player[1] == j) {
				color(PLAYER);
				continue;
			}
			//change la couleur de l'emplacement de la sortie en sa couleur
			if (out[0] == i && out[1] == j) {
				color(EXIT);
				continue;
			}
            
			if (maze[i][j] == 1) {
				color(PATH);
			} else {
				color(WALL);
			}
		}
        color(WALL);
		printw("\n");
	}
    printw("\t");
    for (int j = 0; j < col+2; j++) {
        color(WALL);
    }

	printw("\n");
    printw("\n");
}

//teste si les coordonnées ne dépassent pas
bool Maze::isValid(int x, int y) {
    return (y >= 0) && (x >= 0) && (x < row) && (y < col);
}

//determination de la valeur minimum(min) des voisins de la position donnée
int Maze::minValue(int x, int y) {
    int min = INT_MAX;
    int coordonneeVoisins[4][2] = {
        {x-1, y},
        {x, y-1},
        {x+1, y},
        {x, y+1},
    };

    for(int i=0 ; i < 4 ;i++ ) {
        int xVoisin = coordonneeVoisins[i][0];
        int yVoisin = coordonneeVoisins[i][1];
        
        if (!isValid(xVoisin, yVoisin)) {
            continue;
        }

        if (maze[xVoisin][yVoisin] < min && maze[xVoisin][yVoisin] != 0) {
            min = maze[xVoisin][yVoisin];
        }
    }
    return min;
}


//changer les valeurs qui suivent la position donnee en min
void Maze::changeValueToMin(int x, int y) {
    vector<int> ValeurAutreQueMin;
    //stocker dans un tableau les coordonnees des voisins 
    int coordonneeVoisins[4][2] = {
        {x-1, y},
        {x, y-1},
        {x+1, y},
        {x, y+1},
    };
    int min;
    min = minValue(x, y);

    for(int i=0 ; i < 4 ;i++ ) {
        int xVoisin = coordonneeVoisins[i][0];
        int yVoisin = coordonneeVoisins[i][1];

        if (!isValid(xVoisin, yVoisin)) {
            continue;
        }
    //stocker les valeur autre que la valeur de min et zero
        if (maze[xVoisin][yVoisin] != min && maze[xVoisin][yVoisin] != 0 )
            ValeurAutreQueMin.push_back(maze[xVoisin][yVoisin]);
    }

	bool isNewValue(false);

	for (auto value : ValeurAutreQueMin) {
		for(int i=0; i < row; i++)
			for(int j=0; j < col; j++)
				if(maze[i][j] == value)
					maze[i][j] = min;
	}
//changer les valeurs des coordonnees x et y en min
    maze[x][y] = min;

}

//si tous les valeurs dans la matrice ne sont plus que des 0 ou des 1
bool Maze::mazeCreationDone() {
     for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(maze[i][j] != 0 && maze[i][j] != 1)
                return false;
        }
    }
    return true;
}

//determiner si le mur est utile, soit:
//tous les 4 valeurs autours du murs sont egale a 0 ou
//le mur est entre deux ou plusieurs valeurs positives differentes
int Maze::isUsefullWall(int x, int y) {
    //si la valeur a tester est differente de zero
    if(maze[x][y] != 0) 
        return 0; 
    //nombre de voisins(valeur autour de la valeur de coordonnee x et y) (4 maximum)
    int nombreVoisin = 0;
    //stocker dans un tableau les coordonnees des voisins 
    int coordonneeVoisins[4][2] ={
        {x-1, y},
        {x, y-1},
        {x+1, y},
        {x, y+1},
    };
    //nombre des mur autour de la case a tester 
    int nombreMursVoisin(0);
    //variable different de zero qui suit la valeur de coordonnees x et y
    int pivot;
    for(int i = 0; i<4 ;i++) {
        int xVoisin = coordonneeVoisins[i][0];
        int yVoisin = coordonneeVoisins[i][1];
    //si le voisin ne depasse pas le mur
        if (!isValid(xVoisin, yVoisin)) {
            continue;
        } else {
            nombreVoisin++;
        }

        if(maze[xVoisin][yVoisin] ==0)
            nombreMursVoisin++;
        else {
            pivot = maze[xVoisin][yVoisin];
            break;
        }
    }
	//tous les voisins du mur a tester sont tous des murs
    //@commenter pour garder l'allure continue des murs du labyrinthe
	// if (nombreMursVoisin == nombreVoisin)
    //     return 1; 
   
    for(int i=0; i<4; i++) {
        int xVoisin = coordonneeVoisins[i][0];
        int yVoisin = coordonneeVoisins[i][1];
        
        if (!isValid(xVoisin, yVoisin)) {
            continue;
        }
        //un autre voisin est different du pivot     
        if (maze[xVoisin][yVoisin] != 0 && maze[xVoisin][yVoisin] != pivot){
            return 2;
        }
    }

    return 0;

}

//choisir aleatoirement un mur utile
void Maze::chooseUsefullWall(int chosen[2]) {
    
    vector<vector<int>> useFullWall;
    int choice = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            //pour la matrice au debut, si l'un des coordonnees est impaire, la valeur dans la matrice est 0
            if ((i % 2) == 1 || (j % 2) == 1) {
                //stocker les valeurs dans la matrice egale a zero(mur) et que le mur soit utile
                if (isUsefullWall(i, j)) {
                    useFullWall.push_back({ i, j });
                }
            }
        }
    }
    //choisir un nombre au hazard tel qu'il ne depasse pas le nombre de murs utiles
    choice = rand() % (useFullWall.size());
    //coordonnees suivant la ligne de la valeur prix au hazard
    chosen[0] = useFullWall[choice][0];
    //coordonnees suivant la colonne de la valeur prix au hazard
    chosen[1] = useFullWall[choice][1]; 

}
