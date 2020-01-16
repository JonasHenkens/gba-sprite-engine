//
// Created by Wouter Groeneveld on 08/08/18.
//

#ifndef ZOMBIESHOOTER_GAMESCREEN_H
#define ZOMBIESHOOTER_GAMESCREEN_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <vector>
#include "../Person.h"
#include "../Zombie.h"
#include "../weapons/Weapon.h"
#include "../weapons/Pistol.h"
#include "../weapons/Sniper.h"
#include "../weapons/AK47.h"

class GameScreen : public Scene {
private:
    std::unique_ptr<Background> bg;
    bool shootFast = false;
    bool clicked_A = false;
    bool clicked_B = false;
    bool clicked_START = false;

    int score = 0;
    int points = 0;
    int highscore;
    int ammountBullet = 30;
    int bulletSpeed = 4;

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    int jumpTimer = 0;
    int shootTimer = 1000;

    bool isShopOpened = false;

    void died();

    Person person;
    std::shared_ptr<Weapon> weapon;
    std::vector<std::shared_ptr<Zombie>> zombies;
    std::vector<std::unique_ptr<Sprite>> bulletSprites;
    SpriteBuilder<Sprite> builder;

    std::vector<int> zombiesToRemove;
    std::vector<int> zombiesDeleteQueue;

    bool updateSprites = false;
    int level = 1;
    int openShopNow = false;
    int spawnedZombies = 0;
    int spawnDelayCounter = 20;


public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    GameScreen(std::shared_ptr<GBAEngine> engine) : Scene(engine), highscore(0) {}
    GameScreen(std::shared_ptr<GBAEngine> engine, int highscore) : Scene(engine), highscore(highscore) {}

    void load() override;
    void tick(u16 keys) override;

    bool canPersonJump();
    void checkBounds();
    void move();
    void checkCollisions();
    void shoot();

    void showGameText();
    void updateGameText();
    void showShopText();
    void tickShop(u16 keys);
    void quitShop();
    void openShop();

    void removeExcessSprites();

    void tickSpawnLogic();
};


#endif //ZOMBIESHOOTER_GAMESCREEN_H
