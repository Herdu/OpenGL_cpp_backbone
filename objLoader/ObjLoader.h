//
// Created by matt on 16.04.17.

// 
// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ


//

#ifndef OPENGL_CPP_BACKBONE_OBJLOADER_H
#define OPENGL_CPP_BACKBONE_OBJLOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void load_obj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements);



#endif //OPENGL_CPP_BACKBONE_OBJLOADER_H
