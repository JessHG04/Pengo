#include "Animation.h"



Animation::Animation(sf::Texture* texture, sf::Vector2u coordPj, float changeTime, int numSprites) {
    this->changeTime = changeTime;
    this->coordPj    = coordPj;

    // Height and Width of sprite...
    uvRect.width  = texture->getSize().x / 40;
    uvRect.height = texture->getSize().y / 18;

    // Initial values...
    totalTime     = 0.0f;
    actualCoord.y = 0;
    actualCoord.x = 0;
    range.x       = 0;
    range.y       = numSprites-1;
}



Animation::~Animation() {

}



void Animation::Update(unsigned int row, unsigned int column, float deltaTime) {

    // If pj change movement then change rectangle...
    if (actualCoord.y != row  ||  (column<range.x || column>range.y)) {
        actualCoord.y = row;
        actualCoord.x = column;
        range.y = range.y-range.x + column;
        range.x = column;
        totalTime = 0.0f;
    } else {

        // Count the time...
        totalTime += deltaTime;
    }
    
    // Next rectangle of the same animation...
    if (totalTime >= changeTime) {
        totalTime -= changeTime;
        actualCoord.x++;

        if (actualCoord.x > range.y) {
            actualCoord.x = range.x;
        }
    }

    // Update uvRect...
    uvRect.left = (coordPj.x*8*uvRect.width) + (actualCoord.x*uvRect.width);
    uvRect.top  = (coordPj.y*4*uvRect.height) + (actualCoord.y*uvRect.height);

    // Adjust the last row on the texture...
    uvRect.top += (coordPj.y == 3) ? uvRect.height : 0;
}



sf::IntRect Animation::getUVRect() {
    return uvRect;
}



sf::Vector2f Animation::getOrigin() {
    return sf::Vector2f(uvRect.width/2, uvRect.height/2);
}



void Animation::setChangeTime(float changeTime) {
    this->changeTime = changeTime;
}



void Animation::setCoordPj(sf::Vector2u coordPj) {
    this->coordPj = coordPj;
}