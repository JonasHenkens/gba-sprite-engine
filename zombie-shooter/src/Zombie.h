//
// Created by Souhaib El Habti on 27/12/2019.
//

#ifndef GIT_ZOMBIE_H
#define GIT_ZOMBIE_H

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "../../../../Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/vector"

class Zombie {
private:
    bool headshot;
    int life;
    int speedMultiplier = 1;
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
public:
    std::unique_ptr<Sprite> sprite;
    Zombie(SpriteBuilder<Sprite> builder, int x, int y) {setBuilder(builder, x, y);};
    Zombie(SpriteBuilder<Sprite> builder, int x, int y, int dx, int dy);
    bool isDead();
    bool isHeadshot();
    int getLife();
    void hit();

    std::vector<Sprite *> sprites();

    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void setVelocity(int dx, int dy);

    int getDx();

    int getDy();

    int getSpeedMultiplier();

    void setSpeedMultiplier(int speedMultiplier);
};


#endif //GIT_ZOMBIE_H
