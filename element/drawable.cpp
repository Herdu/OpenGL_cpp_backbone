//
// Created by matt on 01.05.17.
//


#include "drawable.h"







Drawable::Drawable(char *filename) {

    this->rotateSpeed = 100.0f;
    this->rotateX = 0.01f;

    objLoader *objData = new objLoader();

    objData->load(filename);



    vector< vector<vec3> > normals;

    //utworz wektor wektorow wektorow normalnych
    for (int i=0; i<objData->vertexCount; i++){
        vector<vec3> v;
        normals.push_back(v);
    }


    //dla kazdego wierzcholka utworz wektor wektorow normalnych

    for (int i=0; i<objData->faceCount; i++) {//for every face
        for (int j=0; j<3; j++) {  //for every vertex in face
            int vertexIndex = objData->faceList[i]->vertex_index[j];
            int normalIndex = objData->faceList[i]->normal_index[j];
            float x = objData->normalList[normalIndex]->e[0];
            float y = objData->normalList[normalIndex]->e[1];
            float z = objData->normalList[normalIndex]->e[2];
            vec3 normal = vec3(x, y, z);

            normals[vertexIndex].push_back(normal);
        }
    }

    //normalizuj normalne wierzcholkow
    for (int i=0; i<normals.size(); i++){
        for (int j=1; j<normals[i].size(); j++){
            normals[i][0] += normals[i][j];
        }

        normals[i][0] = normalize(normals[i][0]);
    }



    //umiesc wierzcholki i normalne w buforach
    for (int i=0; i<objData->faceCount; i++) {//for every face
        for (int j=0; j<3; j++){  //for every vertex in face
            int vertexIndex = objData->faceList[i]->vertex_index[j];
            int normalIndex = objData->faceList[i]->normal_index[j];

            for(int k=0; k<3; k++){ //for every coordinate in vertex
                //push vertex to buffer
                this->verticesBuffer.push_back(objData->vertexList[vertexIndex]->e[k]);
                //push vertex normal to buffer
                //this->normalBuffer.push_back(objData->normalList[normalIndex]->e[k]);
            }
                this->normalBuffer.push_back(normals[vertexIndex][0].x);
                this->normalBuffer.push_back(normals[vertexIndex][0].y);
                this->normalBuffer.push_back(normals[vertexIndex][0].z);

        }
    }






    this->verticesCount = this->verticesBuffer.size()/3;

    this->modelMatrix = mat4(1.0f);




}


void Drawable::draw(mat4 V) {


    this->modelMatrix = rotate(this->modelMatrix, rotateSpeed*(rotateX*3.14f/180.0f), vec3(0,1,0));

    //this->modelMatrix = scale(this->modelMatrix, vec3(0.01f,0.01f,0.01f));

    //  this->modelMatrix = translate(this->modelMatrix, vec3(0,-1.0f,30.0f));

    glLoadMatrixf(glm::value_ptr(V*this->modelMatrix));


    glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);


     glVertexPointer(3,GL_FLOAT,0, &(this->verticesBuffer[0]));
    glNormalPointer(GL_FLOAT,0, &(this->normalBuffer[0]));


     glDrawArrays(GL_TRIANGLES,0, this->verticesCount);


   glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);


}
