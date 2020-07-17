#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"


class Pengo : public Personaje {
    private:
        int vidas;
        Animacion *animacionMuerte;
        sf::Clock reloj;
        bool quieto;
        bool empujar;
        bool dios;
        float tiempoAturdido;

    public:
        Pengo(sf::Texture*, float, float, sf::Vector2u, sf::Vector2i);
        ~Pengo();
        void Update(float ,Mapa* );
        void modoDios();
        void reiniciarVidas()   {vidas = 3;};
        void reiniciarPosicion();
        void reiniciarPInicial();
        bool perderVida();
        bool getMuerte();
        bool getDios()          {return dios;};  
        int getVidas()          {return vidas;};
};
