#pragma once
#include <SFML/Graphics.hpp>

class Block {
    protected:
        sf::Sprite *block;
        float speed;
        int direction;
        float path;
        bool canCollide;
        sf::Vector2i* position;

    public:
        Block(sf::Texture* , int , int );
        virtual ~Block()                        {};
        virtual void Update(float deltaTime)    {};
        void Draw(sf::RenderWindow &window)     {window.draw(*block);};
        void setDirection(int dir)              {direction = dir;};
        int getDirection()                      {return direction;};
        bool getCanCollide()                    {return canCollide;};
        void dontCollide()                      {canCollide = false;};
        void setPosition(sf::Vector2i );
        sf::Vector2i getPosition()              {return *position;};
        sf::Sprite* getSprite()                 {return block;};
};
