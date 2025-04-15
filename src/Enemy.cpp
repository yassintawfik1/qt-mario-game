#include "Enemy.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QPixmap>

using namespace std;

Enemy::Enemy() : dir(-1) {

    setPixmap(QPixmap(":/images/enemy.png"));
}

void Enemy::onCollide(Player* player) {
    
    player->decreaseHealth(1);
    
    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}

void Enemy::setDirection(int direction) {
    if (direction < 0) dir = -1;
    else if (direction > 0) dir = 1;
    else dir = 0;
}

int Enemy::direction() const {
    return dir;
}
