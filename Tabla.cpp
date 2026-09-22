#include "Tabla.h"
#include <fstream>
#include <algorithm>
#include "Menu.h"
#include <iostream>
#include <cstring>
using namespace std;
bool compararPorPuntos(const Jugador &a, const Jugador &b) {
	return a.puntos > b.puntos; // Ordena de mayor a menor
}

Tabla::Tabla():boton_volver ({100,100},{0,0},"",20,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"){
	
	textura_volver.loadFromFile("imagenes/flecha_volver_menu.jpg");
	s_volver.setTexture(textura_volver);
	s_volver.setPosition({0,0});
	s_volver.setScale(0.35,0.35);
	
	Fuente_tabla.loadFromFile("Tipografia/static/Asap_SemiCondensed-Medium.ttf");
	
	//Crear_record_tabla();
	Cargar_records();
	Ordenar_records();
}
void Tabla::Crear_record_tabla(){
	ofstream tabla("Ranking.dat",ios::binary);
	if(!tabla.is_open()){
		throw runtime_error("No se pudo abrir ranking.dat");
	}
	tabla.close();
}
void Tabla::Procesar_evento(Juego &j, Event &evento, RenderWindow &win){
	if(evento.type==Event::MouseButtonPressed && evento.mouseButton.button==Mouse::Left){
		Vector2i pos_mouse = Mouse::getPosition(win);
		Vector2f posicion_mouse(pos_mouse.x, pos_mouse.y);
		
		if (boton_volver.Contiene(posicion_mouse)) {
			j.Cambiar_escena(new Menu);
		}
	}
}
void Tabla::Actualizar(Juego &j, RenderWindow &win){
	/*win.clear({0,0,0});*/
	
	int posX = 700,posY = 100;
	
	for(size_t i=0;i<Jugadores.size();i++) { 
		Text texto_nombre;
		texto_nombre.setFont(Fuente_tabla);
		texto_nombre.setCharacterSize(24);
		texto_nombre.setFillColor({255,255,255});
		texto_nombre.setString(to_string(i + 1) + ". " + Jugadores[i].nombre);
		texto_nombre.setPosition(posX, posY + i * 70);
		vt_nombres.push_back(texto_nombre);
		
		
		
		Text texto_puntos;
		texto_puntos.setFont(Fuente_tabla);
		texto_puntos.setCharacterSize(24);
		texto_puntos.setFillColor({255,0,0});
		
		texto_puntos.setString(to_string(Jugadores[i].puntos));
		texto_puntos.setPosition(posX+300, posY + i *70);
		
		vt_puntos.push_back(texto_puntos);
	}
}
void Tabla::Cargar_records(){
	ifstream archi("Ranking.dat",ios::binary|ios::ate);
	if(!archi.is_open()){
		throw runtime_error("No se pudo abrir ranking.dat");
	}
	int bytes = archi.tellg();
	archi.seekg(0);
	int cant_datos = bytes/sizeof(Jugador);
	if (bytes <= 0) {
		std::cerr << "Error: Archivo Ranking.dat vacio o corrupto.\n";
		return;
	}
	Jugador x;
	for(int i=0;i<cant_datos;i++) { 
		archi.read(reinterpret_cast<char*>(&x),sizeof(x));
		Jugadores.push_back(x);
	}
	archi.close();
}
void Tabla::Ordenar_records(){
	sort(Jugadores.begin(),Jugadores.end(),compararPorPuntos);
	if(Jugadores.size()>10)Jugadores.resize(10);
	Guardar_records();
}
void Tabla::Guardar_records(){
	ofstream tabla("Ranking.dat",ios::binary);
	
	if(!tabla.is_open()){
		throw runtime_error("No se pudo abrir ranking.dat");
	}
	
	
	for(size_t i=0;i<Jugadores.size();i++) {
		Jugador x;
		strcpy(x.nombre,Jugadores[i].nombre);
		x.puntos=Jugadores[i].puntos;
		tabla.write(reinterpret_cast<char*>(&x),sizeof(x));	
	}
	tabla.close();
}
void Tabla:: Dibujar(RenderWindow &win){
	win.clear({0,0,0});
	boton_volver.Dibujar(win);
	win.draw(s_volver);
	for(int i=0;i<Jugadores.size();i++) { 
		win.draw(vt_nombres[i]);
		win.draw(vt_puntos[i]);
	}
	
}
