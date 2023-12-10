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
	y_pos = x-2;
	x_pos_map = 1;
	y_pos_map = 0;
	//cout << "L:INIT:X: " << x_pos << "Y: " << y_pos << endl;
};

void Laser::movecursor(int y, int x) {

	x_pos_map = x_pos_map + x;
	y_pos_map = y_pos_map + y;
	; bool skip = false;
	if (x_pos_map < 0 || y_pos_map < 0 || y_pos_map > size + 3 || x_pos_map > size + 3) {
		x_pos_map = x_pos_map - x;
		y_pos_map = y_pos_map - y;
		skip = true;
	};




	if (!skip && x_pos_map != 0 && y_pos_map != 0 && y_pos_map != size + 3 && x_pos_map != size + 3) {
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
	if (!skip) {
		x_pos = x_pos + 3 * x;
		y_pos = y_pos + y;
	}
	

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
	bool hit=0, reflect=0,deflect1 =0,deflect=0;
	int x, y;
	int ent_x, ent_y;
	int dir_x = 0;
	int dir_y = 0;
	cout << "XY POS MAP" << endl;
	cout << x_pos_map << " "<<y_pos_map << endl;
	cout<<"--------------------" << endl;
	if (current_cursor() != 'o') {
		if (current_cursor() == 'v') {
			x = x_pos_map - 1;
			ent_x = x_pos_map - 1;
			y = y_pos_map;
			ent_y = y_pos_map;
			dir_y = 1;
		};
		if (current_cursor() == '^') {
			x = x_pos_map - 1;
			ent_x = x_pos_map - 1;
			y = y_pos_map - 2;
			ent_y = y_pos_map - 2;
			dir_y = -1;
		};
		if (current_cursor() == '<') {
			x = x_pos_map - 2;
			ent_x = x_pos_map - 2;
			y = y_pos_map - 1;
			ent_y = y_pos_map - 1;
			dir_x = -1;
		};
		if (current_cursor() == '>') {
			x = x_pos_map;
			ent_x = x_pos_map;
			y = y_pos_map - 1;
			ent_y = y_pos_map - 1;
			dir_x = 1;
		};

		do {
			deflect = false;
			deflect1 = false;
			cout << x << " " << y << " \n";
			if (dir_y != 0) {
				if (map.board[y + dir_y][x] == 1) {
					hit = true;	//hit
				}

				if (map.board[y + dir_y][x - 1] == 1) {		//deflect
					deflect1 = true;
					cout << "deflect3" << endl;
				};

				if (map.board[y + dir_y][x + 1] == 1) {
					if (deflect1) {
						reflect = true;
						//reflect
						cout << "reflect2" << endl;
					}
					else {
						cout << "deflect4" << endl;
						deflect = true;			//deflect
						dir_x = -1;
						dir_y = 0;
					};
				};
				if (deflect1) {
					dir_x = 1;
					dir_y = 0;
				}
			}
			else {
				if (map.board[y][x + dir_x] == 1) {
					hit = true;  //hit
				};
				if (map.board[y - 1][x + dir_x] == 1) {		//deflect
					deflect1 = true;
					cout << "deflect1" << endl;
				};


				if (map.board[y + 1][x + dir_x] == 1) {
					if (deflect1) {
						reflect = true;
						//reflect
						cout << "reflect1" << endl;
					}
					else {
						//deflect
						dir_y = -1;
						dir_x = 0;
						deflect = true;
						cout << "deflect1" << endl;
					};
				};
				if (deflect1) {
					dir_y = 1;
					dir_x = 0;
				}
			}

			if (!(hit || reflect)) {
				x = x + dir_x;
				y = y + dir_y;
			}
		} while (!(hit || reflect || x == 0 || y == 0 || x == size + 2 || y == size + 2));

		if (hit) {
			cout << "HIT on X: " << x + dir_x << " Y: " << y + dir_y << " X: " << ent_x << " Y: " << ent_y << endl;
			map.board[ent_y][ent_x] = 4;
		}
		else if (reflect) {
			cout << "REFLECT on X: " << ent_x << " Y: " << ent_y << endl;
			map.board[ent_y][ent_x] = 5;
		}
		else 
			if (deflect1) {
					cout << "DEFLECT on X: " << x - dir_x << " Y: " << y - dir_y << " TO X:" << ent_x << " Y: " << ent_y << endl;
				} 
				else {
					cout << "MISS ON X:" << ent_x << " Y: " << ent_y << "  X: " << x << " Y : " << y << endl;
					map.board[ent_y][ent_x] = 6 + shotcount;
					if (dir_x > 0 || dir_y > 0) {
						map.board[y-dir_y][x-dir_x] = 6 + shotcount;
					}
					else {
						map.board[y][x] = 6 + shotcount;
					}
					shotcount++;
				};
	};
	
};

int Laser::getshotcount() {
	return shotcount;
};
