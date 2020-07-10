#include "Game.h"



// Initialize pointer
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
    window     = new sf::RenderWindow(sf::VideoMode(610.f, 506.f), "MSX-Pengo FV");
    window->setFramerateLimit(60);
    labyrinth1      = new Labyrinth(&tileset, level1);
    labyrinth2      = new Labyrinth(&tileset, level2);
    labyrinth       = labyrinth1;
    pengo           = new Pengo(&spriteSheet, 45.0f, 0.2f, sf::Vector2u(0,0), sf::Vector2i(6,6));
    this->addSwarm(level1);
    collision       = new Collision();
    snoBeesPerLevel = 8;
    endGame         = false;
    level           = 1;

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
    delete camera;
    delete window;
    delete gameInstance;
    pengo        = NULL;
    labyrinth    = NULL;
    labyrinth1   = NULL;
    labyrinth2   = NULL;
    camera       = NULL;
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
                        if (level == 1) {
                            level = 2;
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

    camera->Update(pengo->getSprite()->getPosition().y);
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

    if (level == 1) {
        this->addSwarm(level1);
        labyrinth1 = new Labyrinth(&tileset, level1);
        labyrinth = labyrinth1;
    } else {
        this->addSwarm(level2);
        labyrinth2 = new Labyrinth(&tileset, level2);
        labyrinth = labyrinth2;
    }
    pengo->restartInitialPosition();
    camera->restartPosition();
}