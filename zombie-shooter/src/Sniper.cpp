//
// Created by Souhaib El Habti on 12/01/2020.
//

#include "Sniper.h"
#include "spritedata.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

Sniper::Sniper(SpriteBuilder<Sprite> builder, int x, int y, int bulletsBegin) {
    setBuilder(builder, x, y);
    magazine = 1;
    bullets = bulletsBegin;
    damage = 25;
    chanceOfHeadshot = 8; // op 10
}

void Sniper::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_8_8)
            .withLocation(x, y)
            .withData(pistolTiles, sizeof(pistolTiles))
            .buildPtr();
    // CHANGE TO SNIPER
}

void Sniper::shoot() {
    bullets--;
}