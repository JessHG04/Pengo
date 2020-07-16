#include "Animacion.h"

Animacion::Animacion(sf::Texture* textura, sf::Vector2u img, float tiempo, int n) {
    tiempoCambio = tiempo;
    cuadrante = img;
    uvRect.width = 16;
    uvRect.height = 16;
    tiempoTotal = 0.0f;
    imgActual.y = 0;
    imgActual.x = 0;
    rango.x = 0;
    rango.y = n-1;
}

void Animacion::Update(int fila, int columna, float deltaTime) {

    // If pj change movement then change rectangle...
    if(imgActual.y != fila || (columna<rango.x || columna>rango.y)){
        imgActual.y = fila;
        imgActual.x = columna;
        rango.y = rango.y-rango.x + columna;
        rango.x = columna;
        tiempoTotal = 0.0f;
    }else{
        // Count the time...
        tiempoTotal += deltaTime;
    }
    // Next rectangle of the same Animacion...
    if(tiempoTotal >= tiempoCambio) {
        tiempoTotal -= tiempoCambio;
        imgActual.x++;
        if(imgActual.x > rango.y) {
            imgActual.x = rango.x;
        }
    }

    // Update uvRect...
    uvRect.left = (cuadrante.x*8*uvRect.width) + (imgActual.x*uvRect.width);
    uvRect.top = (cuadrante.y*4*uvRect.height) + (imgActual.y*uvRect.height);
    
    if(cuadrante.y == 3){
        uvRect.top += uvRect.height;
    }
}