//
// Created by Souhaib El Habti on 22/12/2019.
//

#include "Person.h"
#include "spritedata.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

bool Person::getStillAlive() {
    return stillAlive;
}

void Person::die() {
    //if hit by zombie => stillAlive = false; (how to include Zombie x and y coords???)
}

Weapon Person::getGun() {
    return gun;
}

void Person::setGun(Weapon gun1) {
    gun = gun1;
}

void Person::reload() {
    /* als er ... knop wordt gedrukt => kijk of speler genoeg ammo heeft om
        wapen volledig te vullen (meer/gelijk aan gun.getMagazine)
     * Zo ja => gun.reload(gun.getMagazine()-gun.getBullets());
     * Zo nee => Steek alle resterende kogels in gun
     * Indien volledig geen kogels => weergave "No Ammo!!!"
     */
}

void Person::shoot() {
    if(gun.getBullets() > 0){
        gun.shoot();
    }
    else{
        // Weergave: "Weapon empty!!!"
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

void Person::setBuilder(SpriteBuilder<Sprite> builder) {
    sprite = builder
            .withSize(SIZE_16_32)
            .withLocation(0, 128)
            .withData(zombieheadTiles, sizeof(zombieheadTiles))
            .buildPtr();
}
