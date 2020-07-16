#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bloque.h"

class BRoto : public Bloque {

   private:
        bool roto;
        bool rompiendo;
        sf::Clock reloj;

    public:
        BRoto(sf::Texture* , int, int);
        ~BRoto();
        void Update(float deltaTime);
        void romper()           {rompiendo = true;};
        bool getRoto()          {return roto;};
        bool getRompiendo()     {return rompiendo;};
};
