//
// Created by Souhaib El Habti on 12/01/2020.
//

#include "Pistol.h"
#include "../resources/spritedata.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

Pistol::Pistol(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin) {
    setBuilder(builder, x, y);
    magazine = 6;
    bullets = bulletsBegin;
    damage = 6;
    chanceOfHeadshot = 2; // op 10
}

void Pistol::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_8_8)
            .withLocation(x, y)
            .withData(pistolTiles, sizeof(pistolTiles))
            .buildPtr();
}




