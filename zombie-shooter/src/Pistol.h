//
// Created by Souhaib El Habti on 22/12/2019.
//

#ifndef GIT_PISTOL_H
#define GIT_PISTOL_H

#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Weapon.h"
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <vector>

class Pistol: public Weapon {
private:
    int magazine = 6;
    int bullets;
    int damage = 10;
    int chanceOfHeadshot = 0.20;

    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
public:
    std::unique_ptr<Sprite> sprite;
    std::vector<Sprite *> sprites();

    //Pistol(SpriteBuilder<Sprite> builder, int x, int y) {setBuilder(builder, x, y);};
    Pistol(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin);
    Pistol()= default;;

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void move (bool up, bool down, bool left, bool right);

};

#endif //GIT_PISTOL_H
