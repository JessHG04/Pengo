#include <SFML/Graphics.hpp>
#include "class/Game.h"

int main() {
    srand(time(NULL));
    Game* game = Game::getInstance();

    return EXIT_SUCCESS;
}