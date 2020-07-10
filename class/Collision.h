#pragma once
#include <math.h>
#include "Pengo.h"
#include "SnoBee.h"
#include "Block.h"


class Collision {

    private:


    public:
        Collision();
        ~Collision();
        bool checkCollision(sf::Sprite* ,sf::Sprite* ,float );
};