#include "Pengo.h"

Pengo::Pengo(sf::Texture *texture, float vel, float tiempo, sf::Vector2u cuadra, sf::Vector2i pos) : Personaje(texture, vel, tiempo, cuadra, pos){
    vidas = 3;
    animacionMuerte = new Animacion(texture, cuadra, 0.2f);
    quieto = false;
    empujar = false;
    dios = false;
    tiempoAturdido = 2.5f;
}

Pengo::~Pengo() {
    delete animacionMuerte;
    animacionMuerte = NULL;
    delete animacion;
    animacion = NULL;
    delete sprite;
    sprite = NULL;
}

void Pengo::Update(float deltaTime, Mapa* mapa) {
    sf::Vector2i posAnterior = posicion;
    float desplazamiento = 0.0f;

    if (vidas > 0 && (!caminando && !empujando && !aturdido)){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            empujando = true;
            empujar = true;
            animacion->setTiempoCambio(0.13f);
            fila = 1;
            reloj.restart();
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            caminando = true;
            columna = 4;
            posicion.x--;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            caminando = true;
            columna = 0;
            posicion.x++;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            caminando = true;
            columna = 2;
            posicion.y--;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            caminando = true;
            columna = 6;
            posicion.y++;
        } 
        
        if(mapa->comprobar(posicion)){
            quieto = false;
        }else{
            quieto = true;
            posicion  = posAnterior;
        }
    }

    if(aturdido){
        if(reloj.getElapsedTime().asSeconds() >= tiempoAturdido) {
            aturdido = false;
            animacion->Update(0, 0, deltaTime);
            sprite->setTextureRect(animacion->getUvRect());
            if(!dios){
                vidas--;
            }
            sprite->setTextureRect(animacion->getUvRect());
        }else{
            animacionMuerte->Update(2, 0, deltaTime);
            sprite->setTextureRect(animacionMuerte->getUvRect());
        }

    }else if(empujando){
        if(reloj.getElapsedTime().asSeconds() >= 0.4f) {
            empujando = false;
            fila = 0;
            animacion->setTiempoCambio(0.2f);
        }
        if(empujar) {
            if (columna == 4){
                mapa->empujar(sf::Vector2i(posicion.x-1, posicion.y), 0, true);
            }else if (columna == 6){
                mapa->empujar(sf::Vector2i(posicion.x, posicion.y+1), 1, true);
            }else if (columna == 0){
                mapa->empujar(sf::Vector2i(posicion.x+1, posicion.y), 2, true);
            }else if (columna == 2){
                mapa->empujar(sf::Vector2i(posicion.x, posicion.y-1), 3, true);
            }
            empujar = false;
        }
        animacion->Update(fila, columna, deltaTime);
        sprite->setTextureRect(animacion->getUvRect());
        
    }else if(caminando){
        if(recorrido+velocidad*deltaTime >= 16.0f) {
            desplazamiento = 16.0f - recorrido;
            caminando = false;
            recorrido = 0.0f;
        }else{
            recorrido += velocidad*deltaTime;
            desplazamiento = velocidad*deltaTime;
        }
        if(!quieto) {
            if(columna == 4){
                sprite->move(0, -desplazamiento);
            }else if(columna == 6){
                sprite->move(desplazamiento, 0);
            }else if(columna == 0){
                sprite->move(0, desplazamiento);
            }else if(columna == 2){
                sprite->move(-desplazamiento, 0);
            }
        }
        animacion->Update(fila, columna, deltaTime);
        sprite->setTextureRect(animacion->getUvRect());
    }
}

void Pengo::modoDios() {
    if(dios){
        dios = false;
        tiempoAturdido = 2.5f;
        std::cout << "Modo Dios desactivado" << std::endl;
    }else{
        dios = true;
        tiempoAturdido = 1.2f;
        std::cout << "Modo Dios activado" << std::endl;
    }
}

void Pengo::reiniciarPosicion() {
    sprite->setPosition(16+posicion.y*16, 40+posicion.x*16);
    recorrido = 0.0f;
}

void Pengo::reiniciarPInicial() {
    posicion.x = 6;
    posicion.y = 6;
    recorrido = 0.0f;
    sprite->setPosition(24+6*16, 48+6*16);
}

bool Pengo::perderVida() {
    bool perder = false;
    if (vidas > 0) {
        reloj.restart();
        aturdido = true;
        caminando = false;
        empujando = false;
        fila = 0;
        perder = true;
    }
    return perder;
}

bool Pengo::getMuerte() {
    bool muerto = true;
    if(vidas > 0) {
        muerto = false;
    }
    return muerto;
}



