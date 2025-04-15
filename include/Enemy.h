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

GameObject.h

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>


class Player;

class GameObject : public QGraphicsPixmapItem {
public:
    GameObject();
    virtual ~GameObject() {}
    
    virtual void onCollide(Player* player);
};

#endif
