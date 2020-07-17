#include "SnoBee.h"

SnoBee::SnoBee(sf::Texture* texture, float vel, float tiempo, sf::Vector2u cuadra, sf::Vector2i pos) : Personaje(texture, vel, tiempo, cuadra, pos){
    direccion = 2;
    quieto = false;
    muerto = false;
    bloque = NULL;
}

SnoBee::~SnoBee() {
    delete animacion;
    animacion = NULL;
    delete sprite;
    sprite = NULL;
    bloque = NULL;
}

void SnoBee::Update(float deltaTime, Mapa* mapa) {
    std::vector<sf::Vector2i> _movement;
    std::vector<int> _orientation;
    int _index = -1, _random;

    if (!caminando && !quieto && bloque == NULL) {
        if (mapa->comprobar(sf::Vector2i(posicion.x-1, posicion.y))) {
            _movement.push_back(sf::Vector2i(posicion.x-1, posicion.y));
            _orientation.push_back(0);
        }
        if (mapa->comprobar(sf::Vector2i(posicion.x, posicion.y+1))) {
            _movement.push_back(sf::Vector2i(posicion.x, posicion.y+1));
            _orientation.push_back(1);
        }
        if (mapa->comprobar(sf::Vector2i(posicion.x+1, posicion.y))) {
            _movement.push_back(sf::Vector2i(posicion.x+1, posicion.y));
            _orientation.push_back(2);
        }
        if (mapa->comprobar(sf::Vector2i(posicion.x, posicion.y-1))) {
            _movement.push_back(sf::Vector2i(posicion.x, posicion.y-1));
            _orientation.push_back(3);
        }

        if (_movement.size() > 0) {
            
            // Follow your way...
            for (unsigned int i=0; i<_orientation.size(); i++) {
                if (direccion == _orientation[i]) {
                    _index = int(i);
                    posicion = _movement[i];
                }
            }

            // Turn to one direccion...
            if (_index > -1) {
                quieto  = false;
                caminando = true;
            } else {
                _random = rand()%_movement.size();
                _index = _random;

                direccion = _orientation[_index];
                switch (_orientation[_index]) {
                    case 0:
                        columna = 4;
                        break;
                    case 1:
                        columna = 6;
                        break;
                    case 2:
                        columna = 0;
                        break;
                    case 3:
                        columna = 2;
                        break;
                }

                quieto  = true;
                caminando = false;
            }

            _orientation.clear();
            _movement.clear();
        }

    }


    if (quieto  ||  caminando) {

        // Move Sno-Bee...
        float _displacement = velocidad*deltaTime;

        // Calculate the displacement...
        if (recorrido+_displacement >= 16.0f) {
            _displacement = 16.0f - recorrido;
            caminando     = false;
            quieto      = false;
            recorrido          = 0.0f;
            sprite->setPosition(16+posicion.y*16, 40+posicion.x*16);
        } else {
            recorrido += _displacement;
        }

        if (caminando  &&  !quieto) {
            if (columna == 4)
                sprite->move(0, -_displacement);
            else if (columna == 6)
                sprite->move(_displacement, 0);
            else if (columna == 0)
                sprite->move(0, _displacement);
            else if (columna == 2)
                sprite->move(-_displacement, 0);
        }

        animacion->Update(fila, columna, deltaTime);
        sprite->setTextureRect(animacion->getUvRect());

    } else if (bloque) {
        sf::Vector2f _displacement(0.0f, 0.0f);
        sf::Vector2f _posicion;

        // Suffer the hit...
        if (bloque->getDireccion() > -1) {

            // direction movement...
            switch (bloque->getDireccion()) {
                case 0:
                    columna = 0;
                    _displacement.y = -10;
                    break;
                case 1:
                    columna = 2;
                    _displacement.x = +10;
                    break;
                case 2:
                    columna = 4;
                    _displacement.y = +10;
                    break;
                case 3:
                    columna = 6;
                    _displacement.x = -10;
                    break;
            }

            if (fila != 4) {
                fila = 4;
                animacion->Update(fila, columna, deltaTime);
                sprite->setTextureRect(animacion->getUvRect());
            }

            _posicion = bloque->getSprite()->getPosition();
            sprite->setPosition(_posicion + _displacement);

        } else {
            muerto = true;
        }

    }

}

void SnoBee::getEmpujado(Bloque* bloq) {
    bloque = bloq;
    quieto  = false;
    caminando = false;
}

bool SnoBee::getLibre() {
    if (bloque)
        return false;
    else
        return true;
}
