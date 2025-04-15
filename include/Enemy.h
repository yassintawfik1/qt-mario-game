#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
public:
    Enemy();
    void onCollide(Player* player) override;
    void setDirection(int direction);
    int direction() const;
private:
    int dir;
};

#endif


   
