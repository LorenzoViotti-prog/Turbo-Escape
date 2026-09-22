#ifndef CONTROLES_H
#define CONTROLES_H
#include "Escena.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Juego.h"
#include "Boton.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

class Controles : public Escena{
public:
	Controles();
	void Dibujar(RenderWindow &win)override;
	void Actualizar(Juego &j, RenderWindow &win)override;
	void Procesar_evento(Juego &j, Event &evento, RenderWindow &win)override;
private:
	Boton boton_volver;
	Boton c_up;
	Boton c_down;
	Boton c_right;
	Boton c_left;
	Texture t_volver;
	Sprite s_volver;
};

#endif

