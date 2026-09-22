#include "Asfalto.h"
#include <SFML/System/Vector2.hpp>
using namespace sf; 
Asfalto::Asfalto(bool pos_bool) {
	m_textura_asfalto.loadFromFile("Imagenes/Carretera_p1.png");
	ms_asfalto.setTexture(m_textura_asfalto);
	
	if(pos_bool == true) ms_asfalto.setPosition(960,0);
	else if (pos_bool == false) ms_asfalto.setPosition(960,-1080);
	
	ms_asfalto.setOrigin(960,0);
}
void Asfalto::Movimiento(){
	ms_asfalto.move(0,10);
}

void Asfalto::Detener(){
	ms_asfalto.move(0,0);
}

void Asfalto::Dibujar(RenderWindow &win){
	win.draw(ms_asfalto);
}
Vector2f Asfalto::Mostrar_Posicion(){
	return ms_asfalto.getPosition();
}

void Asfalto::Resetear_posicion(){
	ms_asfalto.setPosition(960,-1080);
}
