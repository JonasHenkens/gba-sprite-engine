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
private:
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
public:
    bool deleted = false;
    std::unique_ptr<Sprite> sprite;
    std::vector<Sprite *> sprites();

    Bullet(SpriteBuilder<Sprite> builder, int x, int y) {setBuilder(builder, x, y);};
    Bullet(SpriteBuilder<Sprite> builder, int x, int y, int dx);

    void setVelocity(int dx);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_BULLET_H
