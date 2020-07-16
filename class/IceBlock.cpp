#include "IceBlock.h"



IceBlock::IceBlock(sf::Texture* texture, int x, int y) : Bloque(texture, x, y) {

    // Initial values
    isBreaking = false;
    isBroke    = false;
    recorrido       = 0.0f;
}



IceBlock::~IceBlock() {
    delete sprite;
    sprite = NULL;
    delete posicion;
    posicion = NULL;
}



void IceBlock::Update(float deltaTime) {
    if (!isBroke  &&  !isBreaking) {

        if (direccion > -1) {
            float _displacement = velocidad*deltaTime;

            // Calculate the block position
            if (_displacement+recorrido >= 16.0f) {
                _displacement  = 16.0f - recorrido;
                recorrido           = 0.0f;
                movimiento     = true;

                if (direccion == 0) {
                    posicion->x--;
                } else if (direccion == 1) {
                    posicion->y++;
                } else if (direccion == 2) {
                    posicion->x++;
                } else if (direccion == 3) {
                    posicion->y--;
                }

            } else {
                recorrido += _displacement;
                movimiento = false;
            }

            switch (direccion) {
                case 0:
                    sprite->move(0, -_displacement);
                    break;
                case 1:
                    sprite->move(_displacement, 0);
                    break;
                case 2:
                    sprite->move(0, _displacement);
                    break;
                case 3:
                    sprite->move(-_displacement, 0);
                    break;
            }
        }
    } else if (isBreaking) {
        if (clock.getElapsedTime().asSeconds() > 0.05f) {
            sf::IntRect _cutout = sprite->getTextureRect();
            _cutout.left += 16;
            if (_cutout.left <= 160) {
                sprite->setTextureRect(_cutout);
            } else {
                isBreaking = false;
                isBroke    = true;
            }
            clock.restart();
        }
    }
}



void IceBlock::breakDown() {
    isBreaking = true;
}



bool IceBlock::getBroke() {
    return isBroke;
}



bool IceBlock::getBreaking() {
    return isBreaking;
}