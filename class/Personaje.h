#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animacion.h"
#include "Mapa.h"

class Personaje{
    protected:
        sf::Sprite * sprite;
        Animacion * animacion;
        sf::Vector2i posicion;
        float velocidad;
        float recorrido;
        int fila;
        int columna;
        bool caminando;
        bool empujando;
        bool aturdido;

    public:
        Personaje(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        virtual ~Personaje()                    {};
        virtual void Update(float ,Mapa* )      {};
        void Draw(sf::RenderWindow & ventana)   {ventana.draw(*sprite);};
        sf::Vector2i getPosicion()              {return posicion;};
        sf::Sprite* getSprite()                 {return sprite;};
        bool getAturdido()                      {return aturdido;};
};
