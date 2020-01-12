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