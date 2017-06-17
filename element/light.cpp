//
// Created by matt on 15.06.17.
//

#include "light.h"

void Light::init(){

    //glEnable(GL_LIGHT1);

    this->posx = 1.0f;
    this->posy = 3.0f;
    this->posz = 1.0f;

    this->dirx = 0.0f;
    this->diry = 1.0f;
    this->dirz = 0.0f;

    // Create light components
    float ambientLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float _position[] = { posx, posy, posz, 1.0f };
    float direction[] = {0,-1,0};
    float cutoff[] = {50.0f};
    float exponent[] = {1.0f};

    this->position = vec3( posx, posy, posz);

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT1, GL_POSITION, _position);

    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
    glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);





}


void Light::draw(mat4 V) {

    glDisable(GL_LIGHTING);
    mat4 M = mat4(1.0f);



    M = translate(M, this->position);
    M = scale(M, vec3(0.05f));
    glColor3d(1,1,0);
    glLoadMatrixf(glm::value_ptr(V*M));
    Models::sphere.drawSolid();

    M = mat4(1.0f);
    glLoadMatrixf(glm::value_ptr(V));

    float pos[] = {posx, posy,posz, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, pos);

    float direction[] = {this->dirx,this->diry,this->dirz};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);


    glEnable(GL_LIGHTING);
};