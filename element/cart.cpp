//
// Created by matt on 14.06.17.
//

#include "cart.h"

Cart::Cart(){
    this->currentPosition = 0;
    this->prevPosition = 0;
    this->nextPosition = 1;
    this->Matrix = mat4(1.0f);
    this->currentAngle = 0;
};


void Cart::move(Track track){
    this->prevPosition = this->currentPosition;
    this->currentPosition++;
    this->currentPosition = this->currentPosition%(track.trackPoint.size()-3);

    this->nextPosition = (this->currentPosition+1)%(track.trackPoint.size()-3);

    this->position = track.trackPoint[this->currentPosition].center;

    vec3 prevToCurr =  track.trackPoint[currentPosition].center - track.trackPoint[prevPosition].center;
    prevToCurr.y = 0;
    vec3 currToNext =  track.trackPoint[nextPosition].center - track.trackPoint[currentPosition].center;
    currToNext.y = 0;

    float d = acos(dot(normalize(prevToCurr), normalize(currToNext)));

    /*

    vec3 c = cross(prevToCurr, currToNext);
    if (dot(prevToCurr, c) < 0) {
        d = -d;
    }
     */

    if (d>=0 && d < 1)
        this->angle = d;



};

void Cart::draw(mat4 V, Track track) {
    this->move(track);
    this->currentAngle -= this->angle;

    mat4 M = mat4(1.0f);

    M = translate(M, this->position + vec3(0,1,0));
    //M = rotate(M, this->currentAngle*3.14f/180.0f, vec3(0,1,0));

    glLoadMatrixf(glm::value_ptr(V*M));
    Models::sphere.drawSolid();
};


void Cart::update(float deltaTime){

}