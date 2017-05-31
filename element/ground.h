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

public:
    Ground();
    void draw(mat4 V);
};

#endif //OPENGL_CPP_BACKBONE2_GROUND_H
