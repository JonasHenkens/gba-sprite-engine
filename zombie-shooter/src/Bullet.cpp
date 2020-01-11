//
// Created by Souhaib El Habti on 11/01/2020.
//

#include "Bullet.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "spritedata.h"

Bullet::Bullet(SpriteBuilder<Sprite> builder, int x, int y, int dx) {
    setBuilder(builder, x, y);
    setVelocity(dx);
}

std::vector<Sprite *> Zombie::sprites() {
    return {
            sprite.get()
    };
}

// Moet aangepast worden naar kogelSprite
void Bullet::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    sprite = builder
            .withSize(SIZE_16_32)
            .withLocation(x, y)
            .withData(zombieTiles, sizeof(zombieTiles))
            .buildPtr();
}

void Bullet::setVelocity(int dx, int dy) {
    sprite->setVelocity(dx, dy);
}