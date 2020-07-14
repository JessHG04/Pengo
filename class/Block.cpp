#include "Block.h"



Block::Block(sf::Texture* texture, int x, int y) {

    // Initial values
    direction  = -1;
    speed      = 250.0f;
    canCollide = false;
    position   = new sf::Vector2i(0, 0);
    

    // Building ice block
    block = new sf::Sprite(*texture);
    block->setTextureRect(sf::IntRect(16, 16, 16, 16));
    block->setOrigin(8, 8);
    block->setPosition(16+x*16, 40+y*16);
}



Block::~Block() {
    
}



void Block::Update(float deltaTime) {
    
}



void Block::Draw(sf::RenderWindow &window) {
    window.draw(*block);
}



void Block::setDirection(int direction) {
    this->direction = direction;
}



int Block::getDirection() {
    return direction;
}



bool Block::getCanCollide() {
    return canCollide;
}



void Block::dontCollide() {
    canCollide = false;
}



void Block::setPosition(sf::Vector2i position) {
    this->position->x = position.x;
    this->position->y = position.y;
}



sf::Vector2i Block::getPosition() {
    return *position;
}



sf::Sprite* Block::getSprite() {
    return block;
}