#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u coordPj, float switchTime, int numSprites) {
    this->switchTime = switchTime;
    this->coordPj = coordPj;
    uvRect.width = 16;
    uvRect.height = 16;
    totalTime = 0.0f;
    actualCoord.y = 0;
    actualCoord.x = 0;
    range.x = 0;
    range.y = numSprites-1;
}

void Animation::Update(int row, int column, float deltaTime) {

    // If pj change movement then change rectangle...
    if(actualCoord.y != row || (column<range.x || column>range.y)){
        actualCoord.y = row;
        actualCoord.x = column;
        range.y = range.y-range.x + column;
        range.x = column;
        totalTime = 0.0f;
    }else{
        // Count the time...
        totalTime += deltaTime;
    }
    // Next rectangle of the same animation...
    if(totalTime >= switchTime) {
        totalTime -= switchTime;
        actualCoord.x++;
        if(actualCoord.x > range.y) {
            actualCoord.x = range.x;
        }
    }

    // Update uvRect...
    uvRect.left = (coordPj.x*8*uvRect.width) + (actualCoord.x*uvRect.width);
    uvRect.top = (coordPj.y*4*uvRect.height) + (actualCoord.y*uvRect.height);
    
    if(coordPj.y == 3){
        uvRect.top += uvRect.height;
    }
}