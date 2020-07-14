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
    // Loading textures...
    if (!spriteSheet.loadFromFile("resources/SpriteSheet.png")) {
        std::cout << "Failed loading sprite sheet..." << std::endl;
        exit(0);
    }
    if (!tileset.loadFromFile("resources/tileset.png")) {
        std::cout << "Failed loading tileset..." << std::endl;
        exit(0);
    }

    // Initialize variables...
    size.x     = 15;
    size.y     = 13;
    window     = new sf::RenderWindow(sf::VideoMode(19*16, 22*16), "Pengo");
    window->setFramerateLimit(60);
    RandomMaps();
    labyrinth       = labyrinth1;
    pengo           = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    this->addSwarm(level1);
    collision       = new Collision();
    snoBeesPerLevel = 8;
    endGame         = false;
    level           = 1;
    maxLevels       = 10;

    // Start game loop...
    this->Draw();
    this->GameLoop();
}



Game::~Game() {
    delete pengo;
    for (SnoBee* snobee : swarm) {
        delete snobee;
    }
    delete collision;
    swarm.clear();
    delete labyrinth1;
    delete labyrinth2;
    delete window;
    delete gameInstance;
    pengo        = NULL;
    labyrinth    = NULL;
    labyrinth1   = NULL;
    labyrinth2   = NULL;
    labyrinth3   = NULL;
    labyrinth4   = NULL;
    labyrinth5   = NULL;
    labyrinth6   = NULL;
    labyrinth7   = NULL;
    labyrinth8   = NULL;
    labyrinth9   = NULL;
    labyrinth10   = NULL;
    window       = NULL;
    gameInstance = NULL;
    collision    = NULL;
}



void Game::GameLoop() {

    while (window->isOpen()) {
        deltaTime = clock.restart().asSeconds();

        // Events loop...
        EventsLoop();
        
        if (pengo->getDead()) {

            // Restart since the first level...
            level = 1;
            this->restoreLevel();
            pengo->restoreLifes();

        } else if (pengo->getStunned()  &&  !pengo->getGodMode()) {

            pengo->Update(deltaTime, labyrinth);
            if (levelClock.getElapsedTime().asSeconds() >= 2.45f)
                this->restoreLevel();

        } else if (!endGame) {

            if (this->levelCompleted()) {

                // Next level...
                if (level == 1) {
                    level = 2;
                    this->restoreLevel();
                } else {
                    endGame = true;
                }
            } else {

                // Update objects...
                pengo->Update(deltaTime, labyrinth);
                GameFunctionality();
                if (pengo->getStunned()  &&  pengo->getGodMode()  &&  levelClock.getElapsedTime().asSeconds() >= 1.15f)
                    pengo->restartPosition();
            }
            
        } else {

            window->close();

        }

        // Draw all the objects...
        Draw();
    }

    // Break free all memory...
    delete gameInstance;
    gameInstance = NULL;
}



void Game::EventsLoop() {

    while (window->pollEvent(event)) {

        switch (event.type) {

            // Close the window manually
            case sf::Event::Closed:
                window->close();
                break;

            // Click one key...
            case sf::Event::KeyPressed:

                switch (event.key.code) {

                    // Close the window pressing escape
                    case sf::Keyboard::Escape:
                        window->close();
                        break;

                    // Active god mode
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
                        // std::cout << "No key handled..." << std::endl;
                        break;
                }
                break;

            default:
                // std::cout << "No event handled..." << std::endl;
                break;
        }
    }
}




void Game::GameFunctionality() {
    labyrinth->Update(deltaTime);
    for (SnoBee* snobee : swarm) {
        if (snobee  &&  !snobee->getDead()) {
            snobee->Update(deltaTime, labyrinth);

            // Check collision snobee-pengo
            if (collision->checkCollision(snobee->getSprite(), pengo->getSprite(), 10.0f)) {
                pengo->loseLife();
                levelClock.restart();
            }

            // Check collision snobee-block
            for (unsigned int i=0; i<size.x; i++) {
                Block* _block;
                for (unsigned int j=0; j<size.y; j++) {
                    _block = labyrinth->getBlock(i, j);

                    // If we smashes Sno-Bee add other one
                    if (_block  &&  _block->getDirection() > -1  &&  snobee->getFree()  &&  collision->checkCollision(_block->getSprite(), snobee->getSprite(), 20.f)) {
                        snobee->getSmashed(_block);
                        this->addSnoBee();
                    }
                    _block = NULL;
                }
            }
        }
    }

}




void Game::Draw() {

    // Clear viewport...
    window->clear(sf::Color::Black);

    // Print objects...
    labyrinth->Draw(*window);
    pengo->Draw(*window);
    for (SnoBee* snobee : swarm) {
        if (snobee  &&  !snobee->getDead())
            snobee->Draw(*window);
    }
   // abeja->Draw(*window);

    // Display them on it...
    window->display();
}



// Create the sno-bees for level
void Game::addSwarm(int level[15][13]) {

    for (SnoBee* snobee : swarm) {
        delete snobee;
    }
    swarm.clear();

    for (int i=0; i<15; i++) {
        for (int j=0; j<13; j++) {
            if (level[i][j] == 2) {
                swarm.push_back(new SnoBee(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0, 2), sf::Vector2i(i, j)));
            }
        }
    }
}



// Add new Sno-Bees for replacing the old smashed
void Game::addSnoBee() {

    if (swarm.size() < snoBeesPerLevel) {
        sf::Vector2i _newPosition = labyrinth->getFreePosition();

        swarm.push_back(new SnoBee(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0, 2), _newPosition));
    }
}


// Verify if the level has been completed
bool Game::levelCompleted() {
    unsigned int _counter = 0;

    if (swarm.size() == snoBeesPerLevel)
        for (SnoBee* snobee : swarm)
            if (snobee  &&  snobee->getDead())
                _counter++;

    if (_counter == snoBeesPerLevel) {
        return true;
    } else {
        return false;
    }
}



// Restore one level
void Game::restoreLevel() {

    if(level == 1) {
        this->addSwarm(level1);
        labyrinth1 = new Labyrinth(&tileset, level1);
        labyrinth = labyrinth1;
    }
    if(level == 2) {
        this->addSwarm(level2);
        labyrinth2 = new Labyrinth(&tileset, level2);
        labyrinth = labyrinth2;
    }
    if(level == 3) {
        this->addSwarm(level3);
        labyrinth3 = new Labyrinth(&tileset, level3);
        labyrinth = labyrinth3;
    }
    if(level == 4) {
        this->addSwarm(level4);
        labyrinth4 = new Labyrinth(&tileset, level4);
        labyrinth = labyrinth4;
    }
    if(level == 5) {
        this->addSwarm(level5);
        labyrinth5 = new Labyrinth(&tileset, level5);
        labyrinth = labyrinth5;
    }
    if(level == 6) {
        this->addSwarm(level6);
        labyrinth6 = new Labyrinth(&tileset, level6);
        labyrinth = labyrinth6;
    }
    if(level == 7) {
        this->addSwarm(level7);
        labyrinth7 = new Labyrinth(&tileset, level7);
        labyrinth = labyrinth7;
    }
    if(level == 8) {
        this->addSwarm(level8);
        labyrinth8 = new Labyrinth(&tileset, level8);
        labyrinth = labyrinth8;
    }
    if(level == 9) {
        this->addSwarm(level9);
        labyrinth9 = new Labyrinth(&tileset, level9);
        labyrinth = labyrinth9;
    }
    if(level == 10) {
        this->addSwarm(level10);
        labyrinth10 = new Labyrinth(&tileset, level10);
        labyrinth = labyrinth10;
    }
    pengo->restartInitialPosition();
}

//Generate random maps
void Game::RandomMaps(){
   /* map.readMap(1);
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            level1[x][y] = map.blocks[x][y];
        }
    }*/
    int num = rand()%2;
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level1[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level1[x][y] = 2;
            }else{
                //Blocks
                level1[x][y] = num;
            }
            
            num = rand()%2;
        }
    }
    labyrinth1 = new Labyrinth(&tileset, level1);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level2[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level2[x][y] = 2;
            }else{
                //Blocks
                level2[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth2 = new Labyrinth(&tileset, level2);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level3[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level3[x][y] = 2;
            }else{
                //Blocks
                level3[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth3 = new Labyrinth(&tileset, level3);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level4[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level4[x][y] = 2;
            }else{
                //Blocks
                level4[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth4 = new Labyrinth(&tileset, level4);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level5[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level5[x][y] = 2;
            }else{
                //Blocks
                level5[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth5 = new Labyrinth(&tileset, level5);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level6[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level6[x][y] = 2;
            }else{
                //Blocks
                level6[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth6 = new Labyrinth(&tileset, level6);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level7[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level7[x][y] = 2;
            }else{
                //Blocks
                level7[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth7 = new Labyrinth(&tileset, level7);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level8[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level8[x][y] = 2;
            }else{
                //Blocks
                level8[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth8 = new Labyrinth(&tileset, level8);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level9[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level9[x][y] = 2;
            }else{
                //Blocks
                level9[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth9 = new Labyrinth(&tileset, level9);

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 13; y++){
            if((x == 0 &&  y == 2) || (x == 0 &&  y == 4) || (x == 1 &&  y == 3) || (x == 2 &&  y == 9) || (x == 3 &&  y == 8) || (x == 3 &&  y == 10) || (x == 4 &&  y == 9) || (x == 6 &&  y == 0) || (x == 6 &&  y == 5) || (x == 6 &&  y == 6) || (x == 6 &&  y == 12) || (x == 7 &&  y == 1) || (x == 7 &&  y == 4) || (x == 7 &&  y == 6) || (x == 8 &&  y == 0) || (x == 8 &&  y == 5) || (x == 8 &&  y == 12) || (x == 10 &&  y == 9) ||  (x == 11 &&  y == 8) || (x == 11 &&  y == 10) || (x == 12 &&  y == 9) || (x == 13 &&  y == 3) || (x == 14 &&  y == 2) || (x == 14 &&  y == 4)){
                //Empty blocks
                level10[x][y] = 0;
            }else if((x == 0 &&  y == 3) || (x == 3 &&  y == 9) || (x == 7 &&  y == 0) || (x == 14 &&  y == 3) || (x == 11 &&  y == 9) || (x == 7 &&  y == 5)){
                //Enemies
                level10[x][y] = 2;
            }else{
                //Blocks
                level10[x][y] = num;
            }
            num = rand()%2;
        }
    }
    labyrinth10 = new Labyrinth(&tileset, level10);
}