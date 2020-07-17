#include "Personaje.h"

Personaje::Personaje(sf::Texture *texture, float vel, float tiempo, sf::Vector2u cuadra, sf::Vector2i pos){
    sprite = new sf::Sprite(*texture);
    animacion = new Animacion(texture, cuadra, tiempo);
    sprite->setTextureRect(animacion->getUvRect());
    sprite->setOrigin(8,8);
    sprite->setPosition(24+pos.y*16, 48+pos.x*16);
    posicion = pos;
    velocidad = vel;
    recorrido = 0.0f;
    caminando = false;
    empujando = false;
    aturdido = false;
    columna = 0;
    if(cuadra.y > 1){
        fila = 1;
    }else{
        fila = 0;
    }
}