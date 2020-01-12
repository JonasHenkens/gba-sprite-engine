//
// Created by Wouter Groeneveld on 08/08/18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "GameScreen.h"
#include "pats.h"
#include "dead.h"
#include "spritedata.h"
#include "Person.h"
#include "DeathScreen.h"
#include "Bullet.h"

std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites = {
            //paddle.get()
    };
    for (int i = 0; i < person.sprites().size(); ++i) {
        sprites.push_back(person.sprites()[i]);
    }
    for (int j = 0; j < zombies.size(); ++j) {
        for (int i = 0; i < zombies[j]->sprites().size(); ++i) {
            sprites.push_back(zombies[j]->sprites()[i]);
        }
    }

    for (int k = 0; k < bullets.size(); ++k) {
        for (int i = 0; i < bullets[k]->sprites().size(); ++i) {
            sprites.push_back(bullets[k]->sprites()[i]);
        }
    }
    return sprites;
}

std::vector<Background *> GameScreen::backgrounds() {
    return {};
}

void GameScreen::youDied() {
    if(highscore < score) highscore = score;
    engine->setScene(new DeathScreen(engine, this, score, highscore));
}

void GameScreen::resetGame() {
    score = 0;
    zombies = {};
    bullets = {};
    TextStream::instance().clear();

    SpriteBuilder<Sprite> builder;
    person.setBuilder(builder, 0, 128);
    person.move(false, false, false, false);
    zombies.push_back(std::shared_ptr<Zombie>(new Zombie(builder, GBA_SCREEN_WIDTH, 128, -1, 0, 3)));
}

void GameScreen::tick(u16 keys) {
    textOnScreen();

    if(keys & KEY_LEFT) {
        moveLeft = true;
    }
    if(keys & KEY_RIGHT) {
        moveRight = true;
    }
    if(keys & KEY_UP && canPersonJump()) {
        jumpTimer = 16;
    }
    else if(keys & KEY_START && canPersonJump()){
        SpriteBuilder<Sprite> builder;
        bullets.push_back(std::shared_ptr<Bullet>(new Bullet(builder, person.getX()+person.getWidth()/2, 110,  2)));
    }

    if (jumpTimer > 0) {
        moveUp = true;
        jumpTimer--;
    } else {
        moveDown = true;
    }

    checkBounds();
    movePerson();
    checkDead();

    score++;
}

void GameScreen::load() {
    engine.get()->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritedataSharedPal, sizeof(spritedataSharedPal)));

    resetGame();
}

bool GameScreen::canPersonJump() {
    if (person.getY() == 128) {
        return true;
    } else return false;
}

void GameScreen::checkBounds() {
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
}

void GameScreen::movePerson() {
    person.move(moveUp, moveDown, moveLeft, moveRight);
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
}

void GameScreen::textOnScreen() {
    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 7, 10);
    TextStream::instance().setText(std::string("Score: ") + std::to_string(score), 13, 10);
    TextStream::instance().setText(std::string("X: ") + std::to_string(person.getX()), 9, 10);
    TextStream::instance().setText(std::string("Life Zombie: ") + std::to_string(zombies[0].get()->getLife()), 11, 10);
}

void GameScreen::checkDead() {
    for (int i = 0; i < zombies.size(); ++i) {
        if (person.sprite->collidesWith(*zombies[i]->sprite)){
            youDied();
        }
        if (zombies[i]->getX() < 0 - zombies[i]->getWidth()){
            zombies[i]->setSpeedMultiplier(0);
        }
    }
}