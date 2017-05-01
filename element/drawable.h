//
// Created by matt on 29.04.17.
//

#ifndef OPENGL_CPP_BACKBONE2_DRAWABLE_H
#define OPENGL_CPP_BACKBONE2_DRAWABLE_H

#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "../loader/objLoader.h"

using namespace std;

class Drawable{
    vector<float> verticesBuffer;
    int verticesCount;

public:
    void draw();
    Drawable(char* filename);
};
#endif //OPENGL_CPP_BACKBONE2_DRAWABLE_H
