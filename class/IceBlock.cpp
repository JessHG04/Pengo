#include "IceBlock.h"



IceBlock::IceBlock(sf::Texture* texture, int x, int y) : Block(texture, x, y) {

    // Initial values
    isBreaking = false;
    isBroke    = false;
    path       = 0.0f;
}



IceBlock::~IceBlock() {
    delete block;
    block = NULL;
    delete position;
    position = NULL;
}



void IceBlock::Update(float deltaTime) {
    if (!isBroke  &&  !isBreaking) {

        if (direction > -1) {
            float _displacement = speed*deltaTime;

            // Calculate the block position
            if (_displacement+path >= 16.0f) {
                _displacement  = 16.0f - path;
                path           = 0.0f;
                canCollide     = true;

                if (direction == 0) {
                    position->x--;
                } else if (direction == 1) {
                    position->y++;
                } else if (direction == 2) {
                    position->x++;
                } else if (direction == 3) {
                    position->y--;
                }

            } else {
                path += _displacement;
                canCollide = false;
            }

            switch (direction) {
                case 0:
                    block->move(0, -_displacement);
                    break;
                case 1:
                    block->move(_displacement, 0);
                    break;
                case 2:
                    block->move(0, _displacement);
                    break;
                case 3:
                    block->move(-_displacement, 0);
                    break;
            }
        }
    } else if (isBreaking) {
        if (clock.getElapsedTime().asSeconds() > 0.05f) {
            sf::IntRect _cutout = block->getTextureRect();
            _cutout.left += 16;
            if (_cutout.left <= 160) {
                block->setTextureRect(_cutout);
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