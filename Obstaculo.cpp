#include "Obstaculo.h"
#include <string>
#include <cstddef>
#include <ctime>
#include <cstdlib>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <vector>
using namespace std;
using namespace sf;

Obstaculo::Obstaculo(Texture &nombre) {}


int Obstaculo::Ver_Reloj(){
	return m_clock.getElapsedTime().asMilliseconds();							//devuelve el tiempo transcurrido en milisegundos
}

void Obstaculo::Reiniciar_reloj(){
	m_clock.restart();
}

void Obstaculo::Detener_obstaculo(){
	o_sprite.move(0,0);
}

void Obstaculo::Dibujar(RenderWindow &win){
	win.draw(o_sprite);
}
Obstaculo::~Obstaculo(){};
