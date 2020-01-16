//
// Created by Wouter Groeneveld on 29/11/18.
//

#ifndef ZOMBIESHOOTER_STARTSCREEN_H
#define ZOMBIESHOOTER_STARTSCREEN_H


#include <libgba-sprite-engine/scene.h>
#include "GameScreen.h"

class DeathScreen : public Scene {
private:
    std::unique_ptr<Background> bg;
    int score;
    int highscore;

public:
    DeathScreen(const std::shared_ptr<GBAEngine> &engine, int score, int highscore);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //ZOMBIESHOOTER_STARTSCREEN_H
