#include <iostream>
#include "Jugador.h"

CJugador::CJugador() {}

CJugador::~CJugador() {}

CJugador::CJugador(int x, int y) {
	this->x = x;
	this->y = y;
	dx = 0;
	dy = 0;
	indiceX = 0;
	indiceY = 2;
	direccion = EDireccion::Ninguna;
	ultimaTecla = EDireccion::Abajo;
	for (int i = 0; i < HABILIDADES; i++) habilidades[i] = false;
}

void CJugador::setDireccion(EDireccion direccion) {
	this->direccion = direccion;
}

void CJugador::controlarLimitesMovimiento(const CanchaArray& cancha) {
	int X = 0, Y = 0;

	for (int i = 0; i < FILAS; i++) {
		X = 0;
		for (int j = 0; j < COLUMNAS; j++) {
			EElementos tipo = cancha[i][j]->getTipo();

			if (tipo == EElementos::paredes || tipo == EElementos::rrompible) {
				Rectangle bloque = Rectangle(X, Y, ANCHOIMAGEN, ALTOIMAGEN);
				Rectangle proximo = Rectangle(x + dx, y + dy, ANCHOJUGADOR * FACTORZOOM, ALTOJUGADOR * FACTORZOOM);

				if (proximo.IntersectsWith(bloque)) {
					dx = 0;
					dy = 0;
					return;
				}
			}
			X += ANCHOIMAGEN;
		}
		Y += ALTOIMAGEN;
	}
}

void CJugador::dibujar(Graphics^ g, Bitmap^ bmpJugador, const CanchaArray& cancha) {
	controlarLimitesMovimiento(cancha);

	Rectangle rectangulo = Rectangle(indiceX * ANCHOJUGADOR, indiceY * ALTOJUGADOR, ANCHOJUGADOR, ALTOJUGADOR);
	Rectangle zoom = Rectangle(x, y, ANCHOJUGADOR * FACTORZOOM, ALTOJUGADOR * FACTORZOOM);

	if (ultimaTecla == EDireccion::Izquierda) {
		bmpJugador->RotateFlip(System::Drawing::RotateFlipType::RotateNoneFlipX);
		g->DrawImage(bmpJugador, zoom, rectangulo, GraphicsUnit::Pixel);
		bmpJugador->RotateFlip(System::Drawing::RotateFlipType::RotateNoneFlipX);
	}
	else {
		g->DrawImage(bmpJugador, zoom, rectangulo, GraphicsUnit::Pixel);
	}

	x += dx;
	y += dy;
}

void CJugador::mover(Graphics^ g, Bitmap^ bmpJugador, const CanchaArray& cancha) {
	switch (direccion) {
	case EDireccion::Arriba:
		indiceY = 0;
		indiceX = (indiceX + 1) % 3;
		dx = 0;
		dy = -10;
		ultimaTecla = EDireccion::Arriba;
		break;
	case EDireccion::Abajo:
		indiceY = 2;
		indiceX = (indiceX + 1) % 3;
		dx = 0;
		dy = 10;
		ultimaTecla = EDireccion::Abajo;
		break;
	case EDireccion::Izquierda:
		indiceY = 3;
		indiceX = (indiceX + 1) % 3;
		dx = -10;
		dy = 0;
		ultimaTecla = EDireccion::Izquierda;
		break;
	case EDireccion::Derecha:
		indiceY = 1;
		indiceX = (indiceX + 1) % 3;
		dx = 10;
		dy = 0;
		ultimaTecla = EDireccion::Derecha;
		break;
	case EDireccion::Ninguna:
		dx = 0;
		dy = 0;
		switch (ultimaTecla) {
		case EDireccion::Abajo:
			indiceX = 0; indiceY = 2; break;
		case EDireccion::Arriba:
			indiceX = 0; indiceY = 0; break;
		case EDireccion::Izquierda:
			indiceX = 1; indiceY = 3; break;
		case EDireccion::Derecha:
			indiceX = 1; indiceY = 1; break;
		}
		break;
	}

	dibujar(g, bmpJugador, cancha);
}
