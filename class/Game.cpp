#include "Game.h"
//alias do="cd build/ && make && mv Pengo .. && cd .. && ./Pengo"
Game* Game::gameInstance = NULL;

Game* Game::getInstance() {
    if (gameInstance == NULL) {
        gameInstance = new Game();
    }
    return gameInstance;
}

Game::Game() {
    window = new sf::RenderWindow(sf::VideoMode(19*16, 22*16), "Pengo");
    window->setFramerateLimit(60);
    if (!spriteSheet.loadFromFile("resources/Character.png")) {
        std::cout << "Failed loading sprite sheet..." << std::endl;
        exit(0);
    }
    if (!tileset.loadFromFile("resources/tileset.png")) {
        std::cout << "Failed loading tileset..." << std::endl;
        exit(0);
    }
    pengo = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    RandomMaps();
    map = map1;
    addEnemies(level1);
    snoBeesPerLevel = 6;
    endGame = false;
    level = 1;
    maxLevels = 10;
    Draw();
    GameLoop();
}

void Game::GameLoop() {
    while (window->isOpen()) {
        deltaTime = clock.restart().asSeconds();
        EventsLoop();
        if(pengo->getDead()) {
            level = 1;
            restoreLevel();
            pengo->restoreLifes();
        }else if(pengo->getStunned() && !pengo->getGodMode()) {
            pengo->Update(deltaTime, map);
            if(levelClock.getElapsedTime().asSeconds() >= 2.45f){
                restoreLevel();
            }
        } else if (!endGame) {
            if (levelCompleted()) {
                if (level == 1) {
                    level = 2;
                    restoreLevel();
                }else{
                    endGame = true;
                }
            }else{
                pengo->Update(deltaTime, map);
                GameFunctionality();
                if (pengo->getStunned()  &&  pengo->getGodMode()  &&  levelClock.getElapsedTime().asSeconds() >= 1.15f)
                    pengo->restartPosition();
            }
        } else {
            window->close();
        }
        Draw();
    }
    delete gameInstance;
    gameInstance = NULL;
}

void Game::EventsLoop() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                    case sf::Keyboard::G:
                        pengo->changeGodMode();
                        break;

                    case sf::Keyboard::X:
                        pengo->restoreLifes();
                        this->restoreLevel();
                        break;

                    case sf::Keyboard::N:
                        if (level < maxLevels) {
                            level++;
                            this->restoreLevel();
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




void Game::GameFunctionality() {
    Bloque* _block;
    map->Update(deltaTime);
    for(int x = 0; x < enemies.size(); x++) {
        if(enemies[x]  &&  !enemies[x]->getDead()) {
            enemies[x]->Update(deltaTime, map);
            if(pengo->getSprite()->getGlobalBounds().intersects(enemies[x]->getSprite()->getGlobalBounds())){
                pengo->loseLife();
                levelClock.restart();
            }
            for(int y = 0; y < 15; y++) {
                for(int z = 0; z < 13; z++) {
                    _block = map->getBlock(y, z);
                    if(_block  &&  _block->getDireccion() > -1  &&  enemies[x]->getFree()){
                           if(enemies[x]->getSprite()->getGlobalBounds().intersects(_block->getSprite()->getGlobalBounds())){
                                enemies[x]->getSmashed(_block);
                                this->addSnoBee();
                           }
                    }
                    _block = NULL;
                }
            }
        }
    }

}

void Game::Draw() {
    window->clear();
    map->Draw(*window);
    pengo->Draw(*window);
    for(int x = 0; x < enemies.size(); x++){
        if (enemies[x]  &&  !enemies[x]->getDead())
            enemies[x]->Draw(*window);
    }
    window->display();
}

void Game::addEnemies(int level[15][13]) {
   for(int x = 0; x < enemies.size(); x++){
        delete enemies[x];
    }
    enemies.clear();
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 13; y++) {
            if (level[x][y] == 2) {
                enemies.push_back(new SnoBee(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0, 2), sf::Vector2i(x, y)));
            }
        }
    }
}

void Game::addSnoBee() {

    if(enemies.size() < snoBeesPerLevel) {
        sf::Vector2i _newPosition = map->getFreePosition();

        enemies.push_back(new SnoBee(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0, 2), _newPosition));
    }
}

bool Game::levelCompleted() {
    int _counter = 0;
    if(enemies.size() == snoBeesPerLevel){
        for(int x = 0; x < enemies.size(); x++){
            if(enemies[x]  &&  enemies[x]->getDead()){
                _counter++;
            }
        }
    }

    if(_counter == snoBeesPerLevel) {
        return true;
    } else {
        return false;
    }
}

void Game::restoreLevel() {
    if(level == 1) {
        this->addEnemies(level1);
        map1 = new Map(&tileset, level1);
        map = map1;
    }
    if(level == 2) {
        this->addEnemies(level2);
        map2 = new Map(&tileset, level2);
        map = map2;
    }
    if(level == 3) {
        this->addEnemies(level3);
        map3 = new Map(&tileset, level3);
        map = map3;
    }
    if(level == 4) {
        this->addEnemies(level4);
        map4 = new Map(&tileset, level4);
        map = map4;
    }
    if(level == 5) {
        this->addEnemies(level5);
        map5 = new Map(&tileset, level5);
        map = map5;
    }
    if(level == 6) {
        this->addEnemies(level6);
        map6 = new Map(&tileset, level6);
        map = map6;
    }
    if(level == 7) {
        this->addEnemies(level7);
        map7 = new Map(&tileset, level7);
        map = map7;
    }
    if(level == 8) {
        this->addEnemies(level8);
        map8 = new Map(&tileset, level8);
        map = map8;
    }
    if(level == 9) {
        this->addEnemies(level9);
        map9 = new Map(&tileset, level9);
        map = map9;
    }
    if(level == 10) {
        this->addEnemies(level10);
        map10 = new Map(&tileset, level10);
        map = map10;
    }
    pengo->restartInitialPosition();
}

void Game::RandomMaps(){
    int num = rand()%2;
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level1[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level1[x][y] = 2;
            }else{
                //Blocks
                level1[x][y] = num;
            }
            
            num = rand()%2;
        }
    }
    map1 = new Map(&tileset, level1);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level2[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level2[x][y] = 2;
            }else{
                //Blocks
                level2[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map2 = new Map(&tileset, level2);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level3[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level3[x][y] = 2;
            }else{
                //Blocks
                level3[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map3 = new Map(&tileset, level3);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level4[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level4[x][y] = 2;
            }else{
                //Blocks
                level4[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map4 = new Map(&tileset, level4);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level5[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level5[x][y] = 2;
            }else{
                //Blocks
                level5[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map5 = new Map(&tileset, level5);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level6[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level6[x][y] = 2;
            }else{
                //Blocks
                level6[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map6 = new Map(&tileset, level6);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level7[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level7[x][y] = 2;
            }else{
                //Blocks
                level7[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map7 = new Map(&tileset, level7);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level8[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level8[x][y] = 2;
            }else{
                //Blocks
                level8[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map8 = new Map(&tileset, level8);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level9[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level9[x][y] = 2;
            }else{
                //Blocks
                level9[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map9 = new Map(&tileset, level9);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level10[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) /*|| (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)*/){
                //Enemies
                level10[x][y] = 2;
            }else{
                //Blocks
                level10[x][y] = num;
            }
            num = rand()%2;
        }
    }
    map10 = new Map(&tileset, level10);
}

Game::~Game(){
    delete pengo;
    for(int x = 0; x < enemies.size(); x++){
        delete enemies[x];
    }
    enemies.clear();
    delete map1;
    delete map2;
    delete window;
    delete gameInstance;
    pengo = NULL;
    map = NULL;
    map1 = NULL;
    map2 = NULL;
    map3 = NULL;
    map4 = NULL;
    map5 = NULL;
    map6 = NULL;
    map7 = NULL;
    map8 = NULL;
    map9 = NULL;
    map10 = NULL;
    window = NULL;
    gameInstance = NULL;
}