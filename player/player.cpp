//
// Created by matt on 29.04.17.
//

#include "player.h"

Player::Player(){

    this->myfile.open("track/track.txt");
    this->eye = vec3(0.0f, 0.0f, -5.0f);
    this->look = vec3(0.0f, 0.0f, 0.0f);
    this->up = vec3(0.0f, 1.0f, 0.0f);

    this->position = vec3(0.0f, 5.0f, -30.0f);


    this->horizontalAngle = 0.0f;
    this->verticalAngle = 0.0f;


    this->step = 5.0f;
    this->rotStep = 1.0f;

    this->loopIterator = 0;

    this->isOnTrack = false;

    this->update();



}

void Player::move(Direction _direction, float deltaTime) {

    if(this->isOnTrack)
        return;


    switch(_direction){
        case LEFT:
        this->position -= right * this->step * deltaTime;
            break;
        case RIGHT:
            this->position += right *  this->step * deltaTime;
            break;
        case FORWARD:
            this->position += this->direction * this->step * deltaTime;
            break;
        case BACKWARD:
            this->position -= this->direction * this->step * deltaTime;
            break;
    }




    this->loopIterator++;
    if (loopIterator > 5){

        if (this->myfile.is_open()) {
            this->myfile << this->position.x << " " << this->position.y << " " << this->position.z<< " "<< this->verticalAngle<< " " <<this->horizontalAngle<<'\n';
        }
        this->loopIterator = 0;
    }

}


void Player::rotate(Direction _direction, float deltaTime) {


    switch(_direction){
        case LEFT:
            this->horizontalAngle += rotStep *deltaTime;
            break;
        case RIGHT:
            this->horizontalAngle -= rotStep * deltaTime;
            break;
        case UP:
            this->verticalAngle += rotStep * deltaTime;
            break;
        case DOWN:
            this->verticalAngle -= rotStep * deltaTime;
            break;
    }

    this->update();


}


void Player::update(){


    this->direction = vec3(
            cos(this->verticalAngle)*sin(this->horizontalAngle),
            sin(this->verticalAngle),
            cos(this->verticalAngle)*cos(this->horizontalAngle)
    );

    this->right = vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
    );

    this->up = cross(this->right, this->direction);



        this->cameraMatrix = lookAt(
                this->position,
                this->position + this->direction,
                this->up
        );



}

mat4 Player::getCameraMatrix() {

    this->update();
    return this->cameraMatrix;

}


void Player::goToTrack(Track track){
    this->isOnTrack = true;
};


void Player::leaveTrack(){
    this->isOnTrack = false;

    this->eye = vec3(0.0f, 0.0f, -5.0f);
    this->look = vec3(0.0f, 0.0f, 0.0f);
    this->up = vec3(0.0f, 1.0f, 0.0f);

    this->position = vec3(0.0f, 5.0f, -30.0f);


    this->horizontalAngle = 0.0f;
    this->verticalAngle = 0.0f;
};

void Player::moveOnTrack(Cart cart) {
    this->position = cart.getPosition() + vec3(0, 3.0f, 0);
};