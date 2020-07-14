#pragma once
#include <SFML/Graphics.hpp>



class Block {

    protected:
        sf::Sprite *block;
        float speed;            // Movement speed
        int direction;          // Displacement direction
        float path;
        bool canCollide;
        sf::Vector2i* position;


    public:
        Block(sf::Texture* , int , int );
        virtual ~Block();
        virtual void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        void setDirection(int direction);
        int getDirection();
        bool getCanCollide();
        void dontCollide();
        void setPosition(sf::Vector2i );
        sf::Vector2i getPosition();
        sf::Sprite* getSprite();
};
