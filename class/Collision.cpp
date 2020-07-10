#include "Collision.h"



Collision::Collision() {

}



Collision::~Collision() {

}



// Collision between two sprites with a minimun distance
bool Collision::checkCollision(sf::Sprite* sprite1, sf::Sprite* sprite2, float minimum) {
    sf::Vector2f _distanceCoord;
    float _distance;
    bool _colliding = false;


    // Global bounding collision...
    if (sprite1->getGlobalBounds().intersects(sprite2->getGlobalBounds())) {

        // AABB collision...
        _distanceCoord = sprite1->getPosition() - sprite2->getPosition();
        _distance = sqrt(pow(abs(_distanceCoord.x),2) + pow(abs(_distanceCoord.y),2));

        if (_distance <= minimum)
            _colliding = true;
    }

    return _colliding;
}
