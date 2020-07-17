#include "BRoto.h"

BRoto::BRoto(sf::Texture* texture, int x, int y) : Bloque(texture, x, y) {
    roto = false;
    rompiendo = false;
    recorrido = 0.0f;
}

BRoto::~BRoto() {
    delete sprite;
    sprite = NULL;
    delete posicion;
    posicion = NULL;
}

void BRoto::Update(float deltaTime) {
    float espacio = 0.0f;
    if(!roto &&  !rompiendo){
        if(direccion > -1){
            espacio = velocidad*deltaTime;
            if(espacio+recorrido >= 16.0f){
                espacio = 16.0f - recorrido;
                recorrido = 0.0f;
                movimiento = true;

                if(direccion == 0) { //Arriba
                    posicion->x--;
                }else if(direccion == 1){ //Derecha
                    posicion->y++;
                }else if (direccion == 2){ //Abajo
                    posicion->x++;
                }else if (direccion == 3){ //Izquierda
                    posicion->y--;
                }

            }else{
                recorrido += espacio;
                movimiento = false;
            }
            if(direccion == 0){ //Arriba
                sprite->move(0, -espacio);
            }else if(direccion == 1){ //Derecha
                sprite->move(espacio, 0);
            }else if(direccion == 2){ //Abajo
                sprite->move(0, espacio);
            }else if(direccion == 3){ //Izquierda
                sprite->move(-espacio, 0);
            }
        }
    //Rompemos el bloque
    }else if(rompiendo){
        if(reloj.getElapsedTime().asSeconds() > 0.05f) {
            sf::IntRect rotura = sprite->getTextureRect();
            rotura.left+= 16;
            if(rotura.left <= 160){
                sprite->setTextureRect(rotura);
            }else{
                rompiendo = false;
                roto = false;
            }
            reloj.restart();
        }
    }
}