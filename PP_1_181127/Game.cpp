#include "Game.h"
#include "Display.h"
#include <iostream>
using namespace std;

#define board_width 60
#define board_length 30
#define easy_atoms 5
#define hard_atoms 8

Game::Game() {
	cout << "Game: IM ALIVE \n";
	display.menu();
	cout << "--------------- \n";
	display.print();
	start();
};

char Game::imput() {
	unsigned char keyboard;
	cin>>keyboard;
	if (keyboard == 51) {
		exit(0);
	}
	else return keyboard;
}

void Game::move() {
	int key = imput();
	if (key == 'w') {
		display.movecursor(-1, 0);
	}
	else if (key == 's') {
		display.movecursor(1, 0);
	}
	else if (key == 'a') {
		display.movecursor(0, -1);
	}
	else if (key == 'd') {
		display.movecursor(0, 1);
	
	}
	else if (key == 'f') {
		display.laser.fire();
		cout << "pew pew pew \n";
	}
	else if (key == 'q') {
		if (menu == false) {
			display.resetboard();
			display.menu();
			display.print();
			cout << "powrot do menu \n";
			menu = true;
			help = false;
		}
		else {
			display.resetboard();
			display.grid(display.getsize());
			display.movecursor(0, 0);
			display.print();
			menu = false;
		};
		
	}
	else if (key == 32) {
		cout << "wczytano gre \n";
	
	}
	else if (key == 'p') {
		if (help == false && menu ==false) {
			display.printmap();
			display.print();
			cout << "Wlaczono oszustwa" << endl;
			help = true;
		}
		else {
			if (!menu) {
				display.resetboard();
				display.grid(display.getsize());
				display.movecursor(0, 0);
				cout << "Wylaczono oszustwa" << endl;
				help = false;
			}
		}
		
	}
	else if (key == 'k') {
		display.printmap();
		display.print();
		cout << "KONIEC GRY" << endl;
	}
	else {
		cout << key << "is invalid move \n";
		move();
	};
};

void Game::start() {
	diff(imput());
	display.print();
	do {
		move();
		display.print();
	} while (win == false);
	display.printmap();
	display.print();
	display.win();
	exit(0);
};

void Game::diff(int key) {
	if (key == '1') {
		menu = false;
		display.laser.init(8);
		display.resetboard();
		display.grid(8);
		display.movecursor(0,0);
		display.laser.map.generate(easy_atoms, 8);
	}
	else if (key == '2') {
		menu = false;
		display.laser.init(10);
		display.resetboard();
		display.grid(10);
		display.movecursor(0,0);;
		display.laser.map.generate(hard_atoms, 10);
	}
	else {
		cout << "invalid \n";
		diff(imput());
	}
};