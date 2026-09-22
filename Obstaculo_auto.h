#ifndef OBSTACULO_AUTO_H
#define OBSTACULO_AUTO_H
#include "Obstaculo.h"
#include <string>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
using namespace std;

class Obstaculo_auto : public Obstaculo{
public:
	Obstaculo_auto(Texture &nombre);
	void Desplazamiento()override;
	FloatRect Ver_Rectangulo_o()override;
	Vector2f Ver_posicion()override;
	Vector2f Aparecer(string tipo_obstaculo)override;
	
	void Desplazamiento_lento();
	void Corregir_inclinacion();
	void Reaccion_derecha();
	void Reaccion_izquierda();
	void Detener();
private:
	Clock reloj_reaccion;
};

#endif

