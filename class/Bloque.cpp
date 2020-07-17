#include "Bloque.h"

Bloque::Bloque(sf::Texture* texture, int x, int y, bool borde) {
    direccion = -1;
    velocidad = 250.0f;
    movimiento = false;
    posicion = new sf::Vector2i(0, 0);
    sprite = new sf::Sprite(*texture);
    if(borde){
        sprite->setTextureRect(sf::IntRect(0*16, 6*16, 16, 16));
    }else{
        sprite->setTextureRect(sf::IntRect(0*16, 3*16, 16, 16));
    }
    sprite->setOrigin(8, 8);
    if(borde){
        sprite->setPosition(32+x*16, 48+y*16);
    }else{
        sprite->setPosition(48+x*16, 64+y*16);
    }
}

void Bloque::setPosicion(sf::Vector2i pos) {
    posicion->x = pos.x;
    posicion->y = pos.y;
}