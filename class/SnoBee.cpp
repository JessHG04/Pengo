#include "SnoBee.h"

SnoBee::SnoBee(sf::Texture* texture, float vel, float tiempo, sf::Vector2u cuadra, sf::Vector2i pos) : Personaje(texture, vel, tiempo, cuadra, pos){
    direccion = 2;
    quieto = false;
    muerto = false;
    bloque = NULL;
}

SnoBee::~SnoBee() {
    delete animacion;
    animacion = NULL;
    delete sprite;
    sprite = NULL;
    bloque = NULL;
}

void SnoBee::Update(float deltaTime, Mapa* mapa) {
    std::vector<sf::Vector2i> movimiento;
    std::vector<int> orientacion;
    int aux = -1;
    int random;
    int randomRomper;
    
    if(!caminando && !quieto && bloque == NULL) {
        if(mapa->comprobar(sf::Vector2i(posicion.x-1, posicion.y))){
            movimiento.push_back(sf::Vector2i(posicion.x-1, posicion.y));
            orientacion.push_back(0);
        }
        if(mapa->comprobar(sf::Vector2i(posicion.x, posicion.y+1))){
            movimiento.push_back(sf::Vector2i(posicion.x, posicion.y+1));
            orientacion.push_back(1);
        }
        if(mapa->comprobar(sf::Vector2i(posicion.x+1, posicion.y))){
            movimiento.push_back(sf::Vector2i(posicion.x+1, posicion.y));
            orientacion.push_back(2);
        }
        if(mapa->comprobar(sf::Vector2i(posicion.x, posicion.y-1))){
            movimiento.push_back(sf::Vector2i(posicion.x, posicion.y-1));
            orientacion.push_back(3);
        }

        if(movimiento.size() > 0) {
            for(int x = 0; x<orientacion.size(); x++){
                if (direccion == orientacion[x]){
                    aux = x;
                    posicion = movimiento[x];
                }
            }
            if(aux != -1){ //Se va a mover en esa direccion
                quieto = false;
                caminando = true;
            }else{//Buscamos otro sitio al que moverse
                randomRomper = rand()%2; //Aleatoriamente elige o empujar el bloque(0) o buscar otra direccion (1)
                if(randomRomper == 0){
                    empujando = true;
                    empujar = true;
                    fila = 2;
                    animacion->setTiempoCambio(0.13f);
                    reloj.restart();
                }else{
                    random = rand()%movimiento.size();
                    aux = random;
                    direccion = orientacion[aux];
                    if(direccion == 0){
                        columna = 4;
                    }else if(direccion == 1){
                        columna = 6;
                    }else if(direccion == 2){
                        columna = 0;
                    }else if(direccion == 3){
                        columna = 2;
                    }
                    quieto  = true;
                    caminando = false;
                }
                
            }
            orientacion.clear();
            movimiento.clear();
        }
    }
    if(empujando){
        if(reloj.getElapsedTime().asSeconds() >= 0.4f){
            empujando = false;
            fila = 1;
            animacion->setTiempoCambio(0.2f);
        }
        if(empujar){
            if(direccion == 0){
                mapa->empujar(sf::Vector2i(posicion.x-1, posicion.y), 0, true);
                columna = 4;
            }else if (direccion == 1){
                mapa->empujar(sf::Vector2i(posicion.x, posicion.y+1), 1, true);
                columna = 6;
            }else if (direccion == 2){
                mapa->empujar(sf::Vector2i(posicion.x+1, posicion.y), 2, true);
                columna = 0;
            }else if (direccion == 3){
                mapa->empujar(sf::Vector2i(posicion.x, posicion.y-1), 3, true);
                columna = 2;
            }
            empujar = false;
        }
        animacion->Update(fila, columna, deltaTime);
        sprite->setTextureRect(animacion->getUvRect());
    }
    if(quieto || caminando) {
        float desplazamiento = velocidad*deltaTime;
        if(recorrido+desplazamiento >= 16.0f) {
            desplazamiento = 16.0f - recorrido;
            caminando = false;
            quieto = false;
            recorrido = 0.0f;
            sprite->setPosition(48+posicion.y*16, 64+posicion.x*16);
        }else{
            recorrido += desplazamiento;
        }

        if (caminando && !quieto) {
            if (columna == 4){
                sprite->move(0, -desplazamiento);
            }else if (columna == 6){
                sprite->move(desplazamiento, 0);
            }else if (columna == 0){
                sprite->move(0, desplazamiento);
            }else if (columna == 2){
                sprite->move(-desplazamiento, 0);
            }
        }
        animacion->Update(fila, columna, deltaTime);
        sprite->setTextureRect(animacion->getUvRect());

    }else if(bloque){ //Si existe es porque esta siendo empujado por el mismo
        sf::Vector2f desplazamiento(0.0f, 0.0f);
        sf::Vector2f posicion;
        if(bloque->getDireccion() > -1) {
            if(bloque->getDireccion() == 0){
                columna = 0;
                desplazamiento.y = -10;
            }else if(bloque->getDireccion() == 1){
                columna = 2;
                desplazamiento.x = 10;
            }else if(bloque->getDireccion() == 2){
                columna = 4;
                desplazamiento.y = 10;
            }else if(bloque->getDireccion() == 3){
                columna = 6;
                desplazamiento.x = -10;
            }
            if(fila != 4) {
                fila = 4;
                animacion->Update(fila, columna, deltaTime);
                sprite->setTextureRect(animacion->getUvRect());
            }
            posicion = bloque->getSprite()->getPosition();
            sprite->setPosition(posicion + desplazamiento);
        } else {
            muerto = true;
        }
    }
}

void SnoBee::getEmpujado(Bloque* bloq) {
    bloque = bloq;
    quieto  = false;
    caminando = false;
}

bool SnoBee::getLibre() {
    bool libre = false;
    if(bloque == NULL){
        libre = true;
    }
    return libre;
}
