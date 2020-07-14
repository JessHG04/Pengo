#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"


class IceBlock : public Block {

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
