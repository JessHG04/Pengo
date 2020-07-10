#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Labyrinth.h"


class Character {

    protected:
        float speed;
        unsigned int row;
        unsigned int column;
        Animation *animation;
        sf::Sprite *body;
        bool isWalking;
        bool isPushing;
        bool isStunned;
        sf::Vector2i position;
        float path;


    public:
        Character(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        virtual ~Character();
        virtual void Update(float ,Labyrinth* );
        void Draw(sf::RenderWindow &);
        sf::Vector2i getPosition();
        sf::Sprite* getSprite();
        bool getStunned();
};
