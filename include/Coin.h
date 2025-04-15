#ifndef COIN_H
#define COIN_H

#include "GameObject.h"

class Coin : public GameObject {
public:
    Coin();
    void onCollide(Player* player) override;
};

#endif
