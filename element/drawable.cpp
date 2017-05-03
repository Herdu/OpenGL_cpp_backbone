//
// Created by matt on 01.05.17.
//


#include "drawable.h"


Drawable::Drawable(char *filename) {

    this->rotateSpeed = 100.0f;
    this->rotateX = 0.01f;

    objLoader *objData = new objLoader();

    objData->load(filename);

    //przejdz po wszystkich face i utworz bufor wierzcholkow
    this->verticesCount = 0;

    vec3 array[objData->faceCount];
    for (int i=0; i<objData->faceCount; i++)
        array[i] = vec3(1.1111f, 0,0);


    vector< vector<vec3> > tab;
    for (int i=0; i<objData->faceCount; i++){
        vector<vec3> temp;
        tab.push_back(temp);
    }




        for (int i=0; i<objData->faceCount; i++) {//for every face
        for (int j=0; j<3; j++){  //for every vertex in face
            for(int k=0; k<3; k++){ //for every coordinate in vertex
                //push vertex to buffer
                this->verticesBuffer.push_back(objData->vertexList[objData->faceList[i]->vertex_index[j]]->e[k]);
                //push vertex normal to buffer
                this->normalBuffer.push_back(objData->normalList[objData->faceList[i]->normal_index[j]]->e[k]);
            }


        }

    }





    this->verticesCount = this->verticesBuffer.size()/3;


    cout<<"Objekt "<<filename<<":"<<endl;
    cout<<"  liczba wierzcholkow:           "<<objData->vertexCount<<endl;
    cout<<"  liczba faces:                  "<<objData->faceCount<<endl;
    cout<<"  liczba wierzcholkow w buforze: "<<this->verticesCount<<endl;


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
