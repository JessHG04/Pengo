#include "Character.h"



Character::Character(sf::Texture *texture, float speed, float switchTime, sf::Vector2u coordPj, sf::Vector2i position) {
    this->row      = (coordPj.y > 1) ? 1 : 0;
    this->column   = 0;
    this->speed    = speed;
    isWalking      = false;
    isPushing      = false;
    isStunned      = false;
    path           = 0.0f;
    this->position = position;
    body          = new sf::Sprite(*texture);
    animation     = new Animacion(texture, coordPj, switchTime, 2);
    //animation = new Animacion(texture, coordPj, switchTime, 2);
    body->setTextureRect(animation->getUvRect());
    body->setOrigin(8,8);
    body->setPosition(16+position.y*16, 40+position.x*16);
}

Character::~Character() {

}

void Character::Update(float deltaTime, Map* map) {
    
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