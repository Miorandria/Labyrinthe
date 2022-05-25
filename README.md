# Jeu de Labyrinthe

Il s’agit d’une programme console écrit en C++. Pour ce projet,  j’ai généré automatiquement des labyrinthes ayant plusieurs niveaux, permettant à l’utilisateur d’utiliser les directions du clavier pour se déplacer vers le point d’arrivée.

<!-- Un labyrinthe est un réseau de chemins souvent compliquée servant a ralentir l’arriver vers une destination. 
Le jeu de labyrinthe consiste à atteindre la case d’arrivée tout en passant par les chemins du labyrinthe.  -->

## Principe du jeu

Le jeu comporte plusieurs niveaux et pour finir un niveau, il faut déplacer le joueur jusqu’à l’arrivée grâce aux directions du clavier :

- **direction haut**= diriger le joueur vers le haut
- **direction bas** = diriger le joueur vers le bas
- **direction gauche** = diriger le joueur vers la gauche
- **direction droite** = diriger le joueur vers la droite

## Technologies utilisées

J’ai choisi d’utilis­er principalement la bibliothèque **ncurses** pour :
  - gérer facilement les évènements claviers
  - créer l'interface


## Pré-requis

- ncurses
- g++
- make (optionnel)

## Installation

Si vous etes sur linux et que vous avez `make` déjà installé, vous pouvez utiliser cette commande pour installer les dépendances:

```sh
make install
```

## Démarrage

Si vous utilisez `make`, il suffit d'utiliser la commande

```sh
make
```

sinon, vous pouvez compiler manuellement en faisant :

```sh
g++ -o ./bin/main -Wall ./src/*.cpp main.cpp -lncurses;
```

Références :

https:://arnaud-feltz.developpez.com/tutoriels/ncurses/?page=premier_pas#II-C
Algo Vol.2 – Sujets.pdf



































