//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_WEAPON_H
#define GIT_WEAPON_H


class Weapon {
private:
    int magazine; // max aantal kogels
    int bullets; // aantal kogels
    int damage;
public:
    int getDamage();
    int getMagazine();
    int getBullets();
    void reload(int ammo);
    void shoot();
};

#endif //GIT_WEAPON_H
