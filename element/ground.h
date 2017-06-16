//
// Created by matt on 29.04.17.
//

#ifndef OPENGL_CPP_BACKBONE2_GROUND_H
#define OPENGL_CPP_BACKBONE2_GROUND_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawable.h"
#include "../cube/detailed_cube.h"


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "../imgLoader/lodepng.h"

namespace GroundInternal{
    extern float vertices[];
    extern float normals[];
    extern float texCoords[];

}



class Ground{
private:
    float *vertices;
    float* normals;
    float* texCoords;
    int vertexCount;
    vector<unsigned char> texture;
    unsigned height;
    unsigned width;

public:
    Ground();
    void draw(mat4 V);
    void loadTextures();
};

#endif //OPENGL_CPP_BACKBONE2_GROUND_H
