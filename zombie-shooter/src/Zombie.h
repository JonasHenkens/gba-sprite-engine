//
// Created by Souhaib El Habti on 27/12/2019.
//

#ifndef GIT_ZOMBIE_H
#define GIT_ZOMBIE_H


class Zombie {
private:
    bool headshot;
    int lenght;
    int life;
public:
    bool isDead();
    bool isHeadshot();
    int getLenght();
    int getLife();
    void hit();
};


#endif //GIT_ZOMBIE_H
