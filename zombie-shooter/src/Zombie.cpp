//
// Created by Souhaib El Habti on 27/12/2019.
//

#include "Zombie.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "resources/spritedata.h"

Zombie::Zombie(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy, int lifePoints) {
    life = lifePoints;
    if(life <= 6){
        setSprite(builder, x, y, 0);
    }
    else{
        setSprite(builder, x, y, 1);
    }
    setVelocity(dx, dy);
}

Zombie::Zombie(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy, int lifePoints, int spriteID) {
    life = lifePoints;
    setSprite(builder, x, y, spriteID);
    setVelocity(dx, dy);
}

std::vector<Sprite *> Zombie::sprites() {
    return {
            sprite.get()
    };
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

void Zombie::setSprite(SpriteBuilder<Sprite> builder, int x, int y, int spriteID) {
    switch(spriteID) {
        case 0 :
            sprite = builder
                    .withSize(SIZE_16_32)
                    .withLocation(x, y)
                    .withData(zombieTiles, sizeof(zombieTiles))
                    .buildPtr();
            break;
        case 1 :
            sprite = builder
                    .withSize(SIZE_16_32)
                    .withLocation(x, y)
                    .withData(zombie2Tiles, sizeof(zombie2Tiles))
                    .buildPtr();
            break;
        case 2 :
            sprite = builder
                    .withSize(SIZE_32_16)
                    .withAnimated(2, 10)
                    .withLocation(x, y)
                    .withData(flyingzombieTiles, sizeof(flyingzombieTiles))
                    .buildPtr();
            break;
    }
}