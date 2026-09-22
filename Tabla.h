#ifndef TABLA_H
#define TABLA_H
#include <string>
#include "Escena.h"
#include <vector>
#include "Boton.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace std;
struct Jugador{
	char nombre[25];
	int puntos;
};



class Tabla:public Escena {
public:
	Tabla();
	void Actualizar(Juego &j, RenderWindow &win) override;
	void Dibujar(RenderWindow &win) override;
	void Procesar_evento(Juego &j, Event &evento, RenderWindow &win)override;
	
	void Cargar_records();
	void Ordenar_records();
	void Guardar_records();
	void Crear_record_tabla();
private:
	vector<Jugador> Jugadores;	
	Font Fuente_tabla;
	Boton boton_volver;
	Texture textura_volver;
	Sprite s_volver;
	
	vector<Text> vt_nombres,vt_puntos;
};

#endif

