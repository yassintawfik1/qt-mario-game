#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <QKeyEvent>

class Level;  

class Player : public GameObject {
public:
    Player();

    int getHealth() const;
    int getScore() const;
    int getCoins() const;

 
    void addScore(int points);
    void addCoin(int count);
    void decreaseHealth(int amount);
    void increaseHealth(int amount);

   
    void jump();
    void moveLeft();
    void moveRight();
    void stopMoving();

  
    void updateMovement();

protected:
    
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    int health;
    int score;
    int coins;
    double velocityX;
    double velocityY;
    int jumpsRemaining;
    bool onGround;
    bool isGameStarted;
};

#endif

