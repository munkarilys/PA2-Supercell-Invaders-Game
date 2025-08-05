#pragma once
#include "Enemy.h"


class GalgolaEnemy : public EnemyShip {
    public:
       GalgolaEnemy(int xpos, int ypos);

        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;

        

};