//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_PERSON_H
#define GIT_PERSON_H


#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Weapon.h"
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <vector>

class Person {
private:
    Weapon gun;
public:
    std::unique_ptr<Sprite> sprite;
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
    std::vector<Sprite *> sprites();

    void shoot();
    void reload();
    Weapon getGun();
    void setGun(Weapon gun);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void move (bool up, bool down, bool left, bool right);
};


#endif //GIT_PERSON_H
