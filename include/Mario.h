#ifndef MARIO_H
#define MARIO_H

#include "Player.h"

class Mario : public Player {
public:
    Mario();
};

#endif

Obstacle.h

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject {
public:
    Obstacle();
    void onCollide(Player* player) override;
};

#endif
