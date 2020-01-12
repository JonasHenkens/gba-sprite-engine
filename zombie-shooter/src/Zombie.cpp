//
// Created by Souhaib El Habti on 27/12/2019.
//

#include "Zombie.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "spritedata.h"

Zombie::Zombie(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy, int lifePoints) {
    setBuilder(builder, x, y);
    setVelocity(dx, dy);
    life = lifePoints;
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
    sprite->setVelocity(dx, dy);
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

void Zombie::hit(int damage, bool isHeadshot) {
    if(!isDead()){
        if(isHeadshot){
            life = life - damage*2;
        }
        else {
            life = life - damage;
        }
    }
}

int Zombie::getLife() {
    return life;
}

void Zombie::setCoords(int x, int y) {
    sprite->moveTo(x, y);

}
