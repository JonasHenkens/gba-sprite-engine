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
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y) override;
public:

    Pistol(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin);
    Pistol()= default;

};

#endif //GIT_PISTOL_H
