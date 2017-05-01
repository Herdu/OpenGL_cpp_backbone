//
// Created by matt on 29.04.17.
//

#ifndef OPENGL_CPP_BACKBONE2_PLAYER_H_H
#define OPENGL_CPP_BACKBONE2_PLAYER_H_H

#include <GLFW/glfw3.h>

class Player{

public:
    float posX;
    float posY;
    float posZ;
    float lookX;
    float lookY;
    float lookZ;
    float upX;
    float upY;
    float upZ;

    GLfloat deltaTime;
    GLfloat lastFrame;

    Player();
    void move(float x, float y, float z);
    void update();
};

#endif //OPENGL_CPP_BACKBONE2_PLAYER_H_H
