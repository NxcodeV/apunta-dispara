#include "stdio.h" //Librería "Standar input and output".
#include "conio.h"
#include "Windows.h"
#include "claseNave.h"
#include "stdlib.h"
#include <list>
#include <iostream>
//#include <fstream>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80


void gotoxy(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwPos; //Objeto de la clase COORD la cual es de la librería Windows.h
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hCon, &cci);
}

void nave::pintar() {
	gotoxy(x, y);
	printf("  %c  ", 94); // %C o cualquier letra solicita el tipo de dato para colocarlo dentro de la string
	gotoxy(x, y+1);
	printf(" %c%c%c ", 179, 207, 179);
	gotoxy(x, y + 2);
	printf("%c%c%c%c%c", 60, 35,206, 35, 62);
	gotoxy(x, y + 3);
	printf("  v  ");
}

void nave::borrar() {
	gotoxy(x, y);
	printf("     ");
	gotoxy(x, y+1);
	printf("     ");
	gotoxy(x, y+2);
	printf("     ");
	gotoxy(x, y + 3);
	printf("      ");
}

void nave::pintarSalud() {
	gotoxy(4, 30);
	printf("x  %d", vidas);


	gotoxy(38, 30);
	printf("   ");//Necesario puesto que la consola va a imprimir la cantidad de corazones, los corazones no son variables, como tal la variable corazones tiene el valor 3 pero cada emoji de corazon no es una variable.

	for (int i = 0; i < corazones; i++) {

		gotoxy(38+i, 30);
		printf("%c", 223);
	}
}

void nave::morir() {
	if (corazones == 0) {
		borrar();
		gotoxy(x, y);
		printf("  *  ");
		gotoxy(x, y+1);
		printf(" *** ");
		gotoxy(x, y+2);
		printf(" *** ");
		gotoxy(x, y+3);
		printf("  *  ");
		Sleep(1000);

		borrar();
		gotoxy(x, y);
		printf("*  *");
		gotoxy(x, y + 1);
		printf(" * ** ");
		gotoxy(x, y + 2);
		printf("* * * ");
		gotoxy(x, y + 3);
		printf(" * *");
		Sleep(1000);
		borrar();
		vidas--;
		corazones = 3;
		pintarSalud();
		pintar();
	}
}


void nave::mover() {
	if (_kbhit()) { //2. _Kbhit activa el if en caso de que una tecla se halla presionado.
		char tecla = _getch(); // _getch Recibe, evalua y guarda valor de la tecla presionada.;
		borrar();
		if (tecla == ARRIBA &&  y > 4) y--;
		if (tecla == IZQUIERDA && x > 2) x--;
		if (tecla == ABAJO && y+5 < 25) y++;
		if (tecla == DERECHA && x+2 < 75) x++;
		if (tecla == 'e') corazones--;
		pintar();
		pintarSalud();

	}
}

void pintarLimites() {
	for (int i = 2; i < 79; i++) {
		gotoxy(i, 3);
		printf("%c", 205);
		gotoxy(i, 24);
		printf("%c", 205);
	}

	for (int i = 4; i < 24; i++) {
		gotoxy(1, i);
		printf("%c", 186);
		gotoxy(79, i);
		printf("%c", 186);
	}

	gotoxy(1,3);
	printf("%c", 201);

	gotoxy(1, 24);
	printf("%c", 200);

	gotoxy(79, 3);
	printf("%c", 187);

	gotoxy(79, 24);
	printf("%c", 188);

}

void asteroides::pintar() {
	gotoxy(x, y);
	printf("%c", 254);
}

void asteroides::mover() {
	gotoxy(x,y);
	printf(" ");

	y++;
	if (y > 23) {
		x = rand()%70 + 5;
		y = 5;
	}
	pintar();
}

void asteroides::choque( class nave &n) {
	if (x >= n.X() && x < n.X() +5  && y >= n.Y() && y <= n.Y()+4) {
		n.COR();
		n.pintar();
		n.pintarSalud();
		n.borrar();
		x = rand() % 70 + 5;
		y = 5;
	}
}

void bala::mover(class nave& b) {
	gotoxy(x, y);
	printf(" ");

	y--;
	gotoxy(x, y);
	printf("*");

}

bool bala::fuera() {
	if (y == 4) return true;
	return false;
}

int main() {

	gotoxy(30, 30);


	DWORD tiempoInicio = GetTickCount();

	OcultarCursor();
	pintarLimites();

	nave nave1(37,10, 3, 3);
	std::list<asteroides*>A;
	std::list<asteroides*>::iterator itA;
	for (int i = 0; i < 5; i++) {
		A.push_back(new asteroides(rand() % 75 + 3, rand() % 5 + 4));
	}
	nave1.pintar();
	nave1.pintarSalud();

	std::list<bala*> B; //Arreglo
	std::list<bala*>::iterator it;

	bool gameOver = false;
	int puntos = 000;
	int ultimoBonus = 0;

	while (!gameOver) {

		DWORD tiempoActual = GetTickCount();
		int tiempoTranscurrido = (tiempoActual - tiempoInicio) / 1000;

		DWORD tiempoCombo = 0;
		int puntosCombo = 0;

		gotoxy(73, 2);
		printf("%d   s", tiempoTranscurrido);


		puntos == puntos;

		if (_kbhit()) {
			char tecla2 = _getch();
			if (tecla2 == 'z'||tecla2 == 'Z')
				B.push_back(new bala(nave1.X() + 2, nave1.Y() - 1));
		}

		for (it = B.begin(); it != B.end();) {
			(*it)->mover(nave1);
			if ((*it)->fuera()) {
				gotoxy((*it)->x_(), (*it)->y_()); printf(" ");
				delete(*it);
				it = B.erase(it);
			}
			else it++;
		}
		nave1.mover();
		nave1.morir();

		for (itA = A.begin(); itA != A.end(); itA++) {
			(*itA)->mover();
			(*itA)->choque(nave1);
		}

		gotoxy(2, 2);
		printf("%d", puntos);

		for (itA = A.begin(); itA != A.end();) {
			bool colision = false;
			for (it = B.begin(); it != B.end() && !colision;) {
				if ((*itA)->X() == (*it)->x_() && ((*itA)->Y() + 1 == (*it)->y_() || (*itA)->Y() == (*it)->y_())) {
					gotoxy((*it)->x_(), (*it)->y_()); printf(" ");
					delete(*it);
					it = B.erase(it);

					gotoxy((*itA)->X(), (*itA)->Y()); printf(" ");
					delete(*itA);
					itA = A.erase(itA);
					A.push_back(new asteroides(rand() % 74 + 3, 4));
					colision = true;
					puntos += 50;

					if (puntos - ultimoBonus >= 250) {
						if (nave1.CORA() < 3) {
							nave1.VIDPLUS();
							nave1.pintarSalud();
						}
						ultimoBonus = puntos;
					}

					colision = true;
					puntos += 50;

					DWORD ahora = GetTickCount();
					if (tiempoCombo == 0 || (ahora - tiempoCombo > 3000)) {
						tiempoCombo = ahora;
						puntosCombo = 50;
					}
					else {
						puntosCombo += 50;

						if (puntosCombo >= 100 && (ahora - tiempoCombo <= 3000)) {
							gotoxy(34, 1);
							printf(" ¡COMBO!");
							tiempoCombo = 0;
							puntosCombo = 0;
						}
					}

				}
				else {
					++it;
				}
			}
			if (!colision) {
				++itA;
			}
		}

		if (tiempoCombo != 0 && (GetTickCount() - tiempoCombo > 3000)) {
			tiempoCombo = 0;
			puntosCombo = 0;
			gotoxy(1, 1);
			printf("        ");
		}

		if (nave1.VID() == 0) {
			gameOver = true;
			gotoxy(1, 27);
			std::cout << "GAME OVER";
		}

		Sleep(30);
	}
	return 0;
}