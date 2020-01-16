//
// Created by Souhaib El Habti on 27/12/2019.
//

#ifndef GIT_ZOMBIE_H
#define GIT_ZOMBIE_H

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "vector"

class Zombie {
private:
    int life;
    int speedMultiplier = 1;
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
    void setBuilder2(SpriteBuilder<Sprite> builder, int x, int y);
public:
    bool deleted = false;
    std::unique_ptr<Sprite> sprite;
    Zombie(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy, int life);
    bool isDead();
    int getLife();
    void hit(int damage, bool isHeadshot);

    std::vector<Sprite *> sprites();

    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void setVelocity(int dx, int dy);
};


#endif //GIT_ZOMBIE_H
