//
// Created by matt on 29.04.17.
//


#include "ground.h"


void Ground::draw(mat4 V){
    mat4 M = mat4(1.0f);

    glLoadMatrixf(glm::value_ptr(V*M));
    glColor3d(0,1.0f,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,this->vertices);
    glDrawArrays(GL_TRIANGLES,0,6);
    glDisableClientState(GL_VERTEX_ARRAY);
};


Ground::Ground(){

    float vertices[] ={
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f

    };

    this->vertices = &vertices[0];
};

