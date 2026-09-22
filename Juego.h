#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Puntaje.h"
#include "Musica.h"
using namespace sf;
class Escena;

class Juego {
public:
	Juego(Escena *e);
	void Iniciar_musica();
	void jugar();
	void Cambiar_escena(Escena *escena_nueva);
	~Juego();
private:
	RenderWindow win;
	Escena *m_escena, *m_prox_escena = nullptr;
	Musica musica_juego;
};

#endif

