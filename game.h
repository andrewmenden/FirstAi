#pragma once
#include "Network.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class Game {
private:
	int board[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
	int score = 0;
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void moveRowLeft(int* row);
	void moveRowRight(int* row);

	int getMaxTile();

	bool boardIsFull();
	bool boardIsEqual(int board2[4][4]);

	std::vector<int> findMove(std::vector<float> output);

public:
	int getScore() { return score + getMaxTile(); };
	void printBoard();
	bool loop(int move, bool print = false, std::string perPrint = "cls");
	bool loop(std::vector<float> move, bool print = false, std::string perPrint = "cls");
	void spawnTile();

	std::vector<float> boardPosition();

	Game();
};
