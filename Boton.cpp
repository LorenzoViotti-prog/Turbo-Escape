#include "Boton.h"
using namespace sf;
using namespace std;

Boton::Boton(Vector2f tamanio, Vector2f posicion, string texto_boton, int tamanio_texto, Color color_boton, Color color_texto, string fuente_boton) {
	rectangulo.setSize(tamanio);
	rectangulo.setPosition(posicion);
	rectangulo.setFillColor(color_boton);
	
	if(!fuente.loadFromFile(fuente_boton)){
		throw runtime_error("No se pudo cargar la fuente");
	}
	texto.setFont(fuente);
	texto.setString(texto_boton);
	texto.setCharacterSize(tamanio_texto);
	texto.setFillColor(color_texto);
	
	
	FloatRect textBounds = texto.getLocalBounds();
	texto.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	texto.setPosition(posicion.x + tamanio.x / 2, posicion.y + tamanio.y / 2);
}

void Boton::Dibujar(RenderWindow &win){
	win.draw(rectangulo);
	win.draw(texto);
}

bool Boton::Contiene(Vector2f &punto){
	return rectangulo.getGlobalBounds().contains(punto);
}
