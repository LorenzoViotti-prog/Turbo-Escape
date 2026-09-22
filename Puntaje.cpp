#include "Puntaje.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
using namespace std;
using namespace sf;
Puntaje::Puntaje() {
	m_font.loadFromFile("Tipografia/static/Asap_Condensed-Black.ttf");
	m_puntos.setFont(m_font);
	m_puntos.setString("0");
	m_puntos.setPosition(100,0);
	m_puntos.setCharacterSize(50);
	m_puntos.setFillColor({0,0,0});
}
void Puntaje::Actualizar(){
	int truncado = c_puntos.getElapsedTime().asMilliseconds()*0.1;				//actualiza y trunca el flotante a un entero
	string valor = to_string(truncado);
	m_puntos.setString(valor);
} 
int Puntaje::Puntaje_actual(){
	return c_puntos.getElapsedTime().asMilliseconds()*0.1;
}

void Puntaje::Dibujar(RenderWindow &win){
	win.draw(m_puntos);
}

