#include "Auto.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

Auto::Auto() {
	m_textura.loadFromFile("Imagenes/auto_player.png");
	m_sprite.setTexture(m_textura);
	m_sprite.setPosition(960, 750);
	m_sprite.setScale(0.13,0.13);
	m_sprite.setOrigin(382,743); //tamanio del auto 765x1486
} //constructor

void Auto::Desplazar(Keyboard::Key acelerar, Keyboard::Key retroceder, Keyboard::Key derecha, Keyboard::Key izquierda){ //movimiento del auto	
	if(Keyboard::isKeyPressed(derecha)){
		int x_r = m_sprite.getPosition().x;
		if(x_r > 1530){
			m_sprite.move(0,0);
			m_sprite.setRotation(10);
		} else {
				m_sprite.move(6,0);
				m_sprite.setRotation(10);
		}
	} else if(Keyboard::isKeyPressed(izquierda)){
		int x_l = m_sprite.getPosition().x;
		if(x_l < 360){
			m_sprite.move(0,0);
			m_sprite.setRotation(-10);
		} else {
				m_sprite.move(-6,0);
				m_sprite.setRotation(-10);
		}
	} else {
		m_sprite.setRotation(0);
	}
	if(Keyboard::isKeyPressed(acelerar)){
		int y_u = m_sprite.getPosition().y;
		if(y_u < 150){
			m_sprite.move(0,0);
		}else {m_sprite.move(0,-6);}
	} 
	if(Keyboard::isKeyPressed(retroceder)){
		int y_d = m_sprite.getPosition().y;
		if(y_d > 960){
			m_sprite.move(0,0);
		}else {m_sprite.move(0,6);}
	} 
}
void Auto::Desplazar_lento(Keyboard::Key acelerar, Keyboard::Key retroceder, Keyboard::Key derecha, Keyboard::Key izquierda){
	if(Keyboard::isKeyPressed(derecha)){
		int x_r = m_sprite.getPosition().x;
		if(x_r > 1530){
			m_sprite.move(0,0);
			m_sprite.setRotation(10);
		} else {
			m_sprite.move(2,0);
			m_sprite.setRotation(10);
		}
	} else if(Keyboard::isKeyPressed(izquierda)){
		int x_l = m_sprite.getPosition().x;
		if(x_l < 360){
			m_sprite.move(0,0);
			m_sprite.setRotation(-10);
		} else {
			m_sprite.move(-2,0);
			m_sprite.setRotation(-10);
		}
	} else {
		m_sprite.setRotation(0);
	}
	if(Keyboard::isKeyPressed(acelerar)){
		int y_u = m_sprite.getPosition().y;
		if(y_u < 150){
			m_sprite.move(0,0);
		}else {m_sprite.move(0,-2);}
	} 
	if(Keyboard::isKeyPressed(retroceder)){
		int y_d = m_sprite.getPosition().y;
		if(y_d > 960){
			m_sprite.move(0,0);
		}else {m_sprite.move(0,2);}
	} 
}


void Auto::Detener_auto(){
	m_sprite.move(0,0);
}

Vector2f Auto::Pos_jugador(){ return m_sprite.getPosition(); }

FloatRect Auto::Ver_Rectangulo_a(){ return m_sprite.getGlobalBounds(); }

void Auto::Dibujar(RenderWindow &win){
	win.draw(m_sprite);
}
