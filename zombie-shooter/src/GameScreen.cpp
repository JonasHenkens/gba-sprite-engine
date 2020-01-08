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
#include "Person.h"

std::vector<Sprite *> GameScreen::sprites() {
    return {
            paddle.get(), person.sprite.get()
    };
}

std::vector<Background *> GameScreen::backgrounds() {
    return {};
}

void GameScreen::youDied() {
    if(highscore < ticks) highscore = ticks;
    engine.get()->enqueueSound(raw_dead, raw_dead_bytes, 32000);
    //zombie->setVelocity(0, 0);
    TextStream::instance() << "You DIED - start to reset";
    dead = true;
}

void GameScreen::resetGame() {
    dead = false;
    ticks = 0;

    TextStream::instance().clear();
    //zombie->moveTo(110, 140);
    //zombie->setVelocity(1, 1);
    //paddle->moveTo(100, 150);
}

void GameScreen::tick(u16 keys) {
    if(dead && (keys & KEY_START)) {
        resetGame();
        return;
    }

    if(dead) return;

    TextStream::instance().setText(std::string("Ticks: ") + std::to_string(ticks), 5, 10);
    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 7, 10);
    TextStream::instance().setText(std::string("x: ") + std::to_string(person.getX()), 9, 10);
    TextStream::instance().setText(std::string("y: ") + std::to_string(person.getY()), 11, 10);
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
    if(keys & KEY_UP && canPersonJump()) {
        jumpTimer = 16;
    }

    if (jumpTimer > 0) {
        moveUp = true;
        jumpTimer--;
    } else {
        moveDown = true;
    }

    // bounds check
    if(person.getX() <= 0) {
        moveLeft = false;
    }
    if(person.getX() >= (GBA_SCREEN_WIDTH - person.getWidth() - 0)) {
        moveRight = false;
    }
    if(person.getY() <= 0) {
        moveUp = false;
    }
    if(person.getY() >= (GBA_SCREEN_HEIGHT - person.getHeight() - 0)) {
        moveDown = false;
    }

    person.move(moveUp, moveDown, moveLeft, moveRight);
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;

}

void GameScreen::load() {
    engine.get()->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritedataSharedPal, sizeof(spritedataSharedPal)));

    SpriteBuilder<Sprite> builder;
/*
    zombie = builder
            .withSize(SIZE_16_32)
            .withLocation(0, 128)
            .withData(zombieheadTiles, sizeof(zombieheadTiles))
            .buildPtr();
*/
    paddle = builder
            .withSize(SIZE_16_32)
            .withLocation(100, 150)
            .withData(zombiehead2Tiles, sizeof(zombiehead2Tiles))
            .withinBounds()
            .buildPtr();
    person.setBuilder(builder);

}

bool GameScreen::canPersonJump() {
    if (person.getY() == 128) {
        return true;
    } else return false;
}
