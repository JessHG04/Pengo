#pragma once
#include <SFML/Graphics.hpp>

class Animation {

    private:
        sf::IntRect uvRect;
        float changeTime;
        float totalTime;
        sf::Vector2u actualCoord;   // Actual coordinates of rectangle
        sf::Vector2u coordPj;       // Pj located on the texture
        sf::Vector2u range;         // Number of rectangle to draw


    public:
        Animation(sf::Texture* ,sf::Vector2u ,float ,int );
        ~Animation();
        void Update(unsigned int ,unsigned int ,float );
        sf::IntRect getUVRect();
        sf::Vector2f getOrigin();
        void setChangeTime(float );
        void setCoordPj(sf::Vector2u );
};
