#pragma once
#include "Boss.h"


class Sakuya : public Boss {
    private:
        float shootAngleOffset = 0.0; // Keep track of the shooting angle offset for the spiral pattern
        ofPoint shootingPoint;
        float radius = 0.0; // Initial radius
        int bulletSpawnCounter = 0; // Counter to manage bullet spawn timing


    public:
        Sakuya(int xpos, int ypos, string name);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;

};
