#include "Mapa.h"

Mapa::Mapa(sf::Texture* tileset, int level[15][13]) {
    bordeI   = new sf::Sprite(*tileset);
    bordeD  = new sf::Sprite(*tileset);
    bordeA    = new sf::Sprite(*tileset);
    bordeAb = new sf::Sprite(*tileset);
    bordeI->setTextureRect(sf::IntRect(8, 16, 8, 256));
    bordeD->setTextureRect(sf::IntRect(8, 16, 8, 256));
    bordeA->setTextureRect(sf::IntRect(0, 8, 224, 8));
    bordeAb->setTextureRect(sf::IntRect(0, 8, 224, 8));
    bordeI->setPosition(0, 24);
    bordeI->setOrigin(4, 0);
    bordeI->setScale(-1, 1);
    bordeI->setOrigin(8, 0);
    bordeD->setPosition(216, 24);
    bordeA->setPosition(0, 24);
    bordeA->setOrigin(0, 4);
    bordeA->setScale(1, -1);
    bordeA->setOrigin(0, 8);
    bordeAb->setPosition(0, 272);
    golpeado = false; //Creo que se puede quitar

    bloques = new Bloque**[15];
    for (int x = 0; x < 15; x++) {
        bloques[x] = new Bloque*[13];
    }
    
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 13; y++) {
            if (level[x][y] == 1) {
                bloques[x][y] = new BRoto(tileset, y, x);
            } else {
                bloques[x][y] = NULL;
            }
        }
    }

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if (bloques[x][y]){
                bloques[x][y]->setPosicion(sf::Vector2i(x, y));
            }
        }
    }
}

Mapa::~Mapa() {
    delete bordeI;
    bordeI = NULL;
    delete bordeD;
    bordeD = NULL;
    delete bordeA;
    bordeA = NULL;
    delete bordeAb;
    bordeAb = NULL;
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if (bloques[x][y]){
                delete bloques[x][y];
            }
        }
        delete[] bloques[x];
    }
    delete[] bloques;
    bloques = NULL;

    for(int x = 0; x < restos.size(); x++){
        if(restos[x] != NULL){
            delete restos[x];
            restos[x] = NULL;
        }
    }
    restos.clear();
}


void Mapa::Update(float deltaTime) {
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if(bloques[x][y] != NULL && bloques[x][y]->getMovimiento()) {
                if(x != bloques[x][y]->getPosicion().x || y != bloques[x][y]->getPosicion().y) {
                    bloques[bloques[x][y]->getPosicion().x][bloques[x][y]->getPosicion().y] = bloques[x][y];
                    bloques[x][y] = NULL;
                }
                
            }
        }
    }
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if (bloques[x][y] != NULL) {
                if (bloques[x][y]->getMovimiento()) {
                    empujar(bloques[x][y]->getPosicion(), bloques[x][y]->getDireccion(), false);
                    bloques[x][y]->parar();
                }
                bloques[x][y]->Update(deltaTime);
            }
        }
    }
    BRoto *roto = NULL;
    for(int x = 0; x < restos.size(); x++){
        if(restos[x] != NULL){
            roto = (BRoto *) &restos[x];
            if(roto != NULL){
                if(roto->getRoto()){
                    restos[x] = NULL;
                }else{
                    restos[x]->Update(deltaTime);
                }
            }
        }
    }
}

bool Mapa::comprobar(sf::Vector2i pos) {
    bool libre = false;

    if (pos.x >= 0 && pos.x < 15 && pos.y >= 0 && pos.y < 13){
        if (bloques[pos.x][pos.y] == NULL) {
            libre = true;
        }
    }

    return libre;
}

void Mapa::empujar(sf::Vector2i pos, int dir, bool romper) {
    if(!comprobar(pos) && pos.x >= 0 && pos.x < 15 && pos.y >= 0 && pos.y < 13) {
       sf::Vector2i siguiente = pos;
        if(dir == 0){
            siguiente.x--;
        }else if(dir == 1){
            siguiente.y++;
        }else if(dir == 2){
            siguiente.x++;
        }else if(dir == 3){
            siguiente.y--;
        }

        if(comprobar(siguiente)){
            bloques[pos.x][pos.y]->setDireccion(dir);
        } else if (BRoto* roto = dynamic_cast<BRoto*>(bloques[pos.x][pos.y])) {
            if (romper) {
                roto->romper();
                restos.push_back(bloques[pos.x][pos.y]);
                bloques[pos.x][pos.y] = NULL;
            } else {
                bloques[pos.x][pos.y]->setDireccion(-1);
            }
        }
    }
}

sf::Vector2i Mapa::getLibre() {
    sf::Vector2i libre(0, 0);

    while(!comprobar(libre)){
        libre.x = rand()%15;
        libre.y = rand()%13;
    }
    return libre;
}

void Mapa::Draw(sf::RenderWindow &ventana) {
   ventana.draw(*bordeI);
    ventana.draw(*bordeD);
    ventana.draw(*bordeA);
    ventana.draw(*bordeAb);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if (bloques[x][y]){
                bloques[x][y]->Draw(ventana);
            }
        }
    }
    
    BRoto *roto = NULL;
    for(int x = 0; x < restos.size(); x++){
        if(restos[x] != NULL){
           roto = (BRoto *) &restos[x];
           if(roto != NULL){
                if(!roto->getRoto()){
                    restos[x]->Draw(ventana);
                }
           }
        }
    }
}
