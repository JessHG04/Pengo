#include "Map.h"

Map::Map(){
}

void Map::readMap(int nivel){
    //bloques.clear();
    //bloquesReinicio.clear();
    //borde.clear();

    tinyxml2::XMLDocument doc;
    doc.LoadFile("resources/Mapas/MapaBloques.tmx");

    tinyxml2::XMLElement *mapp = doc.FirstChildElement("map");

    //Creación de cada bloque
    this->nodo = mapp->FirstChildElement("objectgroup");
    this->data = nodo->FirstChildElement("object");
    int tipo2 = nivel;
    
    if(nivel == 10){
        tipo2 = 1;
    }
    int tipo = 1;
    int xaux  = 48;
    int yaux = 64;
    int num = rand()%2;
    int aux [15][13];
    //Block *baux = NULL;
    
    for(int x = 0; x < 15; x++ ){
        for(int y = 0; y < 13; y++){
            if(this->data != NULL){
                data->QueryIntAttribute("type", &tipo);
                data->QueryIntAttribute("x", &xaux);
                data->QueryIntAttribute("y", &yaux);
                //baux = new Block(tipo, xaux, yaux);
                if((xaux == 104 && yaux == 296) || (xaux == 200 && yaux == 248) || (xaux == 136 && yaux == 184)){ //Huevos
                    //baux = new Block(tipo2, xaux, yaux);
                    //aux.push_back(baux);
                    //aux[x][y] = tipo;
                    //this->data = data->NextSiblingElement("object");
                }else if((xaux == 152 && yaux == 120) || (xaux == 88 && yaux == 232) || (xaux == 216 && yaux == 232)){ //Bloques estrella
                    //tipo = 10;
                    //baux = new Block(tipo, xaux, yaux);
                    //aux.push_back(baux);
                    //this->data = data->NextSiblingElement("object");
                }else{
                    if(num == 0){                   
                        if((xaux == 152 && yaux == 184) || (xaux == 88 && yaux == 72) || (xaux == 104 && yaux == 72) || (xaux == 120 && yaux == 72) || (xaux == 104 && yaux == 88) || (xaux == 200 && yaux == 120) || (xaux == 200 && yaux == 104) || (xaux == 216 && yaux == 120) || (xaux == 200 && yaux == 136) || (xaux == 184 && yaux == 120) || (xaux == 56 && yaux == 184) || (xaux == 56 && yaux == 168) || (xaux == 72 && yaux == 184) || (xaux == 56 && yaux == 200) || (xaux == 133 && yaux == 168) || (xaux == 136 && yaux == 200) || (xaux == 120 && yaux == 184) || (xaux == 200 && yaux == 232) || (xaux == 216 && yaux == 248) || (xaux == 200 && yaux == 264) || (xaux == 184 && yaux == 248) || (xaux == 104 && yaux == 280) || (xaux == 120 && yaux == 196)|| (xaux == 88 && yaux == 296)){ //No quiero que se generen bloques ahí
                            //aux.push_back(NULL);
                            blocks[x][y] = 0;
                            restartBlocks[x][y] = 0;
                        }else{
                            blocks[x][y] = num;
                            restartBlocks[x][y] = num;
                        }
                        this->data = data->NextSiblingElement("object");
                    }else{
                        //aux.push_back(NULL);
                        this->data = data->NextSiblingElement("object");
                    }
                }
                num = rand()%2;
                //std::cout << "Numero aleatorio: " << num << std::endl;
            }
            //baux = NULL;
        }
        //bloques.push_back(aux);
        //bloquesReinicio.push_back(aux);
        //aux.clear();
    }
    
    //Creacion del borde
    /*this->nodo = nodo->NextSiblingElement("objectgroup");
    this->data = nodo->FirstChildElement("object");
    for(int x = 0; x < 17; x++ ){
        for(int y = 0; y < 15; y++){
            if(this->data != NULL){
                if(x == 0 || x == 16 || y == 0 || y == 14){
                    data->QueryIntAttribute("type", &tipo);
                    data->QueryIntAttribute("x", &xaux);
                    data->QueryIntAttribute("y", &yaux);
                    baux = new Block(tipo, xaux, yaux);
                    aux.push_back(baux);
                    this->data = data->NextSiblingElement("object");
                }
                else{
                    aux.push_back(NULL);
                }
            }
        }
        borde.push_back(aux);
        aux.clear();
    }*/
}

void Map::ReinicioNivel(){
    /*std::vector<Block*> aux;
    Block *baux = NULL;
    int tipo = 1;
    int xaux  = 48;
    int yaux = 64;
    
    bloques.clear();
    aux.clear();
    /*if(bloques.empty()){
        for(int x = 0; x < bloquesReinicio.size(); x++){
            for(int y = 0; y < bloquesReinicio[x].size(); y++){
                if(bloquesReinicio[x][y]!=NULL){
                    tipo = bloquesReinicio[x][y].getType();
                    xaux = (bloquesReinicio[x][y].getSprite()->getPosition().x) - 8;
                    yaux = (bloquesReinicio[x][y].getSprite()->getPosition().y) - 8;
                    baux = new Block(tipo, xaux, yaux);
                    aux.push_back(baux);
                }else{
                    aux.push_back(NULL);
                }
            }
            bloques.push_back(aux);
            aux.clear();
        }
    }
    for(int x = 0; x<15; x++){
        for(int y = 0; y < 13; y++){
            blocks[x][y] = restartBlocks[x][y];
        }
    }
}

/*
void Map::Vacio(){
    //bloques.clear();
}

void Map::clearMap(){
    /*for(int x = 0; x < bloquesReinicio.size(); x++){
        for(int y = 0; y < bloquesReinicio[x].size(); y++){
            if(bloquesReinicio[x][y]!= NULL){
                delete bloquesReinicio[x][y];
            }
        }
    }*/
    /*
    for(int x = 0; x < bloques.size(); x++){
        for(int y = 0; y < bloques[x].size(); y++){
            if(bloques[x][y]!= NULL){
                delete bloques[x][y];
            }
        }
    }
    
    for(int x = 0; x < borde.size(); x++){
        for(int y = 0; y < borde[x].size(); y++){
            if(borde[x][y]!= NULL){
                delete borde[x][y];
            }
        }
    }
    bloques.clear();
    bloquesReinicio.clear();
    borde.clear();
    nodo = NULL;
    data = NULL;
    //std::cout << bloques.size() << bloquesReinicio.size() << borde.size() << std::endl;
}*/
/*
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    states.texture = &tile;
    target.draw(vertex,states);
}*/
/*
void Map::drawBloques(sf::RenderWindow &ventana){
    //sf::Sprite *sprit;
    for(int x = 0; x < bloques.size(); x++){
        for(int y = 0; y < bloques[0].size(); y++){
            if(bloques[x][y]!= NULL){
                ventana.draw(bloques[x][y]->getSprite());
            }
        }
    }

    for(int x = 0; x < borde.size(); x++){
        for(int y = 0; y < borde[0].size(); y++){
            /*if(!borde[x][y].getVacio()){
                sprit = borde[x][y].getSprite();
                ventana.draw(*sprit);
            }*/
            /*if(borde[x][y]!= NULL){
                ventana.draw(borde[x][y]->getSprite());
            }
        }
    }

}*/
/*
Map::~Map(){
    
}*/