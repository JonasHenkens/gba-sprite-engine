//
// Created by Souhaib El Habti on 27/12/2019.
//

#include "Zombie.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "spritedata.h"

Zombie::Zombie(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy) {
    setBuilder(builder, x, y);
    setVelocity(dx, dy);
}

std::vector<Sprite *> Zombie::sprites() {
    return {
            sprite.get()
    };
}

void Zombie::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_16_32)
            .withLocation(x, y)
            .withData(zombieTiles, sizeof(zombieTiles))
            .buildPtr();
}

void Zombie::setVelocity(int dx, int dy) {
    sprite->setVelocity(dx*speedMultiplier, dy*speedMultiplier);
}

int Zombie::getX() {
    return sprite->getX();
}

int Zombie::getY() {
    return sprite->getY();
}

int Zombie::getDx() {
    return sprite->getDx();
}

int Zombie::getDy() {
    return sprite->getDy();
}

int Zombie::getSpeedMultiplier() {
    return speedMultiplier;
}

void Zombie::setSpeedMultiplier(int speedMultiplier) {
    this->speedMultiplier = speedMultiplier;
    setVelocity(sprite->getDx(), sprite->getDy());
}

int Zombie::getWidth(){
    return sprite->getWidth();
}

int Zombie::getHeight(){
    return sprite->getHeight();
}

bool Zombie::isDead() {
    if(life>0){
        return false;
    }
    else{
        return true;
    }
}

bool Zombie::isHeadshot() {
    // kijk naar wapen die shiet en doe random waarde
    if(false){
        headshot = true;
    }
    else{
        headshot = false;
    }
    return headshot;
}

void Zombie::hit() {
    if(!isDead()){
        int weaponDamage = 0; // how to find damage of weapon??
        if(headshot){
            life = life - weaponDamage*2;
        }
        else {
            life = life - weaponDamage;
        }
    }
}

int Zombie::getLife() {
    return life;
}