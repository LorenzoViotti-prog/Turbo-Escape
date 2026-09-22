#ifndef FINDELJUEGO_H
#define FINDELJUEGO_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Escena.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Boton.h"
#include "Musica.h"
using namespace sf;
struct Jugador{
	char nombre[25];
	int puntos;
};

class FinDelJuego : public Escena{
public:
	FinDelJuego();
	void Actualizar(Juego &j, RenderWindow &win)override;
	void Dibujar(RenderWindow &win)override;
	void Cargar_ultima_puntuacion();
	void Cargar_nombre();
	void Guardar_record_tabla(string nombre,int puntuacion_fin);
private:
	Font m_font;
	Text m_text, texto_puntuacion;
	Boton boton_reiniciar;
	Boton boton_volver_menu;
	int puntuacion_fin;
	char m_nombre[25];
	Texture fondo_final;
	Sprite sprite_fondo_final;
};

#endif

