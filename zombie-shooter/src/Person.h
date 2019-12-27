//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_PERSON_H
#define GIT_PERSON_H


#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Weapon.h"

class Person {
private:
    int xCoord;
    int yCoord;
    bool stillAlive;
    Weapon gun;
public:
    bool getStillAlive();
    void die(); /* maak speler dood als zombie hem raakt
                   of te zetten in getStillAlive als controle */
    void shoot();
    void reload();
    Weapon getGun();

    int getX();
    int getY();
    void move(u16 keys);
};


#endif //GIT_PERSON_H
