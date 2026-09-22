#ifndef ESCENA_H
#define ESCENA_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Juego.h"
#include <SFML/Window/Event.hpp>
using namespace sf;

class Escena {
public:
	Escena();
	virtual void Actualizar(Juego &j, RenderWindow &win) = 0;
	virtual void Dibujar(RenderWindow &win) = 0;
	virtual void Procesar_evento(Juego &j, Event &evento, RenderWindow &win){}
private:
	
};

#endif

