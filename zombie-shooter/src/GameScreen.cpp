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
#include "gameBackgroundImage.h"

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

void GameScreen::youDied() {
    if(highscore < score) highscore = score;
    engine->setScene(new DeathScreen(engine, score, highscore));
}

void GameScreen::resetGame() {
    score = 0;
    points = 1000;
    zombieSpeedUp = 0;
    countZombies = 0;
    ammountBullet = 30;
    maxZombies = 2;
    zspeed = 1;
    zombies = {};
    bulletSprites.clear();
    TextStream::instance().clear();

    ammoDone = true;
    weaponEmpty = false;
    shootFast = false;
    shopAvialable = false;
    clicked_A = false;
    clicked_B = false;
    clicked_START = false;

    person.setBuilder(builder, 0, 128);
    person.move(false, false, false, false);
    weapon = std::shared_ptr<Weapon>(new Pistol(builder,person.getWidth(),138, 0));
    person.setGun(weapon);
}

void GameScreen::tick(u16 keys) {
    if(shopAvialable){
        shopOnScreen(keys);
        clicked_A = keys & KEY_A;
        clicked_B = keys & KEY_B;
        clicked_START = keys & KEY_START;
        return;
    }

    textOnScreen();

    if (zombies.size() < maxZombies && !zombieCollisions()) {
        spawnZombie();
    }

    if(keys & KEY_LEFT) {
        moveLeft = true;
    }
    if(keys & KEY_RIGHT) {
        moveRight = true;
    }
    if(keys & KEY_A && canPersonJump()){
        ammoDone = person.reload(&ammountBullet);
    }
    else if(keys & KEY_UP && canPersonJump()) {
        jumpTimer = 16;
    }
    if(keys & KEY_B) {
        shoot();
    }
    if(keys & KEY_START && !clicked_START) {
        openShop();
        clicked_START = keys & KEY_START;
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

    engine->updateSpritesInScene();
}

void GameScreen::load() {
    engine.get()->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritedataSharedPal, sizeof(spritedataSharedPal)));

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gameBackgroundPal, sizeof(gameBackgroundPal)));
    bg = std::unique_ptr<Background>(new Background(1, gameBackgroundTiles, sizeof(gameBackgroundTiles), gameBackgroundMap, sizeof(gameBackgroundMap)));
    bg.get()->useMapScreenBlock(16);

    resetGame();
}

bool GameScreen::canPersonJump() {
    if (person.getY() == 128) {
        return true;
    }
    else return false;
}

bool GameScreen::zombieCollisions() {
    for (int i = 0; i < zombies.size(); ++i) {
        int xZombie = zombies[i].get()->getX();
        int space = zombies[i].get()->getWidth() + 4;

        if(GBA_SCREEN_WIDTH - xZombie < space){
            return true;
        }
    }
    return false;
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

void GameScreen::textOnScreen() {
    if(!ammoDone){
        TextStream::instance().setText(std::string("NO AMMUNITION !!!"), 1, 5);
    }
    else{
        TextStream::instance().setText("", 1, 5);
    }

    if(weaponEmpty){
        TextStream::instance().setText(std::string("RELOAD!!!"), 3, 5);
    }
    else{
        TextStream::instance().setText("", 3, 5);
    }

    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 5, 5);
    TextStream::instance().setText(std::string("Score: ") + std::to_string(score), 7, 5);
    TextStream::instance().setText(std::string("Points: ") + std::to_string(points), 9, 5);
    TextStream::instance().setText(std::string("Bullets/Ammo: ") + std::to_string(person.getGun()->getBullets())
    + "/" + std::to_string(ammountBullet), 11, 5);
    // TextStream::instance().setText(std::to_string(zombies[0].get()->getLife()), 13, x van zombie);
}

void GameScreen::shopOnScreen(u16 keys) {
    TextStream::instance().setText(std::string("Click A for AMMO                (+20/+40/+10)  [-6p]"), 6, 1);
    TextStream::instance().setText(std::string("Click B for NEW WEAPON          (PISTOL/AK-47/SNIPER) [-20p]"), 8, 1);
    TextStream::instance().setText(std::string("Click START to return"), 13, 1);
    TextStream::instance().setText(std::string("Points: ") + std::to_string(points), 11, 1);
    TextStream::instance().setText(std::string("Total Ammo: ") + std::to_string(person.getGun()->getBullets() + ammountBullet), 12, 1);

    if(keys & KEY_A && !clicked_A) {
        if(points >= 6){
            ammountBullet = ammountBullet + 30;
            points = points - 6;
        }
    }
    if(keys & KEY_B && !clicked_B) {
        if(points >= 20){
            int chanceWeapon = rand() % 10 + 1;
            if(chanceWeapon < 5){
                ammountBullet = 24;
                weapon = std::shared_ptr<Weapon>(new Pistol(builder,person.getX() + person.getWidth(),138, 6));
                person.setGun(weapon);
                shootFast = false;
            }
            else if(chanceWeapon < 9){
                ammountBullet = 60;
                weapon = std::shared_ptr<Weapon>( new AK47(builder,person.getX() + person.getWidth()/2,137, 30));
                person.setGun(weapon);
                shootFast = true;
            }
            else{
                ammountBullet = 15;
                weapon = std::shared_ptr<Weapon>(new Sniper(builder,person.getX(),136, 1));
                person.setGun(weapon);
                shootFast = false;
            }
            engine->updateSpritesInScene();
            points = points - 20;
        }
    }
    if(keys & KEY_START && !clicked_START) {
        quitShop();
    }
}

void GameScreen::quitShop() {
    shopAvialable = false;
    TextStream::instance().clear();

    for (int i = 0; i < zombies.size(); ++i) {
        zombies[i]->setVelocity(-1, 0);
    }
    for (int i = 0; i < bulletSprites.size(); ++i) {
        bulletSprites[i]->setVelocity(bulletSpeed, 0);
    }
}

void GameScreen::openShop() {
    shopAvialable = true;
    TextStream::instance().clear();

    for (int i = 0; i < zombies.size(); ++i) {
        zombies[i]->setVelocity(0, 0);
    }
    for (int i = 0; i < bulletSprites.size(); ++i) {
        bulletSprites[i]->setVelocity(0, 0);
    }

    person.sprite->setVelocity(0, 0);
    weapon->sprite->setVelocity(0, 0);
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
            if (bulletSprites[j]->isOffScreen()) {
                break;
            }

            if (zombies[i]->sprite->collidesWith(*bulletSprites[j])){
                bool headshot = false;
                int damageGun = person.getGun()->getDamage();
                int chanceHeadshot = person.getGun()->getHeadshotChance();
                int chance = rand() % 10 + 1;

                if(chance <= chanceHeadshot){
                    headshot = true;
                }

                if(damageGun >= zombies[i].get()->getLife()){
                    zombiesToRemove.push_back(i);
                    score++;
                    points++;
                }
                else{
                    zombies[i].get()->hit(damageGun, headshot);
                }

                bulletsToRemove.push_back(j);
                break;
            }
        }
    }
}

void GameScreen::shoot() {
    if (shootTimer < 25 && !shootFast) {
        return;
    }
    else if(shootTimer < 7 && shootFast) {
        return;
    }
    else {
        shootTimer = 0;
    }

    weaponEmpty = !person.shoot();

    if (!weaponEmpty) {
        int xGun = person.getGun()->getX();
        int space = person.getGun()->getWidth()/2;
        bulletSprites.push_back(builder
                                        .withSize(SIZE_8_8)
                                        .withLocation(xGun + space, person.getGun()->getY()+1)
                                        .withData(bulletTiles, sizeof(bulletTiles))
                                        .withVelocity(2, 0)
                                        .buildPtr());
        engine->updateSpritesInScene();
    }
}

void GameScreen::removeExcessSprites() {
    // kan niet alle frames verwijderen
    // want om een of andere reden blijven de sprites zichtbaar ookal bestaan ze niet meer
    for (int i = zombiesDeleteQueue.size() - 1; i >= 0; --i) {
        zombies.erase(zombies.begin() + zombiesDeleteQueue[i]);
    }
    for (int j = bulletsDeleteQueue.size()-1; j >= 0; --j) {
        if (bulletSprites[j]->isOffScreen()) {
            bulletSprites.erase(bulletSprites.begin() + j);
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
    if(countZombies < 6){
        int life = rand() % maxLife + 1;
        countZombies++;
        zombies.push_back(std::shared_ptr<Zombie>(new Zombie(builder, GBA_SCREEN_WIDTH, 128, -1*zspeed, 0, life)));
    }
    if(zombieSpeedUp > 3){
        maxZombies++;
        if(zspeed > 3){}
        else{
            zspeed++;
        }
        zombieSpeedUp = 0;
    }
    else{
        countZombies = 0;
        maxLife = maxLife + 2;
        zombieSpeedUp++;
    }
}