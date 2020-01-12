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

    for (int h = 0; h < pistol.sprites().size(); ++h) {
        sprites.push_back(pistol.sprites()[h]);
    }

    for (int i = 0; i < person.sprites().size(); ++i) {
        sprites.push_back(person.sprites()[i]);
    }

    for (int j = 0; j < zombies.size(); ++j) {
        for (int i = 0; i < zombies[j]->sprites().size(); ++i) {
            sprites.push_back(zombies[j]->sprites()[i]);
        }
    }

    for (int i = 0; i < bulletSprites.size(); ++i) {
        sprites.push_back(bulletSprites[i].get());
    }

    return sprites;
}

std::vector<Background *> GameScreen::backgrounds() {
    return {};
}

void GameScreen::youDied() {
    if(highscore < score) highscore = score;
    engine->setScene(new DeathScreen(engine, score, highscore));
}

void GameScreen::resetGame() {
    score = 0;
    ammountBullet = 30;
    noAmmo = false;
    zombies = {};
    TextStream::instance().clear();

    person.setBuilder(builder, 0, 128);
    person.move(false, false, false, false);
    pistol = Pistol(builder,person.getWidth(),138, 0);
    person.setGun(&pistol);
    zombies.push_back(std::shared_ptr<Zombie>(new Zombie(builder, GBA_SCREEN_WIDTH, 128, -1, 0, 3)));
    bulletSprites.clear();
}

void GameScreen::tick(u16 keys) {
    textOnScreen();
    if (zombies.size() < 2) {
        spawnZombie();
    }

    if(keys & KEY_LEFT) {
        moveLeft = true;
    }
    if(keys & KEY_RIGHT) {
        moveRight = true;
    }
    if(keys & KEY_A && canPersonJump()){
        noAmmo = person.reload(&ammountBullet);
    }
    else if(keys & KEY_UP && canPersonJump()) {
        jumpTimer = 16;
    }
    if(keys & KEY_B) {
        shoot();
    }

    if (jumpTimer > 0) {
        moveUp = true;
        jumpTimer--;
    } else {
        moveDown = true;
    }
    shootTimer++;

    checkBounds();
    move();
    checkCollisions();
    removeExcessSprites();

    engine->updateSpritesInScene();
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

void GameScreen::move() {
    person.move(moveUp, moveDown, moveLeft, moveRight);
    pistol.move(moveUp, moveDown, moveLeft, moveRight);
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
}

void GameScreen::textOnScreen() {
    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 7, 10);
    TextStream::instance().setText(std::string("zombies: ") + std::to_string(zombies.size()), 15, 10);
    TextStream::instance().setText(std::string("Score: ") + std::to_string(score), 13, 10);
    TextStream::instance().setText(std::string("Ammo: ") + std::to_string(ammountBullet), 9, 10);
    TextStream::instance().setText(std::string("Bullets gun: ") + std::to_string(person.getGun()->getBullets()), 11, 10);
    if(noAmmo){
        TextStream::instance().setText(std::string("NO AMMUNITION !!!"), 5, 10);
    }
    TextStream::instance().setText(std::string("Magazine: ") + std::to_string(person.getGun()->getMagazine()), 3, 10);
}

void GameScreen::checkCollisions() {
    for (int i = 0; i < zombies.size(); ++i) {
        if (zombies[i]->deleted) {
            break;
        }
        if (person.sprite->collidesWith(*zombies[i]->sprite)){
            youDied();
            break;
        }
        if (zombies[i]->getX() < 0 - zombies[i]->getWidth()){
            zombiesToRemove.push_back(i);
            continue;
        }
        for (int j = 0; j < bulletSprites.size(); ++j) {
            if (bulletSprites[i]->isOffScreen()) {
                break;
            }

            if (zombies[i]->sprite->collidesWith(*bulletSprites[j])){
                zombiesToRemove.push_back(i);
                bulletsToRemove.push_back(j);
                score++;
                break;
            }
        }
    }

}

void GameScreen::shoot() {

    if (shootTimer < 30) {
        return;
    } else {
        shootTimer = 0;
    }

    if (person.shoot()) {
        bulletSprites.push_back(builder
                                        .withSize(SIZE_8_8)
                                        .withLocation(person.getGun()->getX(), person.getGun()->getY())
                                        .withData(bulletTiles, sizeof(bulletTiles))
                                        .withVelocity(2, 0)
                                        .buildPtr());
        engine->updateSpritesInScene();
    }

}

void GameScreen::removeExcessSprites() {
    // kan niet in 1 frame verwijderen
    // want om een of andere reden blijven de sprites zichtbaar ookal bestaan ze niet meer
    for (int i = zombiesDeleteQueue.size() - 1; i >= 0; --i) {
        zombies.erase(zombies.begin() + zombiesDeleteQueue[i]);
    }
    for (int i = bulletSprites.size()-1; i >= 0; --i) {
        if (bulletSprites[i]->isOffScreen()) {
            bulletSprites.erase(bulletSprites.begin() + i);
        }
    }
    bulletsDeleteQueue.clear();
    zombiesDeleteQueue.clear();

    for (int i = 0; i < zombiesToRemove.size(); ++i) {
        zombies[zombiesToRemove[i]]->sprite->moveTo(300, 300);
        zombies[zombiesToRemove[i]]->deleted = true;
        zombiesDeleteQueue.push_back(zombiesToRemove[i]);
    }
    for (int i = 0; i < bulletsToRemove.size(); ++i) {
        bulletSprites[bulletsToRemove[i]]->moveTo(300, 300);
        bulletsDeleteQueue.push_back(bulletsToRemove[i]);
    }
    bulletsToRemove.clear();
    zombiesToRemove.clear();

    engine->updateSpritesInScene();
}

void GameScreen::spawnZombie() {
    zombies.push_back(std::shared_ptr<Zombie>(new Zombie(builder, GBA_SCREEN_WIDTH, 128, -1, 0, 3)));

}

