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




};

void Cart::draw(mat4 V, Track track) {

    this->currentPosition++;
    this->currentPosition = this->currentPosition%(track.trackPoint.size()-3);
    this->position = track.trackPoint[this->currentPosition].center;

    int space = 3;

    int num = 6;
    float _scale = 1.0f;


    float specReflection[] = { 1.0f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specReflection);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, specReflection);


    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);



    for(int i=0; i<num; i++){
        int pos = (this->currentPosition+space*i)%(track.trackPoint.size()-3);
        mat4 M = mat4(1.0f);
        M = translate(M, track.trackPoint[pos].center + vec3(0,1,0));
        M = scale(M, vec3(_scale));
        glLoadMatrixf(glm::value_ptr(V*M));
        Models::sphere.drawSolid();
    }

    //light


    mat4 M = mat4(1.0f);
    glLoadMatrixf(glm::value_ptr(V*M));


    int pos = (this->currentPosition+space*num-1)%(track.trackPoint.size()-3);
    int dir = (this->currentPosition+space*num+1)%(track.trackPoint.size()-3);

    vec3 posTrack = track.trackPoint[pos].center + vec3(0,5,0);
    vec3 dirTrack = track.trackPoint[dir].center - posTrack;

    //float direction[] = {this->position.x + this->direction.x, this->position.y + this->direction.y, this->position.z + this->direction.z};
    float _position[] = { posTrack.x, posTrack.y+5.0f, posTrack.z, 1.0f };
    glLightfv(GL_LIGHT3, GL_POSITION, _position);


    float _dir[] = { dirTrack.x, dirTrack.y,  dirTrack.z,  0.0f };

    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, _dir);



    float specReflection2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specReflection2);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);

};


void Cart::update(float deltaTime){

}


void Cart::init(){

    // Create light components
    float ambientLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specularLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };



    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);

    glLighti(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0f);
    glLighti(GL_LIGHT3, GL_SPOT_EXPONENT, 1.0f);


    glLighti(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0f);

    glLighti(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.7f);
    glLighti(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.5f);


}