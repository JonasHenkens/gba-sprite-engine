//
// Created by Souhaib El Habti on 12/01/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_AK47_H
#define GBA_SPRITE_ENGINE_PROJECT_AK47_H

#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Weapon.h"
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <vector>

class AK47 : public Weapon {
private:
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y) override;
public:
    AK47(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_AK47_H
