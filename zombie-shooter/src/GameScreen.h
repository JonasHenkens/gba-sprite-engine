//
// Created by Wouter Groeneveld on 08/08/18.
//

#ifndef ZOMBIESHOOTER_GAMESCREEN_H
#define ZOMBIESHOOTER_GAMESCREEN_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <vector>
#include "Person.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Pistol.h"

class GameScreen : public Scene {
private:
    std::unique_ptr<Background> bg;
    bool dead;
    bool noAmmo;
    int score;
    int highscore;
    int ammountBullet;

    void youDied();
    void resetGame();
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
    int jumpTimer = 0;
    int shootTimer = 1000;

    Person person;
    Pistol pistol;
    std::vector<std::shared_ptr<Zombie>> zombies;
    std::vector<std::unique_ptr<Sprite>> bulletSprites;
    SpriteBuilder<Sprite> builder;
    std::unique_ptr<Sprite> bullet;
    int counter;
    int counter2;
    int counter3;

    std::vector<int> bulletsToRemove;
    std::vector<int> zombiesToRemove;
    std::vector<int> bulletsDeleteQueue;
    std::vector<int> zombiesDeleteQueue;

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
    void textOnScreen();
    void checkCollisions();
    void shoot();

    void removeExcessSprites();

    void spawnZombie();
};


#endif //ZOMBIESHOOTER_GAMESCREEN_H
