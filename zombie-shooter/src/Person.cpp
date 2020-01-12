//
// Created by Souhaib El Habti on 22/12/2019.
//

#include "Person.h"
#include "spritedata.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

std::vector<Sprite *> Person::sprites() {
    return {
            sprite.get()
    };
}

Weapon Person::getGun() {
    return gun;
}

void Person::setGun(Weapon gun1) {
    gun = gun1;
}

bool Person::reload(int* ammo) {
    if(gun.getMagazine() - gun.getBullets() <= 0){
        return true;
    }
    else if(*ammo > gun.getMagazine() - gun.getBullets()){
        int enoughBullets = gun.getMagazine() - gun.getBullets();
        gun.reload(enoughBullets);
        *ammo =  *ammo - enoughBullets;
        return true;
    }
    else if(*ammo <= 0){
        return false;
    }
    else{
        gun.reload(*ammo);
        *ammo =  0;
        return true;
    }
}

bool Person::shoot() {
    if(gun.getBullets() > 0){
        gun.shoot();
        return true;
    }
    else{
       return false;
    }
}

int Person::getX() {
    return sprite->getX();
}

int Person::getY() {
    return sprite->getY();
}

int Person::getWidth(){
    return sprite->getWidth();
}

int Person::getHeight(){
    return sprite->getHeight();
}

void Person::move (bool up, bool down, bool left, bool right) {

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

void Person::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_16_32)
            .withLocation(x, y)
            .withData(personTiles, sizeof(personTiles))
            .buildPtr();
}
