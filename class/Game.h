#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Block.h"
#include "Character.h"
#include "Animation.h"
#include "IceBlock.h"
#include "Pengo.h"
#include "Labyrinth.h"
#include "SnoBee.h"
#include "Collision.h"
#include "Map.h"


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
        Labyrinth* labyrinth1;
        Labyrinth* labyrinth2;
        Labyrinth* labyrinth3;
        Labyrinth* labyrinth4;
        Labyrinth* labyrinth5;
        Labyrinth* labyrinth6;
        Labyrinth* labyrinth7;
        Labyrinth* labyrinth8;
        Labyrinth* labyrinth9;
        Labyrinth* labyrinth10;
        Labyrinth* labyrinth;
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
        Map map;
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
        /*int level1[15][13] = {
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 1, 2, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
            {0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
            {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 2, 1, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
            {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
            {1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
            {0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 2, 1, 0},
            {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
            {2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}
        };
        int level2[15][13] = {
            {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 2},
            {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0},
            {0, 1, 2, 1, 0, 1, 0, 1, 0, 0, 2, 1, 0},
            {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0}
        };*/

};