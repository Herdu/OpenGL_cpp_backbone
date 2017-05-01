//
// Created by matt on 29.04.17.
//

#include "player.h"

Player::Player(){

    this->posX = 0.0f;
    this->posY = 0.0f;
    this->posZ = -5.0f;

    this->lookX = 0;
    this->lookY = 0;
    this->lookZ = 0;

    this->upX = 0;
    this->upY = 0;
    this->upZ = 0;


    this->deltaTime = 0.0f;	// Time between current frame and last frame
    this->lastFrame = 0.0f;

}

void Player::move(float x, float y, float z) {
    this->posX += x;
    this->posY += y;
    this->posZ += z;

    this->lookX += x;
    this->lookY += y;
    this->lookZ += z;

}



void Player::update(){

    GLfloat currentFrame = glfwGetTime();
    this->deltaTime = currentFrame - lastFrame;
    this->lastFrame = currentFrame;
}