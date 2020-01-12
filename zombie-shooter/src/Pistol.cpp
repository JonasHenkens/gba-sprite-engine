//
// Created by Souhaib El Habti on 12/01/2020.
//

#include "Pistol.h"
#include "spritedata.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

std::vector<Sprite *> Pistol::sprites() {
    return {
            sprite.get()
    };
}

int Pistol::getX() {
    return sprite->getX();
}

int Pistol::getY() {
    return sprite->getY();
}

int Pistol::getWidth(){
    return sprite->getWidth();
}

int Pistol::getHeight(){
    return sprite->getHeight();
}

void Pistol::move (bool up, bool down, bool left, bool right) {

    if (left == right) {
        sprite->setVelocity(0, sprite->getDy());
    }
    else if (right) {
        sprite->setVelocity(+2, sprite->getDy());
    }
    else if (left) {
        sprite->setVelocity(-2, sprite->getDy());
    }
    if (up == down) {
        sprite->setVelocity(sprite->getDx(), 0);
    }
    else if (up) {
        sprite->setVelocity(sprite->getDx(), -2);
    }
    else if (down) {
        sprite->setVelocity(sprite->getDx(), +2);
    }
}

void Pistol::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_8_8)
            .withLocation(x, y)
            .withData(pistolTiles, sizeof(pistolTiles))
            .buildPtr();
}


Pistol::Pistol(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin) {
    setBuilder(builder, x, y);
    bullets = bulletsBegin;
}

