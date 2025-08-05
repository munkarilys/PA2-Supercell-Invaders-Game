#include "GalgolaEnemy.h"

GalgolaEnemy::GalgolaEnemy(int xpos, int ypos) : EnemyShip(xpos, ypos, 1.0, 20, 50) {
    amIBoss = false;
    enemyShipSprite.load("CompressedImages/Galgola_sprite_open.png");
    enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.03, enemyShipSprite.getHeight() * 0.03);
    
    
}


void GalgolaEnemy::update(const ofPoint& playerPos) {
    // Calculate the angle to the player
        ofVec2f toPlayer = playerPos - pos;
        float angleToPlayer = ofRadToDeg(-atan2(toPlayer.x, toPlayer.y));

    // Update ship's orientation
        shipOrientation = angleToPlayer;

    // Move towards the player
        pos += toPlayer.getNormalized() * speed/2; //slow speed
        enemyHitBox->box.setPosition(pos.x - 15, pos.y - 10);

    this->shotTimer++;
    // Check if the ship should shoot
        if(shotTimer % 120 == 0) { //shoot two bullets
            shoot();
        }
        if(shotTimer % 125 == 0) {
            shoot();
             // resets the timer
        }

            
        
}


void GalgolaEnemy::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 60, 60);
    ofPopMatrix();
    
    if(showHitboxes){
        enemyHitBox->draw();
    }
}


void GalgolaEnemy::shoot() {
    // Create a new projectile and add it to the list of bullets
        Projectiles p = Projectiles(pos, shipOrientation + 90);
        p.setColors(ofColor::red, ofColor::orange);
        enemyBullets.push_back(p);
        SoundManager::playSong("bulletSound", false);
}