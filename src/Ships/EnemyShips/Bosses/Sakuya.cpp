#include "Sakuya.h"


Sakuya::Sakuya(int xpos, int ypos, string name) : Boss(xpos, ypos,0.5, 750, name) {
    enemyShipSprite.load("CompressedImages/Sakuya_boss_sprite.png");
    bulletSprite.load("CompressedImages/knife.png");
    // enemyHitBox = new HitBox(pos.x, pos.y - 30, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.075);
    enemyHitBox = new HitBox( 520, 285, 200, 250);
     shootingPoint = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
    




}
    
void Sakuya::update(const ofPoint& playerPos) {
    // pos.x += speed;
   // enemyHitBox->box.setPosition(pos.x + 10, pos.y - 30);   // Update the hitbox to follow the boss
    shootingPoint = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);   // Update the shooting point





    // Check if ORT is out of the screen, reset position if necessary
    // if (pos.x > ofGetWidth()) {
    //     pos.x = 0;
    // }

    // Shoot bullets in a semi-circular motion
    if (shotTimer % 5  == 0) { // Adjust the value for the frequency of shooting
        shoot();
    }

    if(enemyBullets.size() > 0) {
        // Update bullets
        for (Projectiles& bullet : enemyBullets) {
            bullet.update();
        }
    }

    // Increment shot timer
    shotTimer++;

}

void Sakuya::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    // ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-100, 230, 200, 200);
    //enemyShipSprite.draw(-70, -80, 150, 150);
    ofPopMatrix();
    
    // Uncomment this if you want to see the hitbox for the enemy
    if(showHitboxes){
        enemyHitBox->draw();
    }
    
    showBossHealth();
}


void Sakuya::shoot() {
    const float angleStep = 10.0; // Adjust for how quickly the angle changes
    const float radiusStep = 0.05; // Adjust for how quickly the radius increases
    float angleDegrees = bulletSpawnCounter * angleStep + shootAngleOffset;
    float angleRadians = ofDegToRad(angleDegrees);

    // Calculate the bullet's position using the current radius
    float bulletX = shootingPoint.x + radius * cos(angleRadians);
    float bulletY = shootingPoint.y + radius * sin(angleRadians);
    ofPoint bulletPosition(bulletX, bulletY);

    // Create and initialize the bullet
    Projectiles bullet(bulletPosition, angleDegrees,10,bulletSprite);
    bullet.setSpeed(3);
    bullet.setColors(ofColor::red, ofColor::orange);
    enemyBullets.push_back(bullet);

    // Update radius and shootAngleOffset for the next bullet
    radius += radiusStep;
    shootAngleOffset += angleStep; // This ensures the spiral continues to rotate
    bulletSpawnCounter++; // Increment the counter for the next spawn

    // Adjustments to reset or loop the effect as necessary
    if (shootAngleOffset >= 360.0) shootAngleOffset -= 360.0;
    SoundManager::playSong("bulletSound", false);
}