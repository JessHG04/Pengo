#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bloque.h"
#include "Personaje.h"
#include "BRoto.h"
#include "Pengo.h"
#include "Mapa.h"
#include "SnoBee.h"


class Juego {

    public:
        static Juego* getInstancia();
    private:
        static Juego* instancia;
        sf::RenderWindow* ventana;
        sf::Font fuente;
        sf::Text dios;
        sf::Text vidas;
        sf::Text enem;
        sf::Text lvl;
        sf::Text nombre;
        Mapa* mapa;
        Mapa* mapa1;
        Mapa* mapa2;
        Mapa* mapa3;
        Mapa* mapa4;
        Mapa* mapa5;
        Mapa* mapa6;
        Mapa* mapa7;
        Mapa* mapa8;
        Mapa* mapa9;
        Mapa* mapa10;
        int nivel1[15][13];
        int nivel2[15][13];
        int nivel3[15][13];
        int nivel4[15][13];
        int nivel5[15][13];
        int nivel6[15][13];
        int nivel7[15][13];
        int nivel8[15][13];
        int nivel9[15][13];
        int nivel10[15][13];
        int totalEnemigos;
        int nivel;
        int totalNiveles;
        bool fin;
        float deltaTime;
        Pengo* pengo;
        sf::Clock reloj;
        sf::Clock relojNivel;
        sf::Event evento;
        sf::Texture sprites;
        sf::Texture tileset;
        std::vector<SnoBee*> enemigos;
    protected:
        Juego();
        ~Juego();
        void bucleJuego();
        void bucleEventos();
        void anyadirEnemigos(int[15][13]);
        void suplirEnemigo();
        void mapasAleatorios();
        void comprobarColisiones();
        void reiniciar();
        bool nivelCompleto();
        void Draw();

   
};