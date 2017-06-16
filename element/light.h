//
// Created by matt on 15.06.17.
//

#ifndef OPENGL_CPP_BACKBONE2_LIGHT_H
#define OPENGL_CPP_BACKBONE2_LIGHT_H



#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../cube/sphere.h"


using namespace std;
using namespace glm;

class Light{
private:
    vec3 position;
    float posx;
    float posy;
    float posz;
    float dirx;
    float diry;
    float dirz;
public:
    void init();
    void draw(mat4 V);
};

#endif //OPENGL_CPP_BACKBONE2_LIGHT_H
