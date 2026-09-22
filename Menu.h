#ifndef MENU_H
#define MENU_H
#include "Escena.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Boton.h"
#include <SFML/Audio/Music.hpp>
#include "Musica.h"
#include "InputText.hpp"
using namespace sf;
using namespace std;

class Menu : public Escena{
public:
	Menu();
	void Actualizar(Juego &j, RenderWindow &win) override;
	void Dibujar(RenderWindow &win) override;
	void Procesar_evento(Juego &j, Event &evento, RenderWindow &win) override;
	void Cargar_record();
	void Guardar_nombre(string string_ingresado);
	void Cargar_nombre();
private:
	Font font_menu_nombre, fuente_record;
	Text texto_nombre,texto_record,texto_usuario;
	Texture fondo;
	Sprite fondo_sprite;
	Boton boton_jugar, boton_borrar_record, boton_configuraciones, boton_tipeo_usuario, boton_tabla;
	int menu_record, ajuste_musica;
	InputText m_input;
	bool escribir=false;

};

#endif

