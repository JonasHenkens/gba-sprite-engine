//
// Created by Wouter Groeneveld on 08/08/18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "GameScreen.h"
#include "spritedataOld.h"
#include "pats.h"
#include "dead.h"
#include "spritedata.h"

std::vector<Sprite *> GameScreen::sprites() {
    return {
            paddle.get(), zombie.get()
    };
}

std::vector<Background *> GameScreen::backgrounds() {
    return {};
}

void GameScreen::youDied() {
    if(highscore < ticks) highscore = ticks;
    engine.get()->enqueueSound(raw_dead, raw_dead_bytes, 32000);
    zombie->setVelocity(0, 0);
    TextStream::instance() << "You DIED - start to reset";
    dead = true;
}

void GameScreen::resetGame() {
    dead = false;
    ticks = 0;

    TextStream::instance().clear();
    zombie->moveTo(110, 140);
    zombie->setVelocity(1, 1);
    paddle->moveTo(100, 150);
}

void GameScreen::tick(u16 keys) {
    if(dead && (keys & KEY_START)) {
        resetGame();
        return;
    }

    if(dead) return;

    TextStream::instance().setText(std::string("Ticks: ") + std::to_string(ticks), 5, 10);
    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 7, 10);
    TextStream::instance().setText(std::string("x: ") + std::to_string(zombie->getX()), 9, 10);
    TextStream::instance().setText(std::string("y: ") + std::to_string(zombie->getY()), 11, 10);
/*
    if(zombie->getX() <= 0 || zombie->getX() >= (GBA_SCREEN_WIDTH - zombie->getWidth())) {
        zombie->setVelocity(-zombie->getDx(), zombie->getDy());
    }else if(zombie->getY() <= 0) {
        zombie->setVelocity(zombie->getDx(), -zombie->getDy());
    } else if(zombie->getY() >= (GBA_SCREEN_HEIGHT - zombie->getHeight())) {
       youDied();
       return;
    } else if(zombie->collidesWith(*paddle)) {
        if(ticks > 1 && ticks % 5 == 0) {
            zombie->setVelocity(zombie->getDx() + 1, zombie->getDy() + 1);
        }

        // lousy implementation; zombie could also hit paddle from right/left, meaning *BOOM*
        zombie->setVelocity(zombie->getDx(), -zombie->getDy());
        engine.get()->enqueueSound(pats, sizeof(pats), 32000);

        ticks++;
    }*/
    if(keys & KEY_LEFT) {
        moveLeft = true;
    }
    if(keys & KEY_RIGHT) {
        moveRight = true;
    }
    if(keys & KEY_UP && canPlayerJump()) {
        jumpTimer = 16;
    }
    if(keys & KEY_DOWN) {
        //moveDown = true;
    }

    if (jumpTimer > 0) {
        moveUp = true;
        jumpTimer--;
    } else {
        moveDown = true;
    }

    // bounds check
    if(zombie->getX() <= 0) {
        moveLeft = false;
    }
    if(zombie->getX() >= (GBA_SCREEN_WIDTH - zombie->getWidth() - 0)) {
        moveRight = false;
    }
    if(zombie->getY() <= 0) {
        moveUp = false;
    }
    if(zombie->getY() >= (GBA_SCREEN_HEIGHT - zombie->getHeight() - 0)) {
        moveDown = false;
    }

    // move player
    if (moveLeft == moveRight) {
        zombie->setVelocity(0, zombie->getDy());
    }
    else if (moveRight) {
        zombie->setVelocity(+2, zombie->getDy());
    }
    else if (moveLeft) {
        zombie->setVelocity(-2, zombie->getDy());
    }
    if (moveUp == moveDown) {
        zombie->setVelocity(zombie->getDx(), 0);
    }
    else if (moveUp) {
        zombie->setVelocity(zombie->getDx(), -2);
    }
    else if (moveDown) {
        zombie->setVelocity(zombie->getDx(), +2);
    }
    moveUp = false;
    moveRight = false;
    moveLeft = false;
    moveDown = false;

}

void GameScreen::load() {
    engine.get()->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritedataSharedPal, sizeof(spritedataSharedPal)));

    SpriteBuilder<Sprite> builder;

    zombie = builder
            .withSize(SIZE_16_32)
            .withLocation(0, 128)
            .withData(zombieheadTiles, sizeof(zombieheadTiles))
            .buildPtr();

    paddle = builder
            .withSize(SIZE_16_32)
            .withLocation(100, 150)
            .withData(zombiehead2Tiles, sizeof(zombiehead2Tiles))
            .withinBounds()
            .buildPtr();
}

bool GameScreen::canPlayerJump() {
    if (zombie->getY() == 128) {
        return true;
    } else return false;
}