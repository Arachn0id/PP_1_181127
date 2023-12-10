#pragma once
class Map {
public:
	Map();
	int board[11][11];
	void generate(int atoms, int size);
	int score();
};




