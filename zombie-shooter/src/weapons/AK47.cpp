//
// Created by Souhaib El Habti on 12/01/2020.
//

#include "AK47.h"
#include "../resources/spritedata.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

AK47::AK47(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin) {
    setBuilder(builder, x, y);
    magazine = 30;
    bullets = bulletsBegin;
    damage = 3;
    chanceOfHeadshot = 4; // op 10
}

void AK47::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_64_32)
            .withLocation(x, y)
            .withData(akTiles, sizeof(akTiles))
            .buildPtr();
}
