#include "Coin.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QPixmap>

using namespace std;

Coin::Coin() {
    
    setPixmap(QPixmap(":/images/coin.png"));
}

void Coin::onCollide(Player* player) {
    if (!scene()) return;
    
    player->addCoin(1);
    player->addScore(10);
   
    scene()->removeItem(this);
    delete this;
}
