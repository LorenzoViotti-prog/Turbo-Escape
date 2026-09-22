#include "Obstaculo_objeto.h"
#include <fstream>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
using namespace std;

Obstaculo_objeto::Obstaculo_objeto(Texture &nombre, string &m_tipo) : Obstaculo(nombre){
	o_sprite.setTexture(nombre);
	o_sprite.setPosition(Aparecer(m_tipo));
	o_sprite.scale(0.13,0.13);
	
	tipo=m_tipo;
}
void Obstaculo_objeto::Desplazamiento(){
	o_sprite.move(0,10);														
}

string Obstaculo_objeto::Ver_tipo(){return tipo;}

FloatRect Obstaculo_objeto::Ver_Rectangulo_o(){
	return o_sprite.getGlobalBounds();
}																				

Vector2f Obstaculo_objeto::Aparecer(string tipo_obstaculo){
	if(tipo_obstaculo == "cono"){
		vector<Vector2f> v_apariciones_cono = {
		{400, -1000},
		{700, -1000},
		{1000, -1000},
		{1300, -1000}
		};
		int aparicion_cono = rand() % v_apariciones_cono.size();
		return v_apariciones_cono[aparicion_cono];
	}
	if(tipo_obstaculo == "pozo"){
		int pos_x_pozo = 460+rand()%(1430-460+1); 									
		int pos_y_pozo = -1000+rand()%(-800+1000-1);									
		Vector2f aparicion_pozo(pos_x_pozo, pos_y_pozo);
		return aparicion_pozo;
	}
	if(tipo_obstaculo == "valla"){
		int pos_x_valla = (rand() % 2 == 0) ? 285 : 1170;
		int pos_y_valla = -1000 + rand() % (-800+1000-1);
		Vector2f aparicion_valla(pos_x_valla, pos_y_valla);
		return aparicion_valla;
	}
}
void Obstaculo_objeto::Tumbar_cono(){
	if(tipo == "cono"){
		o_sprite.setRotation(-15+rand()%(15-15+1));
		o_sprite.move(0,-5);
	}
}

Vector2f Obstaculo_objeto::Ver_posicion(){
	return o_sprite.getPosition();
}
