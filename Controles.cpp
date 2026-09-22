#include "Controles.h"
#include "Boton.h"
#include <SFML/Window/Mouse.hpp>
#include "Configuraciones.h"
#include "Menu.h"

Controles::Controles() : boton_volver({100,100},{0,0},"",20,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	c_up({100,100},{560,540},"UP",30,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	c_down({100,100},{760,540},"DOWN",30,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	c_right({100,100},{960,540},"RIGHT",30,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	c_left({100,100},{1160,540},"LEFT",30,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"){
	
	t_volver.loadFromFile("imagenes/flecha_volver_menu.jpg");
	s_volver.setTexture(t_volver);
	s_volver.setPosition({0,0});
	s_volver.setScale(0.35,0.35);
	
}

void Controles::Procesar_evento(Juego &j, Event &evento, RenderWindow &win){
	if(evento.type==Event::MouseButtonPressed && evento.mouseButton.button==Mouse::Left){
		Vector2i pos_mouse = Mouse::getPosition(win);
		Vector2f posicion_mouse(pos_mouse.x, pos_mouse.y);
		
		if(boton_volver.Contiene(posicion_mouse)){
			j.Cambiar_escena(new Configuraciones);
		}
	}
}

void Controles::Actualizar(Juego &j, RenderWindow &win){
	
}

void Controles::Dibujar(RenderWindow &win){
	win.clear({0,0,0});
	boton_volver.Dibujar(win);
	win.draw(s_volver);
	
	c_up.Dibujar(win);
	c_down.Dibujar(win);
	c_right.Dibujar(win);
	c_left.Dibujar(win);
}
