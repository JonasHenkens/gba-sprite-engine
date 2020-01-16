//
// Created by Wouter Groeneveld on 08/08/18.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Screens/StartScreen.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    auto scene = new StartScreen(engine);
    engine->setScene(scene);

    while (true) {
        engine->update();
    }

    return 0;
}