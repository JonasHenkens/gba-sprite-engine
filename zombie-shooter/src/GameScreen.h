//
// Created by Wouter Groeneveld on 08/08/18.
//

#ifndef ZOMBIESHOOTER_GAMESCREEN_H
#define ZOMBIESHOOTER_GAMESCREEN_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <vector>

class GameScreen : public Scene {
private:
    bool dead;
    int ticks, highscore;

    std::unique_ptr<Sprite> paddle;
    std::unique_ptr<Sprite> zombie;

    void youDied();
    void resetGame();
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
    int jumpTimer = 0;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    GameScreen(std::shared_ptr<GBAEngine> engine) : Scene(engine), ticks(0), highscore(0) {}

    void load() override;
    void tick(u16 keys) override;

    bool canPlayerJump();

};


#endif //ZOMBIESHOOTER_GAMESCREEN_H
