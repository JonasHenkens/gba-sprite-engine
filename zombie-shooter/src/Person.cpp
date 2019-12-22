//
// Created by Souhaib El Habti on 22/12/2019.
//

#include "Person.h"

bool Person::getStillAlive() {
    return stillAlive;
}

void Person::die() {
    //if hit by zombie => stillAlive = false;
}

Weapon Person::getGun() {
    return gun;
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