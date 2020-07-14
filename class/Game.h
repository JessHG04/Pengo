#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Block.h"
#include "Character.h"
#include "Animation.h"
#include "IceBlock.h"
#include "Pengo.h"
#include "Map.h"
#include "SnoBee.h"
#include "Collision.h"


class Game {

    public:
        static Game* getInstance();

    protected:
        Game();
        ~Game();
        void GameLoop();
        void RandomMaps();
        void EventsLoop();
        void GameFunctionality();
        void Draw();
        void addSwarm(int[15][13]);
        void addSnoBee();
        bool levelCompleted();
        void restoreLevel();


    private:
        static Game* gameInstance;
        sf::RenderWindow* window;
        Map* map;
        Map* map1;
        Map* map2;
        Map* map3;
        Map* map4;
        Map* map5;
        Map* map6;
        Map* map7;
        Map* map8;
        Map* map9;
        Map* map10;
        Pengo* pengo;
        sf::Clock clock;
        sf::Clock levelClock;
        float deltaTime;
        sf::Event event;
        sf::Texture spriteSheet, tileset;
        sf::Vector2u size;
        std::vector<SnoBee*> swarm;
        unsigned int snoBeesPerLevel;
        Collision* collision;
        int level;
        int maxLevels;
        bool endGame;
        int level1[15][13];
        int level2[15][13];
        int level3[15][13];
        int level4[15][13];
        int level5[15][13];
        int level6[15][13];
        int level7[15][13];
        int level8[15][13];
        int level9[15][13];
        int level10[15][13];
};