#pragma once
#include <SFML/Graphics.hpp>
#include "Bloque.h"


class IceBlock : public Bloque {

    private:
        bool isBreaking;
        bool isBroke;
        sf::Clock clock;

    public:
        IceBlock(sf::Texture* , int, int );
        ~IceBlock();
        void Update(float deltaTime);
        void breakDown();
        bool getBroke();
        bool getBreaking();
};
