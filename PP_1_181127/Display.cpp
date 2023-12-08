#include "Display.h"
#include "Laser.h"
#include "Map.h"
#include <iostream>

using namespace std;

Display::Display() {
	//cout << "Display: IM ALIVE \n";
	resetboard();
};

void Display::offset(int sizet) {
	x_offset = 1 + ((board_width - (3 * (sizet + 2))) / 2);
	y_offset = sizet-1;
	size = sizet;
	laser.set_size(sizet);
}

void Display::resetboard() {
	for (int x = 0; x < board_length; x++) {
		for (int y = 0; y < board_width; y++) {
			board[x][y] = 32;
		}
	};

	for (int i = 0; i < board_width; i++) {
		board[0][i] = 95;
		board[k + 1][i] = 95;
		board[board_length - 1][i] = 95;
	}
	for (int i = 0; i < board_length; i++) {
		board[i][0] = 124;
		board[i][board_width - 1] = 124;
	}
	board[0][0] = 32;
	board[0][board_width - 1] = 32;
	placemiddle(gamename, k-2);
	placemiddle(NAME, k);
};

void Display::grid(int boardsize) {
	offset(boardsize);
	char K = '#';
	if ((x_offset + (size * 3) < board_width) && ((size)+y_offset < board_length)) {      //X axis
		for (int i = 0; i < 6 + size * 3; i++) {						//bottom
			board[y_offset + size + 1][x_offset + i] = '['; i++;
			board[y_offset + size + 1][x_offset + i] = K; i++;
			board[y_offset + size + 1][x_offset + i] = ']';
		}

		for (int i = 0; i < 6 + size * 3; i++) {						//top
			board[y_offset][x_offset + i] = '['; i++;
			board[y_offset][x_offset + i] = K; i++;
			board[y_offset][x_offset + i] = ']';
		}
		//Y axis
		for (int i = 0; i < 2 + size; i++) {							//left
			int j = 0;
			board[y_offset + i][x_offset] = '['; j++;
			board[y_offset + i][x_offset + j] = K; j++;
			board[y_offset + i][x_offset + j] = ']';
		}

		for (int i = 0; i < 2 + size; i++) {                            //right
			int j = 0;
			board[y_offset + i][x_offset + (size + 1) * 3] = '['; j++;
			board[y_offset + i][x_offset + (size + 1) * 3 + j] = K; j++;
			board[y_offset + i][x_offset + (size + 1) * 3 + j] = ']';
		}
	}
	else {
		exit(0);
	}

};

void Display::printmap() {
	for (int i = 1; i < size+1; i++) {
		for (int j = 1; j<size+1; j++){
			if (laser.map.board[i][j] != 0) {
				board[y_offset + i ][x_offset + 3 * j ] = '[';
				board[y_offset + i ][x_offset + 3 * j +1] = 'O';
				board[y_offset + i ][x_offset + 3 * j +2] = ']';
			}
		}
	};
};

int Display::getsize() {
	return size;
};
void Display::menu() {
	placemiddle(A, k + 3);
	placemiddle(B, k + 4);
	placemiddle(C, k + 5);
	placemiddle(D, k + 6);
	placemiddle(E, k + 7);
	placemiddle(G, k + 8);
	placemiddle(H, k + 9);
	placemiddle(F, k + 10);
};

void Display::win() {
	resetboard();
	placemiddle(wintext, 15);
};

void Display::placemiddle(char stringy[], int x) {
	int size = strlen(stringy);
	if (size < board_width - 4) {
		for (int i = 0; i < size; i++) {
			board[x][(board_width - size + 2 * i) / 2] = stringy[i];
		}
	}
	else {
		cout << "widthtooshort";
		exit(1);
	}
};

void Display::print() {
	for (int x = 0; x < board_length; x++) {
		for (int y = 0; y < board_width; y++) {
			cout << board[x][y];
		}
		cout << "\n";
	};
};

void Display::movecursor(int y, int x) {
	board[laser.get_y()][laser.get_x()] = 32;
	laser.movecursor(y,x);
	board[laser.get_y()][laser.get_x()] = laser.current_cursor();

};



