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

class Ground{
private:
    float *vertices;

public:
    Ground();
    void draw();
};

#endif //OPENGL_CPP_BACKBONE2_GROUND_H
