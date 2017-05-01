//
// Created by matt on 29.04.17.
//


#include "ground.h"


void Ground::draw(){

    glColor3d(0,1.0f,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,this->vertices);
    glDrawArrays(GL_TRIANGLES,0,6);
    glDisableClientState(GL_VERTEX_ARRAY);
};


Ground::Ground(){

    float vertices[] ={

                    -1,0,-1,
                    1,0,-1,
                    1,0,1,
                    -1,0,-1,
                    1,0,1,
                    -1,0,1
    };

    this->vertices = &vertices[0];
};

