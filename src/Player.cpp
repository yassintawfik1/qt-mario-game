#include "Player.h"
#include "Level.h"
#include "Coin.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Platform.h"
#include "PowerUp.h"
#include "PrincessPeach.h"
#include <QGraphicsScene>

using namespace std;

Player::Player() {

    health = 3;
    score = 0;
    coins = 0;
    
    velocityX = 0;
    velocityY = 0;
    jumpsRemaining = 2;
    onGround = false;
    isGameStarted = false;
}

int Player::getHealth() const { return health; }
int Player::getScore() const  { return score; }
int Player::getCoins() const  { return coins; }

void Player::addScore(int points) {
    score += points;
    if (score < 0) score = 0;
}
void Player::addCoin(int count) {
    coins += count;
    if (coins < 0) coins = 0;
}
void Player::decreaseHealth(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}
void Player::increaseHealth(int amount) {
    health += amount;
    
}

void Player::jump() {
    if (jumpsRemaining > 0) {
        
        velocityY = -15;
        onGround = false;
        jumpsRemaining--;
    }
}

void Player::moveLeft() {
    velocityX = -5;
}

void Player::moveRight() {
    velocityX = 5;
}

void Player::stopMoving() {
    velocityX = 0;
}

void Player::updateMovement() {
    if (!isGameStarted) {
      
        return;
    }

  
    double gravity = 1.0;
    double sceneW = scene()->sceneRect().width();
    double sceneH = scene()->sceneRect().height();


    if (velocityX != 0) {
        setX(x() + velocityX);
        
        if (x() < 0) {
            setX(0);
        }
        if (x() + boundingRect().width() > sceneW) {
            setX(sceneW - boundingRect().width());
        }

        QList<QGraphicsItem*> collidingItemsH = collidingItems();
        for (QGraphicsItem* item : collidingItemsH) {
            Platform* platform = dynamic_cast<Platform*>(item);
            Obstacle* obstacle = dynamic_cast<Obstacle*>(item);
            if (platform || obstacle) {
               
                if (velocityX > 0) {
                    setX(x() - velocityX);
                } else if (velocityX < 0) {
                    setX(x() - velocityX);
                }
                velocityX = 0;
            }
        }
    }

    
    velocityY += gravity;
    setY(y() + velocityY);

    if (y() + boundingRect().height() > sceneH) {
        setY(sceneH - boundingRect().height());
        velocityY = 0;
        onGround = true;
        jumpsRemaining = 2;
    }

    
    QList<QGraphicsItem*> collidingItemsV = collidingItems();
    bool landed = false;
    for (QGraphicsItem* item : collidingItemsV) {
        Platform* platform = dynamic_cast<Platform*>(item);
        Obstacle* obstacle = dynamic_cast<Obstacle*>(item);
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (platform || obstacle) {
            if (velocityY > 0) {  
                setY(item->y() - boundingRect().height());
                velocityY = 0;
                onGround = true;
                jumpsRemaining = 2;
                landed = true;
            } else if (velocityY < 0) {  
                setY(item->y() + item->boundingRect().height());
                velocityY = 0;
            }
        }
        if (enemy) {
            if (velocityY > 0) {  
                scene()->removeItem(enemy);
                delete enemy;
                velocityY = -10;  
                score += 100;
                onGround = true;
                jumpsRemaining = 2;
                landed = true;
            } else {  
                enemy->onCollide(this);
            }
        }
    }
    if (!landed) {
        
        if (velocityY != 0) {
            onGround = false;
        }
    }


    QList<QGraphicsItem*> collidingItemsAll = collidingItems();
    for (QGraphicsItem* item : collidingItemsAll) {
       
        if (Coin* coin = dynamic_cast<Coin*>(item)) {
            coin->onCollide(this);
        } else if (PowerUp* power = dynamic_cast<PowerUp*>(item)) {
            power->onCollide(this);
        } else if (PrincessPeach* peach = dynamic_cast<PrincessPeach*>(item)) {
            peach->onCollide(this);
        } else if (Enemy* enemy = dynamic_cast<Enemy*>(item)) {
            
            enemy->onCollide(this);
        } else if (Obstacle* obs = dynamic_cast<Obstacle*>(item)) {
     
            obs->onCollide(this);
        }
       
    }
}

void Player::keyPressEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) return;  

    if (!isGameStarted) {
        
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            isGameStarted = true;

            if (QGraphicsScene* scn = scene()) {
                if (Level* lvl = dynamic_cast<Level*>(scn)) {
                    lvl->startGame();
                }
            }
        }
        return;  
    }

    
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        moveLeft();
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        moveRight();
        break;
    case Qt::Key_Space:
        jump();
        break;
    default:
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) return;
    if (!isGameStarted) return;


    if ((event->key() == Qt::Key_A || event->key() == Qt::Key_Left) && velocityX < 0) {
        stopMoving();
    }
    if ((event->key() == Qt::Key_D || event->key() == Qt::Key_Right) && velocityX > 0) {
        stopMoving();
    }
}
