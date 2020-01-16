//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_WEAPON_H
#define GIT_WEAPON_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <vector>
#include "../Bullet.h"

class Weapon {
protected:
    int magazine; // max amount of bullets
    int bullets; // aantal kogels in weapon
    int damage; // Damage of weapon
    int chanceOfHeadshot; // Random headshot kills
    SpriteBuilder<Sprite> builder;

    virtual void setBuilder(SpriteBuilder<Sprite> builder, int x, int y) = 0;
public:
    std::unique_ptr<Sprite> sprite;
    std::vector<std::shared_ptr<Bullet>> activeBullets;
    std::vector<Sprite *> sprites();

    int getDamage();
    int getMagazine();
    int getBullets();
    int getHeadshotChance();
    void reload(int ammo);
    void move (bool up, bool down, bool left, bool right);
    void shoot();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};

#endif //GIT_WEAPON_H
