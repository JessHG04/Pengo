#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bloque {

    protected:
        sf::Sprite *sprite;
        sf::Vector2i* posicion;
        float velocidad;
        int direccion;
        float recorrido;
        bool movimiento;

    public:
        Bloque(sf::Texture* , int , int, bool);
        virtual ~Bloque()                       {};
        virtual void Update(float deltaTime)    {};
        void Draw(sf::RenderWindow &ventana)    {ventana.draw(*sprite);};
        void setDireccion(int dir)              {direccion = dir;};
        void setPosicion(sf::Vector2i );
        void parar()                            {movimiento = false;};
        sf::Sprite* getSprite()                 {return sprite;};
        sf::Vector2i getPosicion()              {return *posicion;};
        int getDireccion()                      {return direccion;};
        bool getMovimiento()                    {return movimiento;};
};
