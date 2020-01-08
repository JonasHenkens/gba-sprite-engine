//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_PERSON_H
#define GIT_PERSON_H


#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Weapon.h"
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class Person {
private:
    bool stillAlive;
    Weapon gun;
public:
    std::unique_ptr<Sprite> sprite;
    void setBuilder(SpriteBuilder<Sprite> builder);
    bool getStillAlive();

    // in scene: ga over alle zombies en kijk of die colliden met person
    void die(); /* maak speler dood als zombie hem raakt
                   of te zetten in getStillAlive als controle */


    void shoot();
    void reload();
    Weapon getGun();
    void setGun(Weapon gun);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void move (bool up, bool down, bool left, bool right);

};


#endif //GIT_PERSON_H
