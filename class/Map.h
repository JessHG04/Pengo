#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "tinyxml2.h"
#include "Block.h"

class Map{
    
    private:
        //static Map *map;
        sf::VertexArray vertex;
        sf::Texture tile;
        
    public:
        Map();
        ~Map();
        void readMap(int );
        //void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        //void drawBloques(sf::RenderWindow &);
        void ReinicioNivel();
        //void Vacio();
        //void MarcarBloques(int );
        //void clearMap();
        tinyxml2::XMLNode *nodo;
        tinyxml2::XMLElement *data;
        int blocks [15][13];
        int restartBlocks [15][13];
        //std::vector<std::vector<Block*>> bloques;
        //std::vector<std::vector<Block*>> bloquesReinicio;
        //std::vector<std::vector<Block*>> borde;
};