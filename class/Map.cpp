#include "Map.h"



Map::Map(sf::Texture* tileset, int level[15][13]) {
    isHit = false;

    // Build the walls and put them on screen...
    leftWall   = new sf::Sprite(*tileset);
    rightWall  = new sf::Sprite(*tileset);
    topWall    = new sf::Sprite(*tileset);
    bottomWall = new sf::Sprite(*tileset);

    leftWall->setTextureRect(sf::IntRect(8, 16, 8, 256));
    rightWall->setTextureRect(sf::IntRect(8, 16, 8, 256));
    topWall->setTextureRect(sf::IntRect(0, 8, 224, 8));
    bottomWall->setTextureRect(sf::IntRect(0, 8, 224, 8));

    leftWall->setPosition(0, 24);
    leftWall->setOrigin(4, 0);
    leftWall->setScale(-1, 1);
    leftWall->setOrigin(8, 0);
    rightWall->setPosition(216, 24);
    topWall->setPosition(0, 24);
    topWall->setOrigin(0, 4);
    topWall->setScale(1, -1);
    topWall->setOrigin(0, 8);
    bottomWall->setPosition(0, 272);


    // Reserve momory for the matrix...
    size.x = 15;  size.y = 13;
    glacier = new Block**[size.x];
    for (unsigned int i=0; i<size.x; i++) {
        glacier[i] = new Block*[size.y];
    }
    
    // Put all the ice blocks...
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (level[i][j] == 1) {
                glacier[i][j] = new IceBlock(tileset, j, i);
            } else {
                glacier[i][j] = NULL;
            }
        }
    }

    // Important position...
    for (int i=0; i<int(size.x); i++)
        for (int j=0; j<int(size.y); j++)
            if (glacier[i][j])
                glacier[i][j]->setPosition(sf::Vector2i(i, j));

}



Map::~Map() {
    delete leftWall;
    leftWall = NULL;
    delete rightWall;
    rightWall = NULL;
    delete topWall;
    topWall = NULL;
    delete bottomWall;
    bottomWall = NULL;
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j])
                delete glacier[i][j];
        }
        delete[] glacier[i];
    }
    delete[] glacier;
    glacier = NULL;
    for (Block* block : icicles) {
        if (block != NULL) {
            delete block;
            block = NULL;
        }
    }
    icicles.clear();
}



void Map::Update(float deltaTime) {

    // Update the position for each block...
    for (int i=0; i<int(size.x); i++)
        for (int j=0; j<int(size.y); j++)
            if (glacier[i][j]  &&  glacier[i][j]->getCanCollide()) {
                sf::Vector2i _pos = glacier[i][j]->getPosition();
                int _x = _pos.x, _y = _pos.y;

                if (i != _x  ||  j != _y) {
                    glacier[_x][_y] = glacier[i][j];
                    glacier[i][j]   = NULL;
                }
                
            }


    // Update each block...
    for (unsigned int i=0; i<size.x; i++)
        for (unsigned int j=0; j<size.y; j++)
            if (glacier[i][j]) {

                if (glacier[i][j]->getCanCollide()) {
                    sf::Vector2i _pos = glacier[i][j]->getPosition();

                    this->pengoPush(_pos, glacier[i][j]->getDirection(), false);
                    glacier[i][j]->dontCollide();
                }
                glacier[i][j]->Update(deltaTime);
            }


    // Delete the ice block falling...
    for (Block* block : icicles) {
        if (block) {
            if (IceBlock* ice = dynamic_cast<IceBlock*>(block)) {
                if (ice->getBroke()) {
                //    delete block;
                    block = NULL;
                } else {
                    block->Update(deltaTime);
                }
            }
        }
    }
}



void Map::Draw(sf::RenderWindow &window) {
    window.draw(*leftWall);
    window.draw(*rightWall);
    window.draw(*topWall);
    window.draw(*bottomWall);
    for (unsigned int i=0; i<size.x; i++) {
        for (unsigned int j=0; j<size.y; j++) {
            if (glacier[i][j])
                glacier[i][j]->Draw(window);
        }
    }

    for (Block* block : icicles) {
        if (block) {
            if (IceBlock* ice = dynamic_cast<IceBlock*>(block))
                if (!ice->getBroke())
                    block->Draw(window);
        }
    }
}



bool Map::checkPosition(sf::Vector2i position) {
    bool _avaliable = false;
    int _x = position.x, _y = position.y;

    // Check the walls...
    if (_x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)) {
        if (glacier[_x][_y] == NULL) {
            _avaliable = true;
        }
    }

    return _avaliable;
}



void Map::pengoPush(sf::Vector2i position, int direction, bool breakIt) {
    int _x = position.x, _y = position.y;

    // Check a block position...
    if (!this->checkPosition(position)  &&  _x >= 0  &&  _x < int(size.x)  &&  _y >= 0  &&  _y < int(size.y)) {
        sf::Vector2i _nextPosition = position;

        // Calculate the following position from block...
        if (direction == 0)
            _nextPosition.x--;
        else if (direction == 1)
            _nextPosition.y++;
        else if (direction == 2)
            _nextPosition.x++;
        else if (direction == 3)
            _nextPosition.y--;

        // Move the block or break it if cotains ice...
        if (this->checkPosition(_nextPosition)) {
            glacier[_x][_y]->setDirection(direction);
        } else if (IceBlock* ice = dynamic_cast<IceBlock*>(glacier[_x][_y])) {
            if (breakIt) {
                ice->breakDown();
                icicles.push_back(glacier[_x][_y]);
                glacier[_x][_y] = NULL;
            } else {
                glacier[_x][_y]->setDirection(-1);
            }
        }
    }
}



Block* Map::getBlock(unsigned int x, unsigned int y) {
    return glacier[x][y];
}



sf::Vector2i Map::getFreePosition() {
    sf::Vector2i _freePosition(0, 0);

    do {
        _freePosition.x = rand()%15,
        _freePosition.y = rand()%13;
    } while (!this->checkPosition(_freePosition));

    return _freePosition;
}