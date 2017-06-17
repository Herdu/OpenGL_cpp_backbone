//
// Created by matt on 13.06.17.
//

#ifndef OPENGL_CPP_BACKBONE2_TRACK_H
#define OPENGL_CPP_BACKBONE2_TRACK_H


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

#include "../cube/cube.h"
#include "../cube/sphere.h"
#include "../cube/detailed_cube.h"

#include "../imgLoader/lodepng.h"

using namespace std;
using namespace glm;


struct TrackPoint{
    vec3 point1;
    vec3 point2;
    vec3 point3;
    vec3 point4;
    vec3 center;
};



class Track{
private:
    vector<float> buffer;
    vector<float> normal;
    int bufferCount;
    float* textureCoord;


    vector<unsigned char> texture;
    unsigned height;
    unsigned width;
    void generateColumn();

    vector<float> columnBuffer;
    int columnCount;
    vector<float> columnNormal;

public:
    void load();
    void draw(mat4 V);
    vector<TrackPoint> trackPoint;

};


#endif //OPENGL_CPP_BACKBONE2_TRACK_H
