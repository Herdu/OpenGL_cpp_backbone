//
// Created by matt on 29.04.17.
//

#ifndef OPENGL_CPP_BACKBONE2_PLAYER_H_H
#define OPENGL_CPP_BACKBONE2_PLAYER_H_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include "../enum/directions.h"

#include "../element/track.h"
#include "../element/cart.h"

using namespace std;
using namespace glm;

class Player{
    vec3 eye;
    vec3 look;
    vec3 up;
    mat4 cameraMatrix;
    vec3 position;

    vec3 direction;
    vec3 right;

    float step;
    float rotStep;



    float horizontalAngle;
    float verticalAngle;

    int loopIterator;

    ofstream myfile;


    vec3 lookAtOnTrack;
    int currentTrack;

    bool isTorch;


public:

    Player();
    vec3 getPosition(){return this->position;};
    void move(Direction direction,float delta);
    void rotate(Direction direction,float delta);
    void update();
    void goToTrack(Track track);
    void moveOnTrack(Cart cart);
    void leaveTrack();
    mat4 getCameraMatrix();
    bool isOnTrack;

    void torch();
    void updateTorch(mat4 V);
    void init();
};

#endif //OPENGL_CPP_BACKBONE2_PLAYER_H_H
