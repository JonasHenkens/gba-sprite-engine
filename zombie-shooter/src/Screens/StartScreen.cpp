//
// Created by Wouter Groeneveld on 29/11/18.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>

#include "StartScreen.h"
#include "GameScreen.h"

#include "../resources/startscreenimage.h"

StartScreen::StartScreen(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> StartScreen::sprites() {
    return {};
}

std::vector<Background *> StartScreen::backgrounds() {
    return {
        bg.get()
    };
}

void StartScreen::tick(u16 keys) {
    if(keys & KEY_ANY) {
        engine->setScene(new GameScreen(engine));
    }
}

void StartScreen::load() {
    engine->disableText();
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(startscreenimagePal, sizeof(startscreenimagePal)));
    bg = std::unique_ptr<Background>(new Background(0, startscreenimageTiles, sizeof(startscreenimageTiles), startscreenimageMap, sizeof(startscreenimageMap)));
    bg->useMapScreenBlock(24);
}
