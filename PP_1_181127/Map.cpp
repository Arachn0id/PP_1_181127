#include "Map.h"
#include <ctime>
#include <cstdlib>

using namespace std;

void Map::generate(int atoms, int size) {
	srand(time(NULL));
	for (int x = 0; x < 11; x++) {
		for (int y = 0; y < 11; y++) {
			board[x][y] = 0;
		}
	};

	for (int i = 0; i < atoms; i++) {
		int x = (rand() % size )+1;
		int y = (rand() % size )+1;
		if (board[x][y] != 1) {
			board[x][y] = 1;
		}
		else {
			i--;
		}
	}

};

int Map::score() {
	int score =0;
	for (int x = 0; x < 11; x++) {
		for (int y = 0; y < 11; y++) {
			if (board[x][y] == 3) {
				score++;
			}
		}
	};
	return score;
}

Map::Map() {

};

