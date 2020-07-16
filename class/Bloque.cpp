#include "Bloque.h"

Bloque::Bloque(sf::Texture* texture, int x, int y) {
    direccion = -1;
    velocidad = 250.0f;
    movimiento = false;
    posicion = new sf::Vector2i(0, 0);
    sprite = new sf::Sprite(*texture);
    //sprite->setTextureRect(sf::IntRect(0*16, 9*16, 16, 16));
    sprite->setTextureRect(sf::IntRect(16, 16, 16, 16));
    sprite->setOrigin(8, 8);
    sprite->setPosition(16+x*16, 40+y*16);
}

void Bloque::setPosicion(sf::Vector2i pos) {
    posicion->x = pos.x;
    posicion->y = pos.y;
}