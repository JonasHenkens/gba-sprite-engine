//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_WEAPON_H
#define GIT_WEAPON_H

class Weapon {
protected:
    int magazine; // max amount of bullets
    int bullets; // aantal kogels in weapon
    int damage; // Damage of weapon
    int chanceOfHeadshot; // Random headshot kills
public:
    virtual int getDamage();
    virtual int getMagazine();
    virtual int getBullets();
    virtual int getHeadshotChance();
    void reload(int ammo);
    void shoot();
};

#endif //GIT_WEAPON_H
