#include "Juego.h"
//alias do="cd build/ && make && mv Pengo .. && cd .. && ./Pengo"
Juego* Juego::instancia = NULL;

Juego* Juego::getInstancia() {
    if (instancia == NULL) {
        instancia = new Juego();
    }
    return instancia;
}

Juego::Juego() {
    ventana = new sf::RenderWindow(sf::VideoMode(19*16, 22*16), "Pengo");
    ventana->setFramerateLimit(60);
    if (!sprites.loadFromFile("resources/Character.png")) {
        std::cout << "Failed loading sprite sheet..." << std::endl;
        exit(0);
    }
    if (!tileset.loadFromFile("resources/Tileset.png")) {
        std::cout << "Failed loading tileset..." << std::endl;
        exit(0);
    }
    pengo = new Pengo(&sprites, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    mapasAleatorios();
    mapa = mapa1;
    anyadirEnemigos(nivel1);
    totalEnemigos = 6;
    fin = false;
    nivel = 1;
    totalNiveles = 10;
    Draw();
    bucleJuego();
}

void Juego::bucleJuego() {
    while(ventana->isOpen()) {
        deltaTime = reloj.restart().asSeconds();
        bucleEventos();
        if(pengo->getMuerte()) {
            nivel = 1;
            reiniciar();
            pengo->reiniciarVidas();
        }else if(pengo->getAturdido() && !pengo->getDios()) {
            pengo->Update(deltaTime, mapa);
            if(relojNivel.getElapsedTime().asSeconds() >= 2.45f){
                reiniciar();
            }
        }else if(!fin) {
            if(nivelCompleto()) {
                if(nivel == 1) {
                    nivel = 2;
                    reiniciar();
                }else{
                    fin = true;
                }
            }else{
                pengo->Update(deltaTime, mapa);
                comprobarColisiones();
                if(pengo->getAturdido() && pengo->getDios() && relojNivel.getElapsedTime().asSeconds() >= 1.15f)
                    pengo->reiniciarPosicion();
            }
        }else{
            ventana->close();
        }
        Draw();
    }
    delete instancia;
    instancia = NULL;
}

void Juego::bucleEventos() {
    while(ventana->pollEvent(evento)) {
        switch(evento.type) {
            case sf::Event::Closed:
                ventana->close();
                break;
            case sf::Event::KeyPressed:
                switch (evento.key.code) {
                    case sf::Keyboard::Escape:
                        ventana->close();
                        break;
                    case sf::Keyboard::G:
                        pengo->modoDios();
                        break;

                    case sf::Keyboard::X:
                        pengo->reiniciarVidas();
                        reiniciar();
                        std::cout << "Has reiniciado el nivel " << nivel << std::endl;
                        break;

                    case sf::Keyboard::N:
                        if (nivel < totalNiveles) {
                            nivel++;
                            reiniciar();
                        }
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}

void Juego::comprobarColisiones() {
    Bloque* bloquesito;
    mapa->Update(deltaTime);
    for(int x = 0; x < enemigos.size(); x++) {
        if(enemigos[x] && !enemigos[x]->getMuerte()) {
            enemigos[x]->Update(deltaTime, mapa);
            if(pengo->getSprite()->getGlobalBounds().intersects(enemigos[x]->getSprite()->getGlobalBounds())){
                pengo->perderVida();
                relojNivel.restart();
            }
            for(int y = 0; y < 15; y++) {
                for(int z = 0; z < 13; z++) {
                    bloquesito = mapa->getBloque(y, z);
                    if(bloquesito && bloquesito->getDireccion() > -1  && enemigos[x]->getLibre()){
                           if(enemigos[x]->getSprite()->getGlobalBounds().intersects(bloquesito->getSprite()->getGlobalBounds())){
                                enemigos[x]->getEmpujado(bloquesito);
                                suplirEnemigo();
                           }
                    }
                    bloquesito = NULL;
                }
            }
        }
    }

}

void Juego::Draw() {
    ventana->clear();
    mapa->Draw(*ventana);
    pengo->Draw(*ventana);
    for(int x = 0; x < enemigos.size(); x++){
        if (enemigos[x]  &&  !enemigos[x]->getMuerte())
            enemigos[x]->Draw(*ventana);
    }
    ventana->display();
}

void Juego::anyadirEnemigos(int nivel[15][13]) {
   for(int x = 0; x < enemigos.size(); x++){
        delete enemigos[x];
    }
    enemigos.clear();
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 13; y++) {
            if (nivel[x][y] == 2) {
                enemigos.push_back(new SnoBee(&sprites, 45.0f, 0.2f, sf::Vector2u(0, 2), sf::Vector2i(x, y)));
            }
        }
    }
}

void Juego::suplirEnemigo() {
    if(enemigos.size() < totalEnemigos) {
        sf::Vector2i _newPosition = mapa->getLibre();
        enemigos.push_back(new SnoBee(&sprites, 45.0f, 0.2f, sf::Vector2u(0, 2), _newPosition));
    }
}

bool Juego::nivelCompleto() {
    int snobees = 0;
    bool completado = false;
    if(enemigos.size() == totalEnemigos){
        for(int x = 0; x < enemigos.size(); x++){
            if(enemigos[x]  &&  enemigos[x]->getMuerte()){
                snobees++;
            }
        }
    }

    if(snobees == totalEnemigos) {
        completado = true;
    }
    return completado;
}

void Juego::reiniciar() {
    if(nivel == 1) {
        anyadirEnemigos(nivel1);
        mapa1 = new Mapa(&tileset, nivel1);
        mapa = mapa1;
    }
    if(nivel == 2) {
        anyadirEnemigos(nivel2);
        mapa2 = new Mapa(&tileset, nivel2);
        mapa = mapa2;
    }
    if(nivel == 3) {
        anyadirEnemigos(nivel3);
        mapa3 = new Mapa(&tileset, nivel3);
        mapa = mapa3;
    }
    if(nivel == 4) {
        anyadirEnemigos(nivel4);
        mapa4 = new Mapa(&tileset, nivel4);
        mapa = mapa4;
    }
    if(nivel == 5) {
        anyadirEnemigos(nivel5);
        mapa5 = new Mapa(&tileset, nivel5);
        mapa = mapa5;
    }
    if(nivel == 6) {
        anyadirEnemigos(nivel6);
        mapa6 = new Mapa(&tileset, nivel6);
        mapa = mapa6;
    }
    if(nivel == 7) {
        anyadirEnemigos(nivel7);
        mapa7 = new Mapa(&tileset, nivel7);
        mapa = mapa7;
    }
    if(nivel == 8) {
        anyadirEnemigos(nivel8);
        mapa8 = new Mapa(&tileset, nivel8);
        mapa = mapa8;
    }
    if(nivel == 9) {
        anyadirEnemigos(nivel9);
        mapa9 = new Mapa(&tileset, nivel9);
        mapa = mapa9;
    }
    if(nivel == 10) {
        anyadirEnemigos(nivel10);
        mapa10 = new Mapa(&tileset, nivel10);
        mapa = mapa10;
    }
    pengo->reiniciarPInicial();
}

void Juego::mapasAleatorios(){
    int num = rand()%2;
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel1[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel1[x][y] = 2;
            }else{
                //Bloques
                nivel1[x][y] = num;
            }
            
            num = rand()%2;
        }
    }
    mapa1 = new Mapa(&tileset, nivel1);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel2[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel2[x][y] = 2;
            }else{
                //Bloques
                nivel2[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa2 = new Mapa(&tileset, nivel2);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel3[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel3[x][y] = 2;
            }else{
                //Bloques
                nivel3[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa3 = new Mapa(&tileset, nivel3);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel4[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel4[x][y] = 2;
            }else{
                //Bloques
                nivel4[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa4 = new Mapa(&tileset, nivel4);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel5[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel5[x][y] = 2;
            }else{
                //Bloques
                nivel5[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa5 = new Mapa(&tileset, nivel5);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel6[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel6[x][y] = 2;
            }else{
                //Bloques
                nivel6[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa6 = new Mapa(&tileset, nivel6);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel7[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel7[x][y] = 2;
            }else{
                //Bloques
                nivel7[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa7 = new Mapa(&tileset, nivel7);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel8[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel8[x][y] = 2;
            }else{
                //Bloques
                nivel8[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa8 = new Mapa(&tileset, nivel8);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel9[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel9[x][y] = 2;
            }else{
                //Bloques
                nivel9[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa9 = new Mapa(&tileset, nivel9);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Huecos
                nivel10[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemigos
                nivel10[x][y] = 2;
            }else{
                //Bloques
                nivel10[x][y] = num;
            }
            num = rand()%2;
        }
    }
    mapa10 = new Mapa(&tileset, nivel10);
}

Juego::~Juego(){
    delete pengo;
    for(int x = 0; x < enemigos.size(); x++){
        delete enemigos[x];
    }
    enemigos.clear();
    delete mapa1;
    delete mapa2;
    delete mapa3;
    delete mapa4;
    delete mapa5;
    delete mapa6;
    delete mapa7;
    delete mapa8;
    delete mapa9;
    delete mapa10;
    delete ventana;
    delete instancia;
    pengo = NULL;
    mapa = NULL;
    mapa1 = NULL;
    mapa2 = NULL;
    mapa3 = NULL;
    mapa4 = NULL;
    mapa5 = NULL;
    mapa6 = NULL;
    mapa7 = NULL;
    mapa8 = NULL;
    mapa9 = NULL;
    mapa10 = NULL;
    ventana = NULL;
    instancia = NULL;
}