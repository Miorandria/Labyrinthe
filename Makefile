main: ./bin/Maze.o ./bin/Game.o
	@reset;
	@g++ -o ./bin/main -Wall ./bin/Maze.o ./bin/Game.o main.cpp -lncurses;
	@./bin/main;
	@rm ./bin/*

./bin/Maze.o:
	@g++ -c ./src/Maze.cpp -o ./bin/Maze.o;

./bin/Game.o:
	@g++ -c ./src/Game.cpp -o ./bin/Game.o;

clean:
	@rm -r ./bin/*

install:
	@sudo apt install libncurses5-dev
	@sudo apt install libncursesw5-dev