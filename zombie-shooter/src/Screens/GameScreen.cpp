//
// Created by Wouter Groeneveld on 08/08/18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <cmath>

#include "GameScreen.h"
#include "../resources/spritedata.h"
#include "../Person.h"
#include "DeathScreen.h"
#include "../resources/gameBackgroundImage.h"
#include "../resources/gunshot.h"

std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites = {};

    for (int h = 0; h < weapon->sprites().size(); ++h) {
        sprites.push_back(weapon->sprites()[h]);
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
    return {
        bg.get()
    };
}

void GameScreen::load() {
    engine->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritedataSharedPal, sizeof(spritedataSharedPal)));

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gameBackgroundPal, sizeof(gameBackgroundPal)));
    bg = std::unique_ptr<Background>(new Background(1, gameBackgroundTiles, sizeof(gameBackgroundTiles), gameBackgroundMap, sizeof(gameBackgroundMap)));
    bg->useMapScreenBlock(16);

    showGameText();

    person.setBuilder(builder, 0, 128);
    person.move(false, false, false, false);
    weapon = std::shared_ptr<Weapon>(new Pistol(builder,person.getWidth(),138, 0));
    person.setGun(weapon);
}

void GameScreen::died() {
    if(highscore < score) highscore = score;
    engine->setScene(new DeathScreen(engine, score, highscore));
}

void GameScreen::tick(u16 keys) {
    if(isShopOpened){
        tickShop(keys);
        clicked_A = keys & KEY_A;
        clicked_B = keys & KEY_B;
        clicked_START = keys & KEY_START;
        engine->updateSpritesInScene();
        return;
    }

    updateGameText();
    tickSpawnLogic();

    moveLeft = keys & KEY_LEFT;
    moveRight = keys & KEY_RIGHT;
    if(keys & KEY_A && canPersonJump()){
        person.reload(&ammountBullet);
    }
    else if(keys & KEY_UP && canPersonJump()) {
        jumpTimer = 16;
    }
    if(keys & KEY_B) {
        shoot();
    }
    if(openShopNow) {
        openShop();
        openShopNow = false;
        return;
    }
    clicked_START = keys & KEY_START;

    if (jumpTimer > 0) {
        moveUp = true;
        jumpTimer--;
    }
    else {
        moveDown = true;
    }

    shootTimer++;
    checkBounds();
    move();
    checkCollisions();
    removeExcessSprites();

    if (updateSprites) {
        engine->updateSpritesInScene();
        updateSprites = false;
    }
}


bool GameScreen::canPersonJump() {
    return person.getY() == 128;
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
    weapon->move(moveUp, moveDown, moveLeft, moveRight);
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
}

void GameScreen::showGameText() {;
    TextStream::instance().setText(std::string("Highscore: "), 5, 5);
    TextStream::instance().setText(std::string("Score: "), 7, 5);
    TextStream::instance().setText(std::string("Points: "), 9, 5);
    TextStream::instance().setText(std::string("Bullets/Ammo: "), 11, 5);
}

void GameScreen::updateGameText() {
    if(ammountBullet == 0) TextStream::instance().setText(std::string("NO AMMUNITION !!!"), 1, 5);
    else if(person.getGun()->getBullets() == 0)TextStream::instance().setText(std::string("RELOAD!!!"), 1, 5);
    else TextStream::instance().setText("", 1, 5);

    TextStream::instance().setFontColor(0);
    TextStream::instance().setText("Wave: " + std::to_string(level), 3, 5);
    TextStream::instance().setText(std::to_string(highscore), 5, 16);
    TextStream::instance().setText(std::to_string(score), 7, 12);
    TextStream::instance().setText(std::to_string(points), 9, 13);
    TextStream::instance().setText(std::to_string(person.getGun()->getBullets()) + "/" + std::to_string(ammountBullet), 11, 19);
}

void GameScreen::showShopText() {
    TextStream::instance().setText(std::string("Click A for AMMO                (2-25 BULLETS)  [-3p]"), 9, 1);
    TextStream::instance().setText(std::string("Click B for NEW WEAPON          (PISTOL/AK-47/SNIPER) [-15p]"), 11, 1);
    TextStream::instance().setText(std::string("Click START to return"), 13, 1);
}

void GameScreen::tickShop(u16 keys) {
    int totalBullets = person.getGun()->getBullets() + ammountBullet;
    TextStream::instance().setText(std::string("Points: ") + std::to_string(points), 6, 1);
    TextStream::instance().setText(std::string("Total Ammo: ") + std::to_string(totalBullets), 7, 1);

    if(keys & KEY_A && !clicked_A) {
        if(points >= 3){
            int extraBullets = rand() % 24 + 2;
            ammountBullet = ammountBullet + extraBullets;
            points = points - 3;
        }
    }
    if(keys & KEY_B && !clicked_B) {
        if(points >= 15){
            int chanceWeapon = rand() % 10 + 1;
            if(chanceWeapon < 5){
                ammountBullet = 24;
                weapon = std::shared_ptr<Weapon>(new Pistol(builder,person.getX() + person.getWidth(),person.getY()+10, 6));
                person.setGun(weapon);
                shootFast = false;
            }
            else if(chanceWeapon < 9){
                ammountBullet = 60;
                weapon = std::shared_ptr<Weapon>( new AK47(builder,person.getX() + person.getWidth()/2,person.getY() + 9, 30));
                person.setGun(weapon);
                shootFast = true;
            }
            else{
                ammountBullet = 15;
                weapon = std::shared_ptr<Weapon>(new Sniper(builder,person.getX(),person.getY()+1, 1));
                person.setGun(weapon);
                shootFast = false;
            }
            points = points - 15;
        }
    }
    if(keys & KEY_START && !clicked_START) {
        quitShop();
    }
}

void GameScreen::quitShop() {
    isShopOpened = false;
    TextStream::instance().clear();
    showGameText();

    for (int i = 0; i < zombies.size(); ++i) {
        zombies[i]->setVelocity(-1, 0);
    }
    for (int i = 0; i < bulletSprites.size(); ++i) {
        bulletSprites[i]->setVelocity(bulletSpeed, 0);
    }
}

void GameScreen::openShop() {
    isShopOpened = true;
    TextStream::instance().clear();
    showShopText();

    for (auto & zombie : zombies) {
        zombie->setVelocity(0, 0);
    }
    for (auto & bulletSprite : bulletSprites) {
        bulletSprite->setVelocity(0, 0);
    }

    person.sprite->setVelocity(0, 0);
    weapon->sprite->setVelocity(0, 0);
}

void GameScreen::checkCollisions() {
    for (int i = 0; i < zombies.size(); ++i) {
        if (zombies[i]->deleted) {
            continue;
        }
        if (person.sprite->collidesWith(*zombies[i]->sprite)){
            died();
            break;
        }
        if (zombies[i]->getX() < 0 - zombies[i]->getWidth()){
            zombiesToRemove.push_back(i);
            continue;
        }
        for (int j = 0; j < bulletSprites.size(); ++j) {
            if (zombies[i]->sprite->collidesWith(*bulletSprites[j])){
                int damageGun = person.getGun()->getDamage();
                int chanceHeadshot = person.getGun()->getHeadshotChance();
                int chance = rand() % 10 + 1;
                bool headshot = chance <= chanceHeadshot;

                zombies[i]->hit(damageGun, headshot);
                if (zombies[i]->getLife() <= 0) {
                    zombiesToRemove.push_back(i);
                    score++;
                    points++;
                }
                bulletSprites[j]->moveTo(260, 180);
                break;
            }
        }
    }
}

void GameScreen::shoot() {
    if (shootTimer < 25 && !shootFast) return;
    else if (shootTimer < 7 && shootFast) return;
    else shootTimer = 0;

    if (person.shoot()) {
        int xGun = person.getGun()->getX();
        int space = person.getGun()->getWidth()/2;
        bulletSprites.push_back(builder
                                        .withSize(SIZE_8_8)
                                        .withLocation(xGun + space, person.getGun()->getY()+1)
                                        .withData(bulletTiles, sizeof(bulletTiles))
                                        .withVelocity(bulletSpeed, 0)
                                        .buildPtr());
        updateSprites = true;

        engine->enqueueSound(gunshot, gunshot_bytes, 44100);
    }
}

void GameScreen::removeExcessSprites() {
    // kan niet alle frames verwijderen
    // want om een of andere reden blijven de sprites zichtbaar ookal bestaan ze niet meer
    for (int i = zombiesDeleteQueue.size() - 1; i >= 0; --i) {
        zombies.erase(zombies.begin() + zombiesDeleteQueue[i]);
    }
    zombiesDeleteQueue.clear();

    for (int i = 0; i < zombiesToRemove.size(); ++i) {
        zombies[zombiesToRemove[i]]->sprite->moveTo(300, 300);
        zombies[zombiesToRemove[i]]->deleted = true;
        zombiesDeleteQueue.push_back(zombiesToRemove[i]);
    }
    zombiesToRemove.clear();

    for (int i = bulletSprites.size()-1; i >= 0 ; --i) {
        if (bulletSprites[i]->isOffScreen() && bulletSprites[i]->getDy() == 0 && bulletSprites[i]->getDx() == 0) {
            bulletSprites.erase(bulletSprites.begin() + i);
        }
        if (bulletSprites[i]->isOffScreen()) {
            bulletSprites[i]->setVelocity(0, 0);
        }
    }

    updateSprites = true;
}

void GameScreen::tickSpawnLogic() {
    if (spawnedZombies >= level*5) {
        if (zombies.empty()) {
            openShopNow = true;
            level++;
            spawnedZombies = 0;
        }
        return;
    }
    if (spawnDelayCounter <= 0) {
        int life = rand() % (level*2) + level;
        double speed = -pow(level, 0.45);

        if (spawnedZombies%5 == 0) {
            zombies.push_back(std::shared_ptr<Zombie>(new Zombie(builder, GBA_SCREEN_WIDTH, 113, speed, 0, life, 2)));
        } else {
            zombies.push_back(std::shared_ptr<Zombie>(new Zombie(builder, GBA_SCREEN_WIDTH, 128, speed, 0, life)));
        }
        spawnedZombies++;
        spawnDelayCounter = (int)(45.0-8*pow(level, 0.65));
        if (spawnDelayCounter < 10 ||spawnDelayCounter >= 60) spawnDelayCounter = 10;
    }

    spawnDelayCounter--;
}
