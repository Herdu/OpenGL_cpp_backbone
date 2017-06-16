//
// Created by matt on 29.04.17.
//


#include "ground.h"


void Ground::draw(mat4 V){

    glColor3d(1,1,1);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)texture.data());




    int groundSize = 2;
    int _scale = 300.0f/groundSize;


    for(int i=0; i<groundSize; i++){
        for (int j=0; j<groundSize; j++){


            mat4 M=mat4(1.0f);
            M = scale(M, vec3(_scale,1.0f, _scale));
            M = translate(M, vec3((i*1.0f*_scale - _scale),-2.0f,(j*1.0f*_scale - _scale)));
            M = translate(M, vec3(0, -10.0f, 0));
            glLoadMatrixf(glm::value_ptr(V*M));
            Models::detailedCube.drawSolid();


        }
    }


    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);


};


Ground::Ground(){

    this->vertices = GroundInternal::vertices;
    this->normals = GroundInternal::normals;
    this->texCoords = GroundInternal::texCoords;
    this->vertexCount = 6;
};

namespace GroundInternal{
    float vertices[] ={
            -1.0f,-1.0f,-1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f,-1.0f,1.0f,

            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
    };

    float normals[] = {
            -1.0f,-1.0f,-1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f,-1.0f,1.0f,

            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
    };


    float texCoords[]={
            1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
            1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

            1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
            1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

            1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
            1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

            1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
            1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

            1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
            1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

            1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
            1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
    };
}








void Ground::loadTextures(){



    lodepng::decode(this->texture, this->width, this->height, "images/asfalt.png");



    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return;
}










