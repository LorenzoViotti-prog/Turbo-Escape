#include "Juego.h"
#include "Menu.h"

int main(int argc, char *argv[]){
	Juego j(new Menu); //empieza con menu
	j.jugar();
	return 0;
}

