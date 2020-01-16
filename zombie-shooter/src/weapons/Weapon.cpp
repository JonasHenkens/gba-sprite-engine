//
// Created by Souhaib El Habti on 22/12/2019.
//

#include "Weapon.h"

void Weapon::reload(int ammo) {
    bullets = bullets + ammo;
}

void Weapon::shoot() {
    bullets--;
}

int Weapon::getMagazine() {
    return magazine;
}

int Weapon::getBullets() {
    return bullets;
}

int Weapon::getHeadshotChance() {
    return chanceOfHeadshot;
}

int Weapon::getDamage() {
    return damage;
}

void Weapon::move (bool up, bool down, bool left, bool right) {

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

int Weapon::getX() {
    return sprite->getX();
}

int Weapon::getY() {
    return sprite->getY();
}

int Weapon::getWidth(){
    return sprite->getWidth();
}

int Weapon::getHeight(){
    return sprite->getHeight();
}

std::vector<Sprite *> Weapon::sprites() {
    std::vector<Sprite *> sprites = {
            sprite.get()
    };
    return sprites;
}