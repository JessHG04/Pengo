#include "Character.h"



Character::Character(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position) {

    // Initial values...
    this->row      = (coordPj.y > 1) ? 1 : 0;
    this->column   = 0;
    this->speed    = speed;
    isWalking      = false;
    isPushing      = false;
    isStunned      = false;
    path           = 0.0f;
    this->position = position;

    // Create the character...
    body          = new sf::Sprite(*texture);
    animation     = new Animation(texture, coordPj, changeTime, 2);
    body->setTextureRect(animation->getUVRect());
    body->setOrigin(animation->getOrigin());
    body->setPosition(16+position.y*16, 40+position.x*16);
}



Character::~Character() {

    // Virtual destructor

}



void Character::Update(float deltaTime, Labyrinth* labyrinth) {
    
}



void Character::Draw(sf::RenderWindow &window) {
    window.draw(*body);
}



sf::Vector2i Character::getPosition() {
    return position;
}



sf::Sprite* Character::getSprite() {
    return body;
}



bool Character::getStunned() {
    return isStunned;
}