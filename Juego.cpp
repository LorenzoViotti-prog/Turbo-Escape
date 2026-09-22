#include "Juego.h"
#include <SFML/Window/VideoMode.hpp>
#include "Escena.h"
#include "Partida.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Menu.h"
#include <fstream>
using namespace std;
using namespace sf;
Juego::Juego(Escena *e) : win(VideoMode(1920,1080),"Turbo Escape"), musica_juego("Musica/Musica_menu1.ogg"){
	Iniciar_musica();
	m_escena = e;	
}
void Juego::jugar(){
	while(win.isOpen()) {
		Event e; 
		while(win.pollEvent(e)) {
			if(e.type == Event::Closed)
				win.close();	
			else 
				m_escena->Procesar_evento(*this, e, win); 
		}
		
		m_escena->Actualizar(*this, win);
		m_escena->Dibujar(win);
		win.display();
		
		if(m_prox_escena){
			delete m_escena;
			m_escena = m_prox_escena;
			m_prox_escena = nullptr;
		}
	}
}

void Juego::Iniciar_musica(){
	Musica::Instancia().CargarMusica("Musica/Musica_menu1.ogg");
	Musica::Instancia().Volumen_on();
	Musica::Instancia().Volumen();
}

void Juego::Cambiar_escena(Escena *escena_nueva){
	m_prox_escena = escena_nueva;
}

Juego::~Juego(){
	delete m_escena;
}
