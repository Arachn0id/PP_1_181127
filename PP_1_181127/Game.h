#pragma once
#include "Display.h"

class Game : public Display {
public:
	bool win = false;
	Display display;
	void move();
	char imput();
	void diff(int key);
	void start();
	Game();
private:
	bool menu = true;
	bool help = false;
};

