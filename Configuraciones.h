#ifndef CONFIGURACIONES_H
#define CONFIGURACIONES_H
#include "Boton.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Escena.h"
#include "Juego.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Musica.h"
#include "Configuraciones.h"

class Configuraciones : public Escena{
public:
	Configuraciones();
	void Dibujar(RenderWindow &win);
	void Actualizar(Juego &j, RenderWindow &win) override;
	void Procesar_evento(Juego &j, Event &evento, RenderWindow &win)override;
	
	void Cambiar_controles(RenderWindow &win);
	void Apagar_musica();
	void Prender_musica();
	bool Ver_WASD();
	
	static Configuraciones& Instancia();
	void Establecer_WASD(bool valor);
private:
	Boton boton_sonido;
	Boton boton_volver;
	Boton boton_WASD;
	Boton boton_flechitas;
	
	Texture textura_sonido_on, textura_sonido_off, textura_volver, textura_WASD, textura_flechitas;
	Sprite s_sonido_on, s_sonido_off , s_volver, s_WASD, s_flechitas;
	
	bool WASD=false;
	bool sonido;
	
	Font fuente;
	Text texto_controles;
};

#endif

