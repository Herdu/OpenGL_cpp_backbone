//
// Created by matt on 29.04.17.
//

#ifndef OPENGL_CPP_BACKBONE2_DRAWABLE_H
#define OPENGL_CPP_BACKBONE2_DRAWABLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../loader/objLoader.h"

using namespace std;
using namespace glm;

class Drawable{
private:
    vector<float> verticesBuffer;
    vector<float> normalBuffer;

    int verticesCount;


    float rotateX;
    float rotateSpeed;

public:
    mat4 modelMatrix;
    void draw(mat4 V);
    Drawable(char* filename);
};
#endif //OPENGL_CPP_BACKBONE2_DRAWABLE_H
