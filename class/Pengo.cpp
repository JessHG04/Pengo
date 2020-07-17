#include "Pengo.h"



Pengo::Pengo(sf::Texture *texture, float speed, float changeTime, sf::Vector2u coordPj, sf::Vector2i position) : Character(texture, speed, changeTime, coordPj, position) {
    lifes         = 3;
    //deadAnimation = new Animation(texture, coordPj, 0.2f, 2);
    deadAnimation = new Animacion(texture, coordPj, 0.2f, 2);
    isBlocked     = false;
    push          = false;
    godMode       = false;
    stunnedTime   = 2.5f;
}


Pengo::~Pengo() {
    delete deadAnimation;
    deadAnimation = NULL;
    delete animation;
    animation = NULL;
    delete body;
    body = NULL;
}



void Pengo::Update(float deltaTime, Mapa* map) {
    sf::Vector2i _auxPosition = position;
    
    if (lifes > 0  &&  (!isWalking && !isPushing && !isStunned)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            isWalking = true;
            column = 4;
            position.x--;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            isWalking = true;
            column = 6;
            position.y++;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            isWalking = true;
            column = 0;
            position.x++;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            isWalking = true;
            column = 2;
            position.y--;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            isPushing = true;
            push      = true;
            animation->setTiempoCambio(0.13f);
            row = 1;
            auxClock.restart();
        }
        
        if (map->comprobar(position)) {
            isBlocked = false;
        } else {
            isBlocked = true;
            position  = _auxPosition;
        }
    }

    if (isWalking) {
        float _displacement;

        if (path+speed*deltaTime >= 16.0f) {
            _displacement = 16.0f - path;
            isWalking     = false;
            path          = 0.0f;
        } else {
            path += speed*deltaTime;
            _displacement = speed*deltaTime;
        }

        if (!isBlocked) {
            if (column == 4)
                body->move(0, -_displacement);
            else if (column == 6)
                body->move(_displacement, 0);
            else if (column == 0)
                body->move(0, _displacement);
            else if (column == 2)
                body->move(-_displacement, 0);
        }

        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUvRect());

    } else if (isPushing) {

        if (auxClock.getElapsedTime().asSeconds() >= 0.4f) {
            isPushing = false;
            row = 0;
            animation->setTiempoCambio(0.2f);
        }

        if (push) {
            if (column == 4)
                map->empujar(sf::Vector2i(position.x-1, position.y), 0, true);
            else if (column == 6)
                map->empujar(sf::Vector2i(position.x, position.y+1), 1, true);
            else if (column == 0)
                map->empujar(sf::Vector2i(position.x+1, position.y), 2, true);
            else if (column == 2)
                map->empujar(sf::Vector2i(position.x, position.y-1), 3, true);
            push = false;
        }

        animation->Update(row, column, deltaTime);
        body->setTextureRect(animation->getUvRect());

    } else if (isStunned) {

        if (auxClock.getElapsedTime().asSeconds() >= stunnedTime) {
            isStunned = false;
            animation->Update(0, 0, deltaTime);
            body->setTextureRect(animation->getUvRect());
            if (!godMode)
                lifes--;
            body->setTextureRect(animation->getUvRect());
        } else {
            deadAnimation->Update(2, 0, deltaTime);
            body->setTextureRect(deadAnimation->getUvRect());
        }

    }
}



bool Pengo::loseLife() {
    if (lifes > 0) {
        auxClock.restart();
        isStunned = true;
        isWalking = false;
        isPushing = false;
        row       = 0;
        return true;
    } else {
        return false;
    }
}



bool Pengo::getDead() {
    if (lifes > 0) {
        return false;
    } else {
        return true;
    }
}

void Pengo::restartInitialPosition() {
    position.x = 6;
    position.y = 6;
    path       = 0.0f;
    body->setPosition(16+6*16, 40+6*16);
}

void Pengo::restoreLifes() {
    lifes = 3;
}

void Pengo::changeGodMode() {
    if (godMode) {
        godMode = false;
        stunnedTime = 2.5f;
        animation->setCuadrante(sf::Vector2u(0, 0));
        deadAnimation->setCuadrante(sf::Vector2u(0, 0));
        std::cout << "Modo Dios desactivado" << std::endl;
    } else {
        godMode = true;
        stunnedTime = 1.2f;
        animation->setCuadrante(sf::Vector2u(2, 0));
        deadAnimation->setCuadrante(sf::Vector2u(2, 0));
        std::cout << "Modo Dios activado" << std::endl;
    }
}

bool Pengo::getGodMode() {
    return godMode;
}

void Pengo::restartPosition() {
    body->setPosition(16+position.y*16, 40+position.x*16);
    path = 0.0f;
}