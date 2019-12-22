//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_PERSON_H
#define GIT_PERSON_H


#include "Weapon.h"

class Person {
private:
    bool stillAlive;
    Weapon gun;
public:
    bool getStillAlive();
    void die(); /* maak speler dood als zombie hem raakt
                   of te zetten in getStillAlive als controle */
    void shoot();
    void reload();
    Weapon getGun();
};


#endif //GIT_PERSON_H
