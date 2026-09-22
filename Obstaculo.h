#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
using namespace std;
using namespace sf;

class Obstaculo {
public:
	Obstaculo(Texture &nombre);
	
	virtual void Desplazamiento()=0;
	virtual FloatRect Ver_Rectangulo_o()=0;
	virtual Vector2f Aparecer(string tipo_obstaculo)=0;
	virtual void Detener_obstaculo();
	virtual Vector2f Ver_posicion()=0;
	
	void Dibujar(RenderWindow &win);
	int Ver_Reloj();
	void Reiniciar_reloj();
	virtual ~Obstaculo();
private:
	Texture o_textura;
	Clock m_clock;
protected:
	Sprite o_sprite;
};

#endif


