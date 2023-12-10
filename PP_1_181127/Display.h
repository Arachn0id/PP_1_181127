#pragma once
#include "Laser.h"

#define board_width 60
#define board_length 25

class Display :public Laser {
private:
	int k = 4; 
	char gamename[13] = "BLACKBOX_1.0";
	char NAME[23] = "PAWEL PAJAK IBM 181127";
	char board[board_length][board_width];
	char A[17] = "POZIOM TRUDNOSCI";
	char B[30] = "Wcisnij odpowiadajacy klawisz";
	char C[10] = "LATWY - 1";
	char D[10] = "TRUDNY- 2";
	char E[12] = "Wyjscie - 3";
	char G[16] = "Kontynuacja - Q";
	char H[16] = "Zaznacz atom: o";
	char F[44] = "Ruch: WSAD / STRZAL: SPACE / POKAZ ATOMY: P";
	char markers[3] = { 'X', '&','%' };
	char wintext[11] = "GRATULACJE";
	char scoretext[11] = "Twoj wynik";
	int x_offset;
	int y_offset;
	int size;
public:
	Laser laser;
	Display();
	void endgame();
	void win();
	void markatom();
	void menu();
	void print();
	void resetboard();
	void grid(int size);
	void movecursor(int x, int y);
	void printmap();
	void placemiddle(char what[], int x);
	void placemiddle(char what, int x);
	void offset(int size);
	int getsize();
	void printguess();
}; 




