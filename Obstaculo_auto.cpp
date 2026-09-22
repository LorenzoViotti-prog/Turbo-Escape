#include "Obstaculo_auto.h"
#include "Obstaculo.h"
#include <string>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
using namespace std;
using namespace sf;

Obstaculo_auto::Obstaculo_auto(Texture &nombre):Obstaculo(nombre){
	string tipo_obstaculo;
	o_sprite.setTexture(nombre);
	o_sprite.setOrigin(382,743);
	o_sprite.setPosition(Aparecer(tipo_obstaculo));
	o_sprite.scale(0.13,0.13);
}

void Obstaculo_auto::Desplazamiento(){
	o_sprite.move(0,8);															//movimiento de los obstaculos
}
void Obstaculo_auto::Desplazamiento_lento(){
	o_sprite.move(0,-15);
}
void Obstaculo_auto::Corregir_inclinacion(){
	o_sprite.setRotation(0);
}
void Obstaculo_auto::Reaccion_derecha(){
	reloj_reaccion.restart();
	if(reloj_reaccion.getElapsedTime().asMilliseconds() < 3000){
		o_sprite.move(8,-8);
		o_sprite.setRotation(10);
	}
}
void Obstaculo_auto::Reaccion_izquierda(){
	reloj_reaccion.restart();
	if(reloj_reaccion.getElapsedTime().asMilliseconds() < 3000){
		o_sprite.move(-8,-8);
		o_sprite.setRotation(-10);
	}
}
void Obstaculo_auto::Detener(){
	o_sprite.move(0,10);
}
FloatRect Obstaculo_auto::Ver_Rectangulo_o(){
	return o_sprite.getGlobalBounds();	
}

Vector2f Obstaculo_auto::Aparecer(string tipo_obstaculo){
	int pos_x_gen = 350+rand()%(1380-350+1); 									
	int pos_y_gen = -500+rand()%(-150+500-1);									
	Vector2f aparicion(pos_x_gen, pos_y_gen);
	return aparicion;
}

Vector2f Obstaculo_auto::Ver_posicion(){
	return o_sprite.getPosition();
}
