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
#include "../enum/directions.h"

using namespace std;
using namespace glm;

class Player{

public:
    vec3 eye;
    vec3 look;
    vec3 up;
    mat4 cameraMatrix;

    vec3 direction;
    vec3 right;
    vec3 position;

    float step;
    float rotStep;


    float horizontalAngle;
    float verticalAngle;



    Player();
    void move(Direction direction,float delta);
    void rotate(Direction direction,float delta);
    void update();
    mat4 getCameraMatrix();
};

#endif //OPENGL_CPP_BACKBONE2_PLAYER_H_H
