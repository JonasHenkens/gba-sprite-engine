//
// Created by Souhaib El Habti on 27/12/2019.
//

#include "Zombie.h"

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