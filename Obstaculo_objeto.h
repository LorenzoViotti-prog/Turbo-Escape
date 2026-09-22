#ifndef OBSTACULO_OBJETO_H
#define OBSTACULO_OBJETO_H
#include "Obstaculo.h"
#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
using namespace std;

class Obstaculo_objeto : public Obstaculo {
public:
	Obstaculo_objeto(Texture &nombre, string &tipo);
	
	void Desplazamiento()override;
	FloatRect Ver_Rectangulo_o()override;	
	Vector2f Aparecer(string tipo_obstaculo)override;
	Vector2f Ver_posicion()override;
	
	void Tumbar_cono();
	string Ver_tipo();
private:
	vector<Texture>v_textura_aparecer;
	string tipo;
};

#endif

