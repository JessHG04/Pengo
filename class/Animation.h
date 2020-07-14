#pragma once
#include <SFML/Graphics.hpp>

class Animation {

    private:
        sf::IntRect uvRect;
        float switchTime;
        float totalTime;
        sf::Vector2u actualCoord;
        sf::Vector2u coordPj;
        sf::Vector2u range;

    public:
        Animation(sf::Texture* ,sf::Vector2u ,float ,int );
        void Update(int, int, float );
        ~Animation()                    { };
        sf::IntRect getUVRect()         {return uvRect;};
        sf::Vector2f getOrigin()        {return sf::Vector2f(uvRect.width/2, uvRect.height/2);};
        void setSwitchTime(float )      {this->switchTime = switchTime;};
        void setCoordPj(sf::Vector2u )  {this->coordPj = coordPj;};
};
