#include "FinDelJuego.h"
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Partida.h"
#include "Menu.h"
#include <fstream>
#include <iostream>
#include "Musica.h"
#include <cstring>
using namespace std;
using namespace sf;


FinDelJuego::FinDelJuego() : 	boton_reiniciar({400,100},{800,500},"Volver a jugar",60,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	boton_volver_menu({400,100},{800,700},"Volver al menu",60,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"){
	
	
	fondo_final.loadFromFile("imagenes/imagen_ferrari_perdiste.png");
	sprite_fondo_final.setTexture(fondo_final);
	

	m_font.loadFromFile("Tipografia/static/Asap_Condensed-Black.ttf");
	m_text.setFont(m_font);
	m_text.setPosition(400,500);
	m_text.setFillColor({255,255,255});
	m_text.setCharacterSize(60);
	m_text.setString("PERDISTE");
	
	
	Cargar_ultima_puntuacion();
	Cargar_nombre();
	Guardar_record_tabla(m_nombre,puntuacion_fin);
	
}
void FinDelJuego::Cargar_nombre(){
	ifstream archi("nombre.txt");
	if(!archi.is_open()){
		throw runtime_error("No se pudo abrir nombre.txt");
	}
	char nombre[25];
	if(archi>>nombre){
		strcpy(m_nombre,nombre);
	}else{
		string nombre_aux="invitado";
		strcpy(m_nombre,nombre_aux.c_str());
	}
}
void FinDelJuego::Guardar_record_tabla(string nombre,int puntuacion_fin){
	ofstream tabla("Ranking.dat",ios::binary|ios::app);
	
	if(!tabla.is_open()){
		throw runtime_error("No se pudo abrir ranking.dat");
	}
	Jugador x;
	strcpy(x.nombre,nombre.c_str());
	x.puntos=puntuacion_fin;
	tabla.write(reinterpret_cast<char*>(&x),sizeof(x));
	tabla.close();
}

void FinDelJuego::Cargar_ultima_puntuacion(){
	ifstream archivo2("puntuacion.dat", ios::binary);
	if(!archivo2.is_open()){
		throw runtime_error("No se pudo abrir 'puntuacion.dat'");
	}
	archivo2.read(reinterpret_cast<char*>(&puntuacion_fin),sizeof(puntuacion_fin));
	archivo2.close();
	
	texto_puntuacion.setFont(m_font);
	texto_puntuacion.setCharacterSize(45);
	texto_puntuacion.setFillColor({0,0,0});
	texto_puntuacion.setPosition(0, 0);  // Ajusta la posición en pantalla
	texto_puntuacion.setString("Tu puntuacion: " + to_string(puntuacion_fin));	
}
void FinDelJuego::Actualizar(Juego &j, RenderWindow &win){
	if(Mouse::isButtonPressed(Mouse::Left)){
		Vector2i pos_mouse = Mouse::getPosition(win);
		Vector2f posicion_mouse(pos_mouse.x, pos_mouse.y);
		
		if(boton_reiniciar.Contiene(posicion_mouse)){
			Musica::Instancia().Volumen_off();
			j.Cambiar_escena(new Partida);
		}
		
		if(boton_volver_menu.Contiene(posicion_mouse)){
			Musica::Instancia().Volumen_off();
			j.Cambiar_escena(new Menu);
		}
	}
}
void FinDelJuego::Dibujar(RenderWindow &win){
	win.clear({0,0,0});
	win.draw(sprite_fondo_final);
	boton_reiniciar.Dibujar(win);
	win.draw(texto_puntuacion);
	boton_volver_menu.Dibujar(win);
	win.draw(m_text);
}
