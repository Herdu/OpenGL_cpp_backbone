//
// Created by matt on 28.05.17.
//

#include "skybox.h"


Skybox::Skybox(){

    backVertices=SkyboxInternal::backVertices;
    backVertexNormals=SkyboxInternal::backVertexNormals;

    frontVertices=SkyboxInternal::frontVertices;
    frontVertexNormals=SkyboxInternal::frontVertexNormals;

    leftVertices=SkyboxInternal::leftVertices;
    leftVertexNormals=SkyboxInternal::leftVertexNormals;

    rightVertices=SkyboxInternal::rightVertices;
    rightVertexNormals=SkyboxInternal::rightVertexNormals;

    bottomVertices=SkyboxInternal::bottomVertices;
    bottomVertexNormals=SkyboxInternal::bottomVertexNormals;

    topVertices=SkyboxInternal::topVertices;
    topVertexNormals=SkyboxInternal::topVertexNormals;


    TexCoords=SkyboxInternal::texCoords;
    vertexCount= 6;
}

void Skybox::draw(){

    glClearColor(0,0,0,0);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    //back wall
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)back.data());
    glVertexPointer(4,GL_FLOAT,0,backVertices);
    //glColorPointer(4,GL_FLOAT,0,colors);
    glNormalPointer(GL_FLOAT,sizeof(float)*4,backVertexNormals);
    glTexCoordPointer(2,GL_FLOAT,0,TexCoords);
    glDrawArrays(GL_TRIANGLES,0,vertexCount);


    //front wall
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)front.data());
    glVertexPointer(4,GL_FLOAT,0,frontVertices);
    //glColorPointer(4,GL_FLOAT,0,colors);
    glNormalPointer(GL_FLOAT,sizeof(float)*4,frontVertexNormals);
    glTexCoordPointer(2,GL_FLOAT,0,TexCoords);
    glDrawArrays(GL_TRIANGLES,0,vertexCount);

    //left wall
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)left.data());
    glVertexPointer(4,GL_FLOAT,0,leftVertices);
    //glColorPointer(4,GL_FLOAT,0,colors);
    glNormalPointer(GL_FLOAT,sizeof(float)*4,leftVertexNormals);
    glTexCoordPointer(2,GL_FLOAT,0,TexCoords);
    glDrawArrays(GL_TRIANGLES,0,vertexCount);

    //right wall
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)right.data());
    glVertexPointer(4,GL_FLOAT,0,rightVertices);
    //glColorPointer(4,GL_FLOAT,0,colors);
    glNormalPointer(GL_FLOAT,sizeof(float)*4,rightVertexNormals);
    glTexCoordPointer(2,GL_FLOAT,0,TexCoords);
    glDrawArrays(GL_TRIANGLES,0,vertexCount);


    //bottom wall
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)bottom.data());
    glVertexPointer(4,GL_FLOAT,0,bottomVertices);
    //glColorPointer(4,GL_FLOAT,0,colors);
    glNormalPointer(GL_FLOAT,sizeof(float)*4,bottomVertexNormals);
    glTexCoordPointer(2,GL_FLOAT,0,TexCoords);
    glDrawArrays(GL_TRIANGLES,0,vertexCount);


    //top wall
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)top.data());
    glVertexPointer(4,GL_FLOAT,0,topVertices);
    //glColorPointer(4,GL_FLOAT,0,colors);
    glNormalPointer(GL_FLOAT,sizeof(float)*4,topVertexNormals);
    glTexCoordPointer(2,GL_FLOAT,0,TexCoords);
    glDrawArrays(GL_TRIANGLES,0,vertexCount);


    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);



}



void Skybox::loadTextures(){



    lodepng::decode(this->front, this->width, this->height, "images/skybox/front.png");

    lodepng::decode(this->left, this->width, this->height, "images/skybox/left.png");
    lodepng::decode(this->back, this->width, this->height, "images/skybox/back.png");
    lodepng::decode(this->right, this->width, this->height, "images/skybox/right.png");
    lodepng::decode(this->top, this->width, this->height, "images/skybox/top.png");
    lodepng::decode(this->bottom, this->width, this->height, "images/skybox/bottom.png");



    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return;
}





namespace SkyboxInternal {
    unsigned int vertexCount=6;

    float backVertices[]={
            1.0f,-1.0f,-1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
            -1.0f,-1.0f,-1.0f,1.0f,

            1.0f,-1.0f,-1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
    };

    float backVertexNormals[]={
            1.0f,-1.0f,-1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
            -1.0f,-1.0f,-1.0f,1.0f,

            1.0f,-1.0f,-1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
    };

    float frontVertices[]={
            -1.0f,-1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,

            -1.0f,-1.0f, 1.0f,1.0f,
            -1.0f, 1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,
    };

    float frontVertexNormals[]={
            -1.0f,-1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,

            -1.0f,-1.0f, 1.0f,1.0f,
            -1.0f, 1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,
    };

    float leftVertices[]={
            1.0f,-1.0f, 1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
            1.0f,-1.0f,-1.0f,1.0f,

            1.0f,-1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
    };

    float leftVertexNormals[]={
            1.0f,-1.0f, 1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
            1.0f,-1.0f,-1.0f,1.0f,

            1.0f,-1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
    };


    float rightVertices[]={
            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f, 1.0f, 1.0f,1.0f,
            -1.0f,-1.0f, 1.0f,1.0f,

            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
            -1.0f, 1.0f, 1.0f,1.0f,
    };

    float rightVertexNormals[]={
            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f, 1.0f, 1.0f,1.0f,
            -1.0f,-1.0f, 1.0f,1.0f,

            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
            -1.0f, 1.0f, 1.0f,1.0f,
    };

    float bottomVertices[]={
            -1.0f,-1.0f,-1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f,-1.0f,1.0f,

            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
    };

    float bottomVertexNormals[]={
            -1.0f,-1.0f,-1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f,-1.0f,1.0f,

            -1.0f,-1.0f,-1.0f,1.0f,
            -1.0f,-1.0f, 1.0f,1.0f,
            1.0f,-1.0f, 1.0f,1.0f,
    };


    float topVertices[]={
            -1.0f, 1.0f, 1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,

            -1.0f, 1.0f, 1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
    };

    float topVertexNormals[]={
            -1.0f, 1.0f, 1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
            1.0f, 1.0f, 1.0f,1.0f,

            -1.0f, 1.0f, 1.0f,1.0f,
            -1.0f, 1.0f,-1.0f,1.0f,
            1.0f, 1.0f,-1.0f,1.0f,
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