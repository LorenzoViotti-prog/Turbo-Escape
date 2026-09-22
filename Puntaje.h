#ifndef PUNTAJE_H
#define PUNTAJE_H
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace std;
using namespace sf;

class Puntaje {
public:
	Puntaje();
	void Actualizar();
	void Dibujar(RenderWindow &win);
	int Puntaje_actual();
private:
	Text m_puntos;
	Clock c_puntos;
	Font m_font;
};

#endif

