#pragma once
#include "Map.h"

class Laser :public Map {
public:
	Map map;
	Laser();
	void init(int x);
	void fire();
	int get_x();
	int get_y();
	int get_x_map();
	int get_y_map();
	void movecursor(int y, int x);
	char current_cursor();
	void setcursor(int x);
	void set_size(int x);
	int getshotcount();
private:
	char icon[6] = { 'v','^','<','>','o','x' };
	int cursor_id = 0;
	int x_pos;
	int x_pos_map;
	int y_pos;
	int y_pos_map;
	int size;
	int shotcount = 0;
};
