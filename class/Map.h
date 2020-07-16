#pragma once
#include <SFML/Graphics.hpp>
#include "IceBlock.h"

class Map {

    private:
        sf::Sprite *leftWall;
        sf::Sprite *rightWall;
        sf::Sprite *topWall;
        sf::Sprite *bottomWall;
        bool isHit;
        Bloque ***glacier;
        sf::Vector2u size;
        std::vector<Bloque*> icicles;  // Remains of ice blocks


    public:
        Map(sf::Texture* , int[15][13]);
        ~Map();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        bool checkPosition(sf::Vector2i );
        void pengoPush(sf::Vector2i ,int ,bool );
        Bloque* getBlock(unsigned int, unsigned int);
        sf::Vector2i getFreePosition();
};