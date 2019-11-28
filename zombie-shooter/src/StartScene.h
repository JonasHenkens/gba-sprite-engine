//
// Created by henke on 28/11/2019.
//

#ifndef ZOMBIESHOOTER_STARTSCREEN_H
#define ZOMBIESHOOTER_STARTSCREEN_H


#include <libgba-sprite-engine/scene.h>

class StartScene : public Scene {
private:
    std::unique_ptr<Background> bg;

public:
    StartScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};


#endif //ZOMBIESHOOTER_STARTSCREEN_H
