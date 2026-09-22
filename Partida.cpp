#include "Partida.h"
#include "Auto.h"
#include "Obstaculo.h"
#include "Asfalto.h"
#include "Obstaculo_auto.h"
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include "FinDelJuego.h"
#include <cmath>
#include "Obstaculo_objeto.h"
#include "Configuraciones.h"
#include <SFML/Window/Keyboard.hpp>
using namespace std;
using namespace sf;
struct Estado_configuracion{
	bool controles, sonido;
};
Partida::Partida() : asf1(true), asf2(false){
	ifstream archi("textura_obstaculos.txt");
	if(!archi.is_open()){
		throw runtime_error("Error al abrir textura_obstaculos.txt");
	}
	string nombre_obstaculo;
	while(getline(archi,nombre_obstaculo)){
		auto t_obstaculo = make_unique<Texture>(); 
		t_obstaculo -> loadFromFile(nombre_obstaculo);
		v_texturas.push_back(move(t_obstaculo));
	}
	archi.close();

	
	ifstream archivo("textura_obstaculo_objetos.txt");
	if(!archivo.is_open()){
		throw runtime_error("Error al abrir textura_obstaculo_objetos.txt");
	}
	string nombre_objeto;
	while(getline(archivo,nombre_objeto)){
		auto t_obs_objeto = make_unique<Texture>();
		t_obs_objeto -> loadFromFile(nombre_objeto);
		v_texturas_obj.push_back(move(t_obs_objeto));
	}
	archivo.close();
	
	Cargar_record();
}

bool Partida::Preguntar_reloj_autos(){
	if(Cronometro.Puntaje_actual()>=100) frecuencia = 1600+rand()%(1900-1600+1);
	if(Cronometro.Puntaje_actual()>=4500) frecuencia = 1400+rand()%(1600-1400+1);
	if(Cronometro.Puntaje_actual()>=8000) frecuencia = 1000+rand()%(1200-1000+1);
	if(reloj_partida_autos.getElapsedTime().asMilliseconds()<frecuencia){
		return false;
	}
	reloj_partida_autos.restart();
	return true;
}
bool Partida::Preguntar_reloj_objetos(){
	if(Cronometro.Puntaje_actual()>=100) frecuencia_objetos = 7300+rand()%(7500-7300+1);
	if(Cronometro.Puntaje_actual()>=4500) frecuencia_objetos = 7000+rand()%(7300-7000+1);
	if(reloj_partida_objetos.getElapsedTime().asMilliseconds()<frecuencia_objetos){
		return false;
	}
	reloj_partida_objetos.restart();
	return true;
}

bool Partida::Ralentizar(){
	if(reloj_ralentizar.getElapsedTime().asMilliseconds()<10000){return false;}
	reloj_ralentizar.restart();
	return true;
}

FloatRect Partida::Disminuir_hitbox_valla(FloatRect rectangulo){
	float nuevo_ancho = rectangulo.width * 0.8;
	float nueva_altura = rectangulo.height * 0.45;
	
	float setX = (rectangulo.width - nuevo_ancho) / 2;
	float setY = (rectangulo.height - nueva_altura) / 2;
	
	return FloatRect(rectangulo.left + setX, rectangulo.top + setY, nuevo_ancho, nueva_altura);
}
FloatRect Partida::Disminuir_hitbox(FloatRect rectangulo){
	FloatRect limites = rectangulo;
	float nuevo_ancho = limites.width * 0.45;
	float nueva_altura = limites.height * 0.80;
	
	float setX = (limites.width - nuevo_ancho) / 2;
	float setY = (limites.height - nueva_altura) / 2;
	
	return FloatRect(limites.left + setX, limites.top + setY, nuevo_ancho, nueva_altura);
}
FloatRect Partida::Disminuir_hitbox2(FloatRect rectangulo){
	FloatRect limites = rectangulo;
	float nuevo_ancho = limites.width * 0.45;
	float nueva_altura = limites.height;
	
	float setX = (limites.width - nuevo_ancho) / 2;
	float setY = (limites.height - nueva_altura) / 2;
	
	return FloatRect(limites.left + setX, limites.top + setY, nuevo_ancho, nueva_altura);
}

FloatRect Partida::Hitbox_obstaculo(FloatRect rectangulo, string tipo){
	FloatRect limites = rectangulo;
	
	if(tipo == "cono" || tipo=="pozo"){
		float nuevo_ancho = limites.width * 0.45;
		float nueva_altura = limites.height * 1.5;
		
		float setX = (limites.width - nuevo_ancho) / 2;
		float setY = (limites.height - nueva_altura);
		
		return FloatRect(limites.left + setX, limites.top + setY, nuevo_ancho, nueva_altura);
	}
	if(tipo == "valla"){
		float nuevo_ancho = limites.width * 0.80;
		float nueva_altura = limites.height * 1.5;
		
		float setX = (limites.width - nuevo_ancho) / 2;
		float setY = (limites.height - nueva_altura + 200);
		
		return FloatRect(limites.left + setX, limites.top + setY, nuevo_ancho, nueva_altura);
	}
}

FloatRect Partida::Eliminar_hitbox(FloatRect rectangulo){
	return FloatRect(rectangulo.left, rectangulo.top, 0, 0);
}

bool Partida::Detectar_choque(Auto &auto_player, Obstaculo_auto &obs_auto){
	
	FloatRect hitbox_player = Disminuir_hitbox(auto_player.Ver_Rectangulo_a());
	FloatRect hitbox_obstaculo = Disminuir_hitbox(obs_auto.Ver_Rectangulo_o());
	
	return hitbox_player.intersects(hitbox_obstaculo);
}
bool Partida::Detectar_distancia(Obstaculo_auto &obs_auto, Obstaculo_objeto &obs_objeto){
	FloatRect hitbox_auto_obs = Disminuir_hitbox(obs_auto.Ver_Rectangulo_o());
	FloatRect hitbox_objeto_obs = Hitbox_obstaculo(obs_objeto.Ver_Rectangulo_o(), obs_objeto.Ver_tipo());
	
	return hitbox_auto_obs.intersects(hitbox_objeto_obs);
}

pair<bool,string> Partida::Choque_obstaculo(Auto &auto_player, Obstaculo_objeto &obs_objeto){
	FloatRect hitbox_player = Disminuir_hitbox(auto_player.Ver_Rectangulo_a());
	FloatRect hitbox_obstaculo;
	if(obs_objeto.Ver_tipo()=="valla"){
		hitbox_obstaculo = Disminuir_hitbox_valla(obs_objeto.Ver_Rectangulo_o());
	}else{
		hitbox_obstaculo = Disminuir_hitbox(obs_objeto.Ver_Rectangulo_o());
	}
	
	return {hitbox_player.intersects(hitbox_obstaculo),obs_objeto.Ver_tipo()};
}

float Partida::Reaccion(Obstaculo_auto &obs_auto, Obstaculo_objeto &obs_obj){
	return obs_auto.Ver_posicion().x - obs_obj.Ver_posicion().x;
}


bool Partida::Auto_reaccion(int pos ,vector<Obstaculo_auto>&v_autos){
	FloatRect hitbox_auto = v_autos[pos].Ver_Rectangulo_o();
	for(size_t i=0;i<v_autos.size();i++) { 
		if(i!=pos){
			FloatRect hitbox_auto_otro = v_autos[i].Ver_Rectangulo_o();
			if(hitbox_auto.intersects(hitbox_auto_otro)){
				return true;
			}
		}
	}
	return false;
}

void Partida::Guardar_record(){
	ofstream archivo("record.dat", ios::binary);
	if(!archivo.is_open()){
		throw runtime_error("No se pudo abrir 'record.dat'");
	}
	archivo.write(reinterpret_cast<char*>(&p_record),sizeof(p_record));
	archivo.close();
}

void Partida::Cargar_record(){
	ifstream archivo2("record.dat", ios::binary);
	if(!archivo2.is_open()){
		throw runtime_error("No se pudo abrir 'record.dat'");
	}
	archivo2.read(reinterpret_cast<char*>(&p_record),sizeof(p_record));
	archivo2.close();
	
	fuente_record.loadFromFile("Tipografia/static/Asap_Condensed-Black.ttf");
	texto_record.setFont(fuente_record);
	texto_record.setCharacterSize(30);
	texto_record.setFillColor({0,0,0});
	texto_record.setPosition(1720, 0);  // Ajusta la posición en pantalla
	texto_record.setString("Record: " + to_string(p_record));
}

void Partida::Guardar_ultima_puntuacion(){
	ofstream archivo("puntuacion.dat", ios::binary);
	if(!archivo.is_open()){
		throw runtime_error("No se pudo abrir 'puntuacion.dat'");
	}
	archivo.write(reinterpret_cast<char*>(&puntuacion),sizeof(puntuacion));
	archivo.close();
}
void Partida::Cargar_objetos(){
	if(Cronometro.Puntaje_actual()>=800 && cantidad_objetos < 1) cantidad_objetos = 1;
	vector<Obstaculo_objeto> v_objeto_aux;
	int contador;
	for(int i=0;i<cantidad_objetos;){
		int indice = rand() % 3;
		string tipo;
		if(indice == 0){
			tipo = "cono";
		}
		if(indice == 1){
			tipo = "pozo";
		}
		if(indice == 2){
			tipo = "valla";
		}
		Obstaculo_objeto objeto_obs(*v_texturas_obj[indice],tipo);
		contador=0;
		if(i!=0){
			for(size_t j=0;j<v_objeto_aux.size();j++) { 
				FloatRect hitbox_ultimo_obstaculo = objeto_obs.Ver_Rectangulo_o();
				FloatRect hitbox_anterior_obstaculo = v_objeto_aux[j].Ver_Rectangulo_o();
				hitbox_ultimo_obstaculo = Disminuir_hitbox(hitbox_ultimo_obstaculo);
				hitbox_anterior_obstaculo = Disminuir_hitbox(hitbox_anterior_obstaculo);
				
				if(!hitbox_ultimo_obstaculo.intersects(hitbox_anterior_obstaculo)){
					contador++;
				}
			}
		}
		if(contador==v_objeto_aux.size()){
			v_objeto_aux.push_back(objeto_obs);
			i++;
		}
	}
	for(size_t i=0;i<v_objeto_aux.size();i++) { 
		v_objeto.push_back(v_objeto_aux[i]);
	}
}

void Partida::Cargar_obstaculos(Obstaculo_objeto &objeto){                      //objeto y que lo reciba en el bucle del actualizar
	if(Cronometro.Puntaje_actual()>=100 && cantidad < 1) cantidad = 1;
	if(Cronometro.Puntaje_actual()>=5000 && cantidad < 2) cantidad = 2;
	if(Cronometro.Puntaje_actual()>=20000 && cantidad < 3) cantidad  = 3;
	
	vector<Obstaculo_auto> v_obs_aux;
	
	int contador_obstaculo;
	for(int i=0;i<cantidad;){
		Obstaculo_auto auto_obs(*v_texturas[rand()%7]);
		contador_obstaculo=0;
		
		if(i!=0){
			for(size_t j=0;j<v_obs_aux.size();j++) { 
				FloatRect hitbox_ultimo_obstaculo = auto_obs.Ver_Rectangulo_o();
				FloatRect hitbox_anterior_obstaculo = v_obs_aux[j].Ver_Rectangulo_o();
				hitbox_ultimo_obstaculo = Disminuir_hitbox2(hitbox_ultimo_obstaculo);
				hitbox_anterior_obstaculo = Disminuir_hitbox2(hitbox_anterior_obstaculo);
				
				FloatRect hitbox_objeto = objeto.Ver_Rectangulo_o();
				if(!hitbox_ultimo_obstaculo.intersects(hitbox_objeto)){
					if(!hitbox_ultimo_obstaculo.intersects(hitbox_anterior_obstaculo)){
						contador_obstaculo++;
					}
				}
			}
		}
		if(contador_obstaculo==v_obs_aux.size()){
			v_obs_aux.push_back(auto_obs);
			i++;
		}
	}
	for(size_t i=0;i<v_obs_aux.size();i++) { 
		v_obstaculo.push_back(v_obs_aux[i]);
	}
}
void Partida::Cargar_obstaculos(){                     
	if(Cronometro.Puntaje_actual()>=100 && cantidad < 1) cantidad = 1;
	if(Cronometro.Puntaje_actual()>=5000 && cantidad < 2) cantidad = 2;
	if(Cronometro.Puntaje_actual()>=20000 && cantidad < 3) cantidad  = 3;
	
	vector<Obstaculo_auto> v_obs_aux;
	
	int contador_obstaculo;
	for(int i=0;i<cantidad;){
		Obstaculo_auto auto_obs(*v_texturas[rand()%7]);
		contador_obstaculo=0;
		
		if(i!=0){
			for(size_t j=0;j<v_obs_aux.size();j++) { 
				FloatRect hitbox_ultimo_obstaculo = auto_obs.Ver_Rectangulo_o();
				FloatRect hitbox_anterior_obstaculo = v_obs_aux[j].Ver_Rectangulo_o();
				hitbox_ultimo_obstaculo = Disminuir_hitbox2(hitbox_ultimo_obstaculo);
				hitbox_anterior_obstaculo = Disminuir_hitbox2(hitbox_anterior_obstaculo);
				
				if(!hitbox_ultimo_obstaculo.intersects(hitbox_anterior_obstaculo)){
					contador_obstaculo++;
				}
			}
		}
		if(contador_obstaculo==v_obs_aux.size()){
			v_obs_aux.push_back(auto_obs);
			i++;
		}
	}
	for(size_t i=0;i<v_obs_aux.size();i++) { 
		v_obstaculo.push_back(v_obs_aux[i]);
	}
}

void Partida::Borrar_obstaculos(){
	for(size_t i=0;i<v_obstaculo.size();){    
		Vector2f pos_obs = v_obstaculo[i].Ver_posicion();
		if(pos_obs.y > 2200){
			v_obstaculo.erase(v_obstaculo.begin()+i);
		} else {i++;}
	}
	
	for(size_t i=0;i<v_objeto.size();){    
		Vector2f pos_obs = v_objeto[i].Ver_posicion();
		if(pos_obs.y > 2200){
			v_objeto.erase(v_objeto.begin()+i);
		} else {i++;}
	}
}
	

void Partida::Explosion(Auto &player, Obstaculo_auto &obs_choque){
	t_explosion.loadFromFile("imagenes/explosion.png");
	s_explosion.setTexture(t_explosion);
	
	s_explosion.setPosition(Pos_choque(player, obs_choque));
	
	s_explosion.setScale(0.15,0.15);
	s_explosion.setOrigin(960,540);
	reloj_explosion.restart();
	
	en_explosion=true;
}
Vector2f Partida::Pos_choque(Auto &player, Obstaculo_auto &obs_choque){
	Vector2f obs = obs_choque.Ver_posicion();
	Vector2f pyr = player.Pos_jugador();
	
	Vector2f promedio = (obs + pyr) / 2.0f;
	promedio.x+=25;
	return promedio;
}

void Partida::Actualizar(Juego &j, RenderWindow &win){
	win.setFramerateLimit(60);
	bool control_WASD=Configuraciones::Instancia().Ver_WASD();
	if(!en_explosion){
		asf1.Movimiento();
		asf2.Movimiento();
		if(control_WASD){
			auto_jugador.Desplazar(Keyboard::W,Keyboard::S,Keyboard::D,Keyboard::A);
		}else{auto_jugador.Desplazar(Keyboard::Up,Keyboard::Down,Keyboard::Right,Keyboard::Left);}
	}
	
	Vector2f posicion_actual_asf1 = asf1.Mostrar_Posicion();
	Vector2f posicion_final(960,1080);
	if(posicion_actual_asf1 == posicion_final){
		asf1.Resetear_posicion(); 
	}
	Vector2f posicion_actual_asf2 = asf2.Mostrar_Posicion();					//se encarga de ir generando la carretera de fondo
	if(posicion_actual_asf2 == posicion_final){
		asf2.Resetear_posicion();
	} 													
	if(!en_explosion){
		Cronometro.Actualizar();
	}
	p_actual = Cronometro.Puntaje_actual();
	if(!m_generar){
		if(Preguntar_reloj_autos()==true){
			if(!v_objeto.empty()){
				for(size_t i=0;i<v_objeto.size();i++) {
					Cargar_obstaculos(v_objeto[i]);								//se encarga de la generacion de los autos
				}
			}else{
				Cargar_obstaculos();
			}
		}
	}
	if(Preguntar_reloj_objetos()==true){
		Cargar_objetos();
	}
	
	for(size_t i=0;i<v_obstaculo.size();i++) { 
		if(!en_explosion){
			if(!detener_autos){
				v_obstaculo[i].Desplazamiento();
			}
		}
	}
	for(size_t i=0;i<v_objeto.size();i++) { 
		if(!en_explosion){
			v_objeto[i].Desplazamiento();
		}
	}
	if (en_explosion) {
		float tiempo = reloj_explosion.getElapsedTime().asSeconds();
		
		if (tiempo < 0.5) {
			s_explosion.setScale(0.15, 0.15);
		} else if (tiempo < 1.0) {
			s_explosion.setScale(0.3, 0.3);
		} else if (tiempo < 1.5) {
			s_explosion.setScale(0.15, 0.15);
		} else {
			en_explosion = false;
			Musica::Instancia().Volumen_off();
			j.Cambiar_escena(new FinDelJuego);
			return; // Terminar la función tras cambiar de escena
		}
		
		return; // Evita que siga ejecutando lógica mientras la explosión ocurre
	}
	
	// Detección de colisiones con autos obstáculo
	for (size_t i = 0; i < v_obstaculo.size(); i++) {
		if (Detectar_choque(auto_jugador, v_obstaculo[i])) {
			puntuacion = Cronometro.Puntaje_actual();
			Guardar_ultima_puntuacion();
			if (p_actual > p_record) {
				p_record = p_actual;
				Guardar_record();
			}
			
			Explosion(auto_jugador, v_obstaculo[i]); // Inicia la explosión
		}
	}
	if(!en_explosion){
		for(size_t i=0;i<v_obstaculo.size();i++) { 
			for(size_t j=0;j<v_objeto.size();j++) { 
				if(Detectar_distancia(v_obstaculo[i],v_objeto[j])){
					if(v_objeto[j].Ver_tipo() == "cono" || v_objeto[j].Ver_tipo() == "pozo"){
						if(Reaccion(v_obstaculo[i],v_objeto[j])>0){
							v_obstaculo[i].Reaccion_derecha();
							if(Auto_reaccion(i,v_obstaculo)){
								v_obstaculo[i].Detener();
							}
						}
						if(Reaccion(v_obstaculo[i],v_objeto[j])<0){
							v_obstaculo[i].Reaccion_izquierda();
							if(Auto_reaccion(i,v_obstaculo)){
								v_obstaculo[i].Detener();
							}
						}
					}
					if(v_objeto[j].Ver_tipo() == "valla"){
						detener_autos = true;
						v_obstaculo[i].Detener();
					}
				} else{
					v_obstaculo[i].Corregir_inclinacion();
					detener_autos = false;
				}
			}
		}
	}
	for (size_t i=0; i < v_objeto.size(); i++) { 
		pair<bool, string> par_choque = Choque_obstaculo(auto_jugador, v_objeto[i]);
		
		if (par_choque.first && (par_choque.second == "cono")) {
			Eliminar_hitbox(v_objeto[i].Ver_Rectangulo_o()); 
			v_objeto[i].Tumbar_cono();
			m_ralentizar = true; 
			m_generar = true;
			win.setFramerateLimit(30);
			
			reloj_ralentizar.restart(); 
		}
		if (par_choque.first && (par_choque.second == "pozo")) {
			Eliminar_hitbox(v_objeto[i].Ver_Rectangulo_o()); 
			m_ralentizar = true; 
			m_generar = true;
			win.setFramerateLimit(30);
			
			reloj_ralentizar.restart(); 
		}
		if(par_choque.first and par_choque.second=="valla"){
			puntuacion = Cronometro.Puntaje_actual();
			Guardar_ultima_puntuacion();
			if(p_actual > p_record){                                            //detecta los choques y cambia de escena al final del juego
				p_record = p_actual;
				Guardar_record();
			}
			j.Cambiar_escena(new FinDelJuego);
		}
	}
	if (m_ralentizar) {
		if (reloj_ralentizar.getElapsedTime().asMilliseconds() > 1500) {
			m_ralentizar = false; 
			m_generar = false;
			win.setFramerateLimit(60);
		} else {
			for (size_t i = 0; i < v_obstaculo.size(); i++) {
				v_obstaculo[i].Desplazamiento_lento(); 
			}
		}
	}
	Borrar_obstaculos();														
};



void Partida::Dibujar(RenderWindow &win){
	asf1.Dibujar(win);
	asf2.Dibujar(win);
	for(size_t i=0;i<v_objeto.size();i++) { 
		v_objeto[i].Dibujar(win);
	}
	for(size_t i=0;i<v_obstaculo.size();i++) { 
		v_obstaculo[i].Dibujar(win);
	}
	auto_jugador.Dibujar(win);
	win.draw(texto_record);
	Cronometro.Dibujar(win);
	win.draw(s_explosion);
};
