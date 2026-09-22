#ifndef CRONOMETRO_H
#define CRONOMETRO_H
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

class Cronometro {
public:
	Cronometro();
private:
	Text texto;
	Clock cronometro;
};

#endif

