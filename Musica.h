#ifndef MUSICA_H
#define MUSICA_H
#include <string>
#include <SFML/Audio/Music.hpp>
using namespace std;
using namespace sf;

class Musica {
public:
	Musica(string nombre);
	static Musica& Instancia();
	void CargarMusica(string archivo);
	void Volumen();
	void Volumen_off();
	void Volumen_on();
	bool Ver_estado();
	~Musica();
private:
	Music musica;
	
	Musica(){}
	bool m_sonido;
	Musica(const Musica&) = delete;
	Musica& operator=(const Musica&) = delete;
};

#endif

