//
// Created by Wouter Groeneveld on 29/11/18.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "DeathScreen.h"
#include "GameScreen.h"

#include "DeathScreenImage.h"

DeathScreen::DeathScreen(const std::shared_ptr<GBAEngine> &engine, GameScreen *gameScreen, int score, int highscore) : Scene(engine), gameScreen(gameScreen), score(score), highscore(highscore) {}

std::vector<Sprite *> DeathScreen::sprites() {
    return {};
}

std::vector<Background *> DeathScreen::backgrounds() {
    return {
        bg.get()
    };
}

void DeathScreen::tick(u16 keys) {
    if(keys & KEY_START) {
        engine->setScene(new GameScreen(engine, highscore));
    }
}

void DeathScreen::load() {
    engine.get()->enableText();

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(deathscreenimagePal, sizeof(deathscreenimagePal)));
    bg = std::unique_ptr<Background>(new Background(1, deathscreenimageTiles, sizeof(deathscreenimageTiles), deathscreenimageMap, sizeof(deathscreenimageMap)));
    bg.get()->useMapScreenBlock(16);

    TextStream::instance().setText(std::string("You died!"), 5, 3);
    TextStream::instance().setText(std::string("HIGHSCORE: ") + std::to_string(highscore), 7, 3);;
    TextStream::instance().setText(std::string("SCORE: ") + std::to_string(score), 9, 3);;
    TextStream::instance().setText(std::string("Press START to try again"), 11, 3);;

}
