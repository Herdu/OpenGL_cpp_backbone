//
// Created by matt on 01.05.17.
//


#include "drawable.h"


Drawable::Drawable(char *filename) {

    objLoader *objData = new objLoader();

    objData->load(filename);

    //przejdz po wszystkich face i utworz bufor wierzcholkow
    this->verticesCount = 0;

    for (int i=0; i<objData->faceCount; i++)
    {
        for (int j=0; j<3; j++)
        {
            this->verticesBuffer.push_back(objData->vertexList[objData->faceList[i]->vertex_index[j]]->e[0]);
            this->verticesBuffer.push_back(objData->vertexList[objData->faceList[i]->vertex_index[j]]->e[1]);
            this->verticesBuffer.push_back(objData->vertexList[objData->faceList[i]->vertex_index[j]]->e[2]);
        }

    }
    this->verticesCount = objData->faceCount*3;

}


void Drawable::draw() {

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0, &(this->verticesBuffer[0]));
    glDrawArrays(GL_TRIANGLES,0, this->verticesCount);
    glDisableClientState(GL_VERTEX_ARRAY);

}
