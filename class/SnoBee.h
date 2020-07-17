#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "Pengo.h"

class SnoBee : public Personaje {
    private:
        int direccion;
        bool quieto;
        bool muerto;
        Bloque* bloque;

    public:
        SnoBee(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        ~SnoBee();
        void Update(float ,Mapa* );
        void getEmpujado(Bloque* );
        bool getMuerte()            {return muerto;};
        bool getLibre();
};