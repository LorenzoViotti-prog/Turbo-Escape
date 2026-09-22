#ifndef ASFALTO_H
#define ASFALTO_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class Asfalto {
public:
	Asfalto(bool pos_bool);
	void Movimiento();
	void Dibujar(RenderWindow &win);
	Vector2f Mostrar_Posicion();
	void Resetear_posicion();
	void Movimiento_lento();
	void Detener();
private:
	Texture m_textura_asfalto;
	Sprite ms_asfalto;
};

#endif

