#include "Block.h"

Block::Block(sf::Texture* texture, int x, int y) {
    direction  = -1;
    speed      = 250.0f;
    canCollide = false;
    position   = new sf::Vector2i(0, 0);
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(16, 16, 16, 16));
    block->setOrigin(8, 8);
    block->setPosition(16+x*16, 40+y*16);
}

void Block::setPosition(sf::Vector2i position) {
    this->position->x = position.x;
    this->position->y = position.y;
}