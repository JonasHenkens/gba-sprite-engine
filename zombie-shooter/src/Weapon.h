//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_WEAPON_H
#define GIT_WEAPON_H


class Weapon {
protected:
    int magazine; // max aantal kogels
    int bullets; // aantal kogels
    int damage;
    int chanceOfHeadshot; // Random headshot kills: makkelijker dan zelf mikken
public:
    virtual int getDamage();
    virtual int getMagazine();
    virtual int getBullets();
    virtual int getHeadshotChance();
    virtual void reload(int ammo);
    virtual void shoot();
};

#endif //GIT_WEAPON_H
