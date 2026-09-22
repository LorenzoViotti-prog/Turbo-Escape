#ifndef PARTIDA_H
#define PARTIDA_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Obstaculo.h"
#include "Asfalto.h"
#include "Auto.h"
#include <vector>
#include "Obstaculo_auto.h"
#include <SFML/System/Clock.hpp>
#include "Puntaje.h"
#include "Escena.h"
#include "Juego.h"
#include "Obstaculo_objeto.h"
#include "Musica.h"
#include "Configuraciones.h"
using namespace std;
using namespace sf;

class Partida : public Escena{
public:
	Partida();
	float Reaccion(Obstaculo_auto &obs_auto, Obstaculo_objeto &obs_obj);
	void Actualizar(Juego &j, RenderWindow &win)override;
	void Guardar_record();
	void Cargar_record();
	void Guardar_ultima_puntuacion();
	void Cargar_obstaculos(Obstaculo_objeto &objeto);
	void Cargar_obstaculos();
	void Cargar_objetos();
	void Borrar_obstaculos();
	void Dibujar(RenderWindow &win);
	void Explosion(Auto &player, Obstaculo_auto &obs_choque);
	
	bool Preguntar_reloj_autos();
	bool Preguntar_reloj_objetos();
	bool Auto_reaccion(int pos ,vector<Obstaculo_auto>&v_autos);
	bool Detectar_choque(Auto &auto_player, Obstaculo_auto &obs_auto);
	bool Detectar_distancia(Obstaculo_auto &obs_auto, Obstaculo_objeto &obs_objeto);
	bool Ralentizar();
	
	FloatRect Disminuir_hitbox(FloatRect rectangulo);
	FloatRect Disminuir_hitbox2(FloatRect rectangulo);
	FloatRect Hitbox_obstaculo(FloatRect rectangulo, string tipo);
	FloatRect Eliminar_hitbox(FloatRect rectangulo);
	FloatRect Disminuir_hitbox_valla(FloatRect rectangulo);
	
	pair<bool,string> Choque_obstaculo(Auto &auto_player, Obstaculo_objeto &obs_objeto);

	Vector2f Pos_choque(Auto &player, Obstaculo_auto &obs_choque);
	Vector2f Inteseccion();
	
private:
	Asfalto asf1;
	Asfalto asf2;
	Auto auto_jugador;
	Puntaje Cronometro;


	//Puntaje puntaje; 															//para guardar record de puntaje
	int p_actual = 0;
	int p_record = 0;
	Font fuente_record;
	Text texto_record;
	Texture t_explosion;
	Sprite s_explosion;
	
	vector<Obstaculo_auto> v_obstaculo;
	vector<Obstaculo_objeto> v_objeto;
	vector<unique_ptr<Texture>> v_texturas;
	vector<unique_ptr<Texture>> v_texturas_obj;
	
	Clock reloj_partida_autos;
	Clock reloj_partida_objetos;
	Clock reloj_ralentizar;
	Clock reloj_explosion;

	bool m_ralentizar = false;
	bool m_generar = false;
	bool en_explosion=false;
	bool detener_autos = false;
	bool reaccion = false;
	
	int puntuacion=0;
	int cantidad=0;
	int cantidad_objetos=0;
	int frecuencia=1500;
	int frecuencia_objetos=2500;
	
};

#endif

