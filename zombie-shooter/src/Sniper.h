//
// Created by Souhaib El Habti on 12/01/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SNIPER_H
#define GBA_SPRITE_ENGINE_PROJECT_SNIPER_H

#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Weapon.h"
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <vector>

class Sniper: public Weapon {
private:
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
public:
    Sniper(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin);
    void shoot() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SNIPER_H
