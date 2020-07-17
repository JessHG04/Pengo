#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BRoto.h"

class Mapa {
    private:
        Bloque ***bloques;
        Bloque ***borde;
        std::vector<Bloque*> restos;

    public:
        Mapa(sf::Texture* , int[15][13]);
        ~Mapa();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        bool comprobar(sf::Vector2i );
        void empujar(sf::Vector2i, int, bool, bool);
        sf::Vector2i getLibre();
        Bloque* getBloque(int x, int y)      {return bloques[x][y];};
};