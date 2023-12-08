#include "Laser.h"
#include "Map.h"
#include <iostream>
#define board_width 60
#define board_length 30
#define easy_atoms 8
#define hard_atoms 5

using namespace std;

void Laser::init(int x) {
	x_pos = ((board_width - (3 * (x + 2))) / 2) + 2;
	y_pos = x - 2;
	x_pos_map = 1;
	y_pos_map = 0;
	//cout << "L:INIT:X: " << x_pos << "Y: " << y_pos << endl;
};

void Laser::movecursor(int y, int x) {

	x_pos_map = x_pos_map + x;
	y_pos_map = y_pos_map + y;

	if (x_pos_map < 0 || y_pos_map < 0 || y_pos_map > size + 3 || x_pos_map > size + 3) {
		x_pos_map = x_pos_map - x;
		y_pos_map = y_pos_map - y;
		goto end;
	};

	if (x_pos_map != 0 && y_pos_map != 0 && y_pos_map != size + 3 && x_pos_map != size + 3) {
		setcursor(4);
		if (x_pos_map == 1 || y_pos_map == 1 || y_pos_map == size + 2 || x_pos_map == size + 2) {
			if (x > 0) {
				x_pos_map = x_pos_map + x;
				x++;
			};
			if (x < 0) {
				x_pos_map = x_pos_map + x;
				x--;
			};
			if (y < 0) {
				y_pos_map = y_pos_map + y;
				y--;
			};
			if (y > 0) {
				y_pos_map = y_pos_map + y;
				y++;
			};
		};
	};

	x_pos = x_pos + 3*x;
	y_pos = y_pos + y;

	end:

	if (y_pos_map == 0) {
		setcursor(0);
	};

	if (x_pos_map == (size + 3)) {
		setcursor(2);
	};

	if (x_pos_map == 0) {
		setcursor(3);
	};

	if (y_pos_map == (size + 3)) {
		setcursor(1);
	};
};


Laser::Laser() {
};

void Laser::set_size(int x) {
	size = x;
};

int Laser::get_x() {
	return x_pos;
};

int Laser::get_y() {
	return y_pos;
};

int Laser::get_x_map() {
	return x_pos_map;
};

int Laser::get_y_map() {
	return y_pos_map;
};

void Laser::setcursor(int x) {
	cursor_id = x;
}
char Laser::current_cursor() {
	return icon[cursor_id];
};

void Laser::fire() {
	bool dodge, hit, reflect;
	int x, y;
	int ent_x, ent_y;
	int dir_x = 0;
	int dir_y = 0;
	if (current_cursor() != 'o') {
		if (current_cursor() == 'v') {
			x = x_pos_map;
			ent_x = x_pos_map;
			y = y_pos_map + 1;
			ent_y = y_pos_map+1;
			dir_y = 1;
		};
		if (current_cursor() == '^') {
			x = x_pos_map;
			ent_x = x_pos_map;
			y = y_pos_map - 1;
			ent_y = y_pos_map-1;
			dir_y = 1;
		};
		if (current_cursor() == '<') {
			x = x_pos_map - 1;
			ent_x = x_pos_map-1;
			y = y_pos_map;
			ent_y = y_pos_map;
			dir_x = -1;
		};
		if (current_cursor() == '>') {
			x = x_pos_map + 1;
			ent_x = x_pos_map+1;
			y = y_pos_map;
			ent_y = y_pos_map;
			dir_x = 1;
		};
		do {
		start:
			hit = false;
			dodge = false;
			reflect = false;
			cout << x << " " << y << " \n";
			if (dir_y != 0) {
				if (map.board[y - 1][x + dir_x] == 1) {		//deflect
					dir_x = 0;
					dir_y = -1;
					dodge = true;
				};
				if (map.board[y][x + dir_x] == 1) {
					hit = true;  //hit
					goto end;
				}

				if (map.board[y + 1][x + dir_x] == 1) {
					if (dodge) {
						reflect = true;
						goto end;       //reflect
					}
					else {
						dir_x = 0;			//deflect
						dir_y = 1;
						dodge = true;
					}
				}
			}
			else {

				if (map.board[y + dir_y][x - 1] == 1) {		//deflect
					dir_x = 1;
					dir_y = 0;
					dodge = true;
				};
				if (map.board[y + dir_y][x] == 1) {
					hit = true;			//hit
				}

				if (map.board[y + dir_y][x + 1] == 1) {
					if (dodge) {
						reflect = true;
						goto end;				//reflect
					}
					else {
						dodge = true;			//deflect
						dir_x = -1;
						dir_y = 0;
					}
				}

				if (dodge) {
					goto start;
				}
				if (hit) {
					goto end;
				}
			}
			x = x + dir_x;
			y = y + dir_y;
		} while (!(x == 1 || y == 1 || x == size + 2 || y == size + 2));

	end:
		if (hit) { cout << "HIT on X: " << x << " Y: " << y << endl; };
		if (reflect) { cout << "REFLECT on X: " << ent_x << " Y: " << ent_y << endl; }
		else {
			cout << "DEFLECT on X: " << x << " Y: " << y << " TO X:" << ent_x<<" Y: "<<ent_y<< endl;
		}
	}

	else {
		cout << "invalid shot\n";
	}
};
