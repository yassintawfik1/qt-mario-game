#include "Mario.h"
#include <QPixmap>

using namespace std;

Mario::Mario() : Player() {
  
    setPixmap(QPixmap(":/images/mario.png"));
}

Obstacle.cpp

#include "Obstacle.h"
#include "Player.h"
#include <QPixmap>

using namespace std;

Obstacle::Obstacle() {

    setPixmap(QPixmap(":/images/obstacle.png"));
}

void Obstacle::onCollide(Player* player) {
   
    player->decreaseHealth(1);
  
}
