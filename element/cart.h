//
// Created by matt on 14.06.17.
//

#ifndef OPENGL_CPP_BACKBONE2_CART_H
#define OPENGL_CPP_BACKBONE2_CART_H

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
#include "../element/track.h"

using namespace std;
using namespace glm;


class Cart{
private:
    int currentPosition;
    int prevPosition;
    int nextPosition;

    vec3 position;
    float angle;
    mat4 Matrix;
    float currentAngle;

public:
    void draw(mat4 V, Track track);
    void move(Track track);
    void update(float deltaTime);
    vec3 getPosition(){return this->position;};
    Cart();
};

#endif //OPENGL_CPP_BACKBONE2_CART_H
