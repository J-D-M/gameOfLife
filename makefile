CC=g++
FLAGS=-Wall -O3

gameOfLife: ./src/main.cpp ./src/world.cpp
	$(CC) -o ./bin/$@ $^ $(FLAGS)
