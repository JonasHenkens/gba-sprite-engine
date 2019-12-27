//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_PISTOL_H
#define GIT_PISTOL_H

#include "Weapon.h"

class Pistol: public Weapon { // pistool erft van wapen
private:
    int magazine = 6; // max aantal kogels
    int bullets;
    int damage = 10;
    // Afbeelding???
};

#endif //GIT_PISTOL_H
