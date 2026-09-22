#include "Menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Partida.h"
#include <fstream>
#include "Boton.h"
#include "Configuraciones.h"
#include "Musica.h"
#include "Tabla.h"
using namespace std;


Menu::Menu() : boton_jugar({185,90},{865,540},"Jugar",50,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"), 
	boton_borrar_record({168,40},{1718,43},"Borrar record",30,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	boton_configuraciones({350,90},{780,700},"Configuraciones",50,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	boton_tipeo_usuario({170,30},{620,50},"Nombre de usuario: ", 20,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf"),
	boton_tabla({170,30},{0,0}," Ranking ", 30,{100,100,100},{200,200,200},"Tipografia/static/Asap_SemiCondensed-Medium.ttf")
{
	
	
	fondo.loadFromFile("imagenes/ferrari fondo.jpg");
	fondo_sprite.setTexture(fondo);
	font_menu_nombre.loadFromFile("Tipografia/static/Asap_Condensed-BlackItalic.ttf");

	texto_nombre.setFont(font_menu_nombre);
	texto_nombre.setString("Turbo Escape");
	texto_nombre.setFillColor({255,255,255});
	texto_nombre.setPosition(760,300);
	texto_nombre.setCharacterSize(80);
	
	m_input.setFont(font_menu_nombre);
	m_input.setFillColor({0,0,0});
	m_input.setPosition(800,46);
	m_input.setCharacterSize(30);
	
	Cargar_record();
	Cargar_nombre();
}

void Menu::Cargar_record(){ 
	ifstream archivo2("record.dat", ios::binary);
	if(!archivo2.is_open()){
		throw runtime_error("No se pudo abrir 'record.dat'");
	}
	archivo2.read(reinterpret_cast<char*>(&menu_record),sizeof(menu_record));
	archivo2.close();
	
	fuente_record.loadFromFile("Tipografia/static/Asap_Condensed-Black.ttf");
	texto_record.setFont(fuente_record);
	texto_record.setCharacterSize(30);
	texto_record.setFillColor({255,255,255});
	texto_record.setPosition(1720, 0);  
	texto_record.setString("Record: " + to_string(menu_record));
}

void Menu::Procesar_evento(Juego &j, Event &e, RenderWindow &win){
	if(e.type==Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left){
		Vector2i pos_mouse = Mouse::getPosition(win);
		Vector2f posicion_mouse(pos_mouse.x, pos_mouse.y);
		if(boton_configuraciones.Contiene(posicion_mouse)){
			j.Cambiar_escena(new Configuraciones);
		}
		if(boton_jugar.Contiene(posicion_mouse)){
			j.Cambiar_escena(new Partida);
		}
		if(boton_tabla.Contiene(posicion_mouse)){
			j.Cambiar_escena(new Tabla);
		}
		if(boton_borrar_record.Contiene(posicion_mouse)){
			ofstream archi("record.dat", ios::binary|ios::trunc);
			if(!archi.is_open()){
				throw runtime_error("No se pudo abrir 'record.dat'");
			}
			int menu_record=0;
			texto_record.setString("Record: " + to_string(menu_record));
		}
		if(boton_tipeo_usuario.Contiene(posicion_mouse)){
			escribir=true;
			
		}
	}
	if(escribir){
		m_input.update();
		if (e.type==sf::Event::KeyPressed && e.key.code==sf::Keyboard::Return) { 
			string string_ingresado = m_input.getValue();
			Guardar_nombre(string_ingresado);
			Cargar_nombre();
			escribir=false;
		}else m_input.processEvent(e);
	}
	
	
}
void Menu::Guardar_nombre(string string_ingresado){
	ofstream archivo_nombre("nombre.txt");
	if(!archivo_nombre.is_open()){
		throw runtime_error("No se pudo abrir el archivo nombre");
	}
	archivo_nombre<<string_ingresado;
}
void Menu::Cargar_nombre(){
	ifstream archivo_nombre("nombre.txt");
	if(!archivo_nombre.is_open()){
		throw runtime_error("No se pudo abrir el archivo nombre");
	}
	string nombre;
	if(archivo_nombre>>nombre){
	texto_usuario.setString(nombre);
	texto_usuario.setFont(font_menu_nombre);
	texto_usuario.setPosition({800,46});
	texto_usuario.setCharacterSize(30);
	texto_usuario.setFillColor({0,0,0});
	}
	archivo_nombre.close();
}

void Menu::Actualizar(Juego &j, RenderWindow &win){
	
}
void Menu::Dibujar(RenderWindow &win){
	win.clear({0,0,0});
	win.draw(fondo_sprite);
	win.draw(texto_record);
	win.draw(texto_nombre);
	win.draw(m_input);
	
	if(!escribir){
		win.draw(texto_usuario);
	}
	
	boton_jugar.Dibujar(win);
	boton_borrar_record.Dibujar(win);
	boton_configuraciones.Dibujar(win);
	boton_tipeo_usuario.Dibujar(win);
	boton_tabla.Dibujar(win);
}

