//
// Created by matt on 28.05.17.
//

#ifndef OPENGL_CPP_BACKBONE2_SKYBOX_H
#define OPENGL_CPP_BACKBONE2_SKYBOX_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../imgLoader/lodepng.h"

using namespace std;
using namespace glm;


namespace SkyboxInternal {
    extern float backVertices[];
    extern float backVertexNormals[];
    extern float frontVertices[];
    extern float frontVertexNormals[];
    extern float leftVertices[];
    extern float leftVertexNormals[];
    extern float rightVertices[];
    extern float rightVertexNormals[];
    extern float bottomVertices[];
    extern float bottomVertexNormals[];
    extern float topVertices[];
    extern float topVertexNormals[];



    extern float texCoords[];
}





class Skybox{

private:
    unsigned int vertexCount;
    float* backVertices;
    float* backVertexNormals;

    float* frontVertices;
    float* frontVertexNormals;

    float* leftVertices;
    float* leftVertexNormals;

    float* rightVertices;
    float* rightVertexNormals;

    float* bottomVertices;
    float* bottomVertexNormals;

    float* topVertices;
    float* topVertexNormals;



    float* TexCoords;





public:
    Skybox();
    void loadTextures();
    void draw(vec3 color);
    vector<unsigned char> front;
    vector<unsigned char> right;
    vector<unsigned char> back;
    vector<unsigned char> left;
    vector<unsigned char> top;
    vector<unsigned char> bottom;
    unsigned height;
    unsigned width;
};








#endif //OPENGL_CPP_BACKBONE2_SKYBOX_H
