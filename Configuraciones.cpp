#include "Configuraciones.h"
#include "Boton.h"
#include <SFML/Window/Mouse.hpp>
#include "Menu.h"
#include "Controles.h"
#include <SFML/Window/Event.hpp>
#include "Musica.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
using namespace std;

Configuraciones::Configuraciones() : boton_sonido({100,100},{1820,0},"",20,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"), 
	boton_volver ({100,100},{0,0},"",20,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	boton_WASD({200,180},{600,300},"WASD",50,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	boton_flechitas({200,200},{1100,300},"<>",50,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf")
{
	textura_sonido_on.loadFromFile("imagenes/imagen_sonido_on.png");
	textura_sonido_off.loadFromFile("imagenes/imagen_sonido_off.png");
	
	
	textura_volver.loadFromFile("imagenes/flecha_volver_menu.jpg");
	s_volver.setTexture(textura_volver);
	s_volver.setPosition({0,0});
	s_volver.setScale(0.35,0.35);
	
	textura_WASD.loadFromFile("imagenes/WASD.jpg");
	s_WASD.setTexture(textura_WASD);
	s_WASD.setPosition({500,300});
	s_WASD.setScale(0.2,0.2);
	
	textura_flechitas.loadFromFile("imagenes/Flechitas.jpg");
	s_flechitas.setTexture(textura_flechitas);
	s_flechitas.setPosition({1100,300});
	s_flechitas.setScale(0.2,0.2);
	
	fuente.loadFromFile("Tipografia/static/Asap_Condensed-BlackItalic.ttf");
	texto_controles.setFont(fuente);
	texto_controles.setString("Controles");
	texto_controles.setFillColor({255,255,255});
	texto_controles.setPosition(825,130);
	texto_controles.setCharacterSize(70);
	
	sonido=Musica::Instancia().Ver_estado();
	
}

void Configuraciones::Procesar_evento(Juego &j, Event &evento, RenderWindow &win){
	if(evento.type==Event::MouseButtonPressed && evento.mouseButton.button==Mouse::Left){
		Vector2i pos_mouse = Mouse::getPosition(win);
		Vector2f posicion_mouse(pos_mouse.x, pos_mouse.y);
		
		if (boton_volver.Contiene(posicion_mouse)) {
			j.Cambiar_escena(new Menu);
		}
		if(boton_flechitas.Contiene(posicion_mouse)){
			Instancia().Establecer_WASD(false);
			j.Cambiar_escena(new Menu);
		}
		if(boton_WASD.Contiene(posicion_mouse)){
			Instancia().Establecer_WASD(true);
			j.Cambiar_escena(new Menu);
		}
		if (boton_sonido.Contiene(posicion_mouse)){
			if(sonido){
				Apagar_musica();
				s_sonido_off.setPosition({1820,0});
				s_sonido_off.setScale(0.445,0.445);
				s_sonido_on.setScale(0,0);
				sonido = false;
			} else{
				Prender_musica();
				s_sonido_on.setPosition({1820,0});
				s_sonido_on.setScale(0.455,0.455);
				s_sonido_off.setScale(0,0);
				sonido = true;
			}
		}
	}
}

void Configuraciones::Actualizar(Juego &j, RenderWindow &win){
	win.clear({0,0,0});
	
	if(sonido){
		s_sonido_on.setTexture(textura_sonido_on);
		s_sonido_on.setPosition({1820,0});
		s_sonido_on.setScale(0.445,0.445);
	}else{
		s_sonido_off.setTexture(textura_sonido_off);
		s_sonido_off.setPosition({1820,0});
		s_sonido_off.setScale(0.445,0.445);
	}
	
}

void Configuraciones::Prender_musica(){
	Musica::Instancia().Volumen_on(); 
}

void Configuraciones::Apagar_musica(){
	Musica::Instancia().Volumen_off(); 
}


bool Configuraciones::Ver_WASD(){ return WASD;}

Configuraciones& Configuraciones::Instancia(){
	static Configuraciones instancia;
	return instancia;
}

void Configuraciones::Establecer_WASD(bool valor){
	WASD = valor;
}

void Configuraciones::Dibujar(RenderWindow &win){
	win.clear({0,0,0});
	boton_sonido.Dibujar(win);
	boton_volver.Dibujar(win);
	boton_flechitas.Dibujar(win);
	boton_WASD.Dibujar(win);
	win.draw(s_sonido_on);
	win.draw(s_sonido_off);
	win.draw(s_volver);
	win.draw(texto_controles);
	win.draw(s_WASD);
	win.draw(s_flechitas);
}
