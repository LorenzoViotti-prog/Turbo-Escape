#ifndef AUTO_H
#define AUTO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <SFML/Window/Keyboard.hpp>
using namespace std;
using namespace sf;

class Auto {
public:
	Auto();
	
	void Desplazar(Keyboard::Key acelerar, Keyboard::Key retroceder, Keyboard::Key derecha, Keyboard::Key izquierda);
	void Desplazar_lento(Keyboard::Key acelerar, Keyboard::Key retroceder, Keyboard::Key derecha, Keyboard::Key izquierda);
	
	void Dibujar(RenderWindow &win);
	Vector2f Pos_jugador();
	FloatRect Ver_Rectangulo_a();
	void Detener_auto();
private:
	Texture m_textura;
	Sprite m_sprite;
};

#endif

