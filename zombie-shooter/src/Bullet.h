//
// Created by Souhaib El Habti on 11/01/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BULLET_H
#define GBA_SPRITE_ENGINE_PROJECT_BULLET_H

#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <vector>

class Bullet {
public:
    std::unique_ptr<Sprite> sprite;
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
    std::vector<Sprite *> sprites();

    Bullet(SpriteBuilder<Sprite> builder, int x, int y) {setBuilder(builder, x, y);};
    Bullet(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy);

    void setVelocity(int dx, int dy);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_BULLET_H
