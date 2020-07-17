#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animacion {

    private:
        sf::IntRect uvRect;
        float tiempoCambio;
        float tiempoTotal;
        sf::Vector2u imgActual;
        sf::Vector2u cuadrante;
        sf::Vector2u rango;

    public:
        Animacion(sf::Texture* ,sf::Vector2u ,float);
        void Update(int, int, float );
        ~Animacion()                    { };
        sf::IntRect getUvRect()         {return uvRect;};
        void setTiempoCambio(float tiempo)   {tiempoCambio = tiempo;};
        void setCuadrante(sf::Vector2u cua)  {cuadrante = cua;};
};
