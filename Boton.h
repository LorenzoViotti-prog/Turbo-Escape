#ifndef BOTON_H
#define BOTON_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
using namespace sf;
using namespace std;

class Boton {
public:
	Boton(Vector2f tamanio, Vector2f posicion, string texto_boton, int tamanio_texto, Color color_boton, Color color_texto, string fuente_boton);
	bool Contiene(Vector2f &punto);
	void Dibujar(RenderWindow &win);
private:
	RectangleShape rectangulo;
	Text texto;
	Font fuente;
};

#endif

