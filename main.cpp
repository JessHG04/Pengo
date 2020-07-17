#include <SFML/Graphics.hpp>
#include "class/Juego.h"

int main() {
    srand(time(NULL));
    Juego* juego = Juego::getInstancia();

    return EXIT_SUCCESS;
}