#include "Musica.h"
#include <SFML/Audio/Music.hpp>
#include <stdexcept>
using namespace std;
Musica::Musica(string nombre) {
	musica.setLoop(true);  
}
Musica& Musica::Instancia(){
	static Musica instancia;
	return instancia;
}
void Musica::CargarMusica(string archivo) {
	if (!musica.openFromFile(archivo)) {
		throw runtime_error("Error al abrir la musica");
	}
}
void Musica::Volumen(){
	musica.setVolume(10);
}
void Musica::Volumen_on(){
	musica.play();
	m_sonido = true;
}

void Musica::Volumen_off(){
	musica.stop();
	m_sonido=false;
}
  
bool Musica::Ver_estado(){
	return m_sonido;
}


Musica::~Musica(){}
