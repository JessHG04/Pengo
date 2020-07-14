#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Pengo.h"


class SnoBee : public Character {

    private:
        //Pengo* pengo;
        int direction; // 0:Up - 1:Right - 2:Down - 3:Left
        bool isStatic;
        bool isDead;
        Block* bomb;


    public:
        SnoBee(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        ~SnoBee();
        void Update(float ,Map* );
        void getSmashed(Block* );
        bool getFree();
        bool getDead();
};