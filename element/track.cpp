//
// Created by matt on 13.06.17.
//

#include "track.h"

using namespace std;

vec3 calcNormal(vec3 p1, vec3 p2, vec3 p3){

    vec3 U = p2 - p1;
    vec3 V = p3 - p1;
    vec3 normal;

    normal.x = U.y*V.z - U.z*V.y;
    normal.y = U.z*V.x - U.x*V.z;
    normal.z = U.x*V.y - U.y*V.x;
    normal = normalize(normal);

    return normal;

}


void Track::load(){


    //read track from file
    float var1, var2, var3;

    string line;
    ifstream myfile ("track/track3.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            istringstream ss(line);

            string name;
            float var1,var2,var3;

            ss >> var1 >> var2 >> var3;
            cout << var1 <<" "<< var2 <<" "<< var3 << endl << endl;

            vec3 vec(var1,var2,var3);

            TrackPoint tp;
            tp.point1 = vec;

            this->trackPoint.push_back(tp);

        }
        myfile.close();
    }

    else {
        cout << "Unable to open file";
        return;
    }


    //close the loop
    TrackPoint last = trackPoint[trackPoint.size()-1];
    TrackPoint first = trackPoint[0];
    float distance = length(last.point1-first.point1);
    float unitDistance = length(trackPoint[1].point1 - first.point1);
    int n = distance/unitDistance;
    cout<<" brakujace przesla: "<<n<<endl;

    vec3 current = last.point1;
    vec3 diff = (1.0f/n)*(first.point1 - last.point1);
    cout<<"unit distance: "<<unitDistance<<endl;
    cout<<"diff: ("<<diff.x<<" , "<<diff.y<<" , "<<diff.z<<" ) "<<endl;

    for (int i=0; i<n; i++){
        current += diff;
        //cout<<"current: ("<<current.x<<" , "<<current.y<<" , "<<current.z<<" ) "<<endl;
        TrackPoint tmp;
        tmp.point1 = current;
        trackPoint.push_back(tmp);

    }







    //calc other points
    for (int i=0; i<trackPoint.size()-1; i++){
        vec3 point1 = this->trackPoint[i].point1;

        vec3 point2 = point1 + vec3(0, -0.4, 0);

        vec3 point3 = point1 + 3.0f*normalize(cross( this->trackPoint[i+1].point1 - point1,  point2-point1));

        vec3 point4 = point3 + vec3(0, -0.4, 0);

        vec3 center = (point1+point3)*0.5f;

        this->trackPoint[i].point2 = point2;
        this->trackPoint[i].point3 = point3;
        this->trackPoint[i].point4 = point4;
        this->trackPoint[i].center = center;
    }




    //make buffer

    for (int i=0; i<trackPoint.size()-2; i++){
        //top


        buffer.push_back(trackPoint[i].point3.x);
        buffer.push_back(trackPoint[i].point3.y);
        buffer.push_back(trackPoint[i].point3.z);

        buffer.push_back(trackPoint[i].point1.x);
        buffer.push_back(trackPoint[i].point1.y);
        buffer.push_back(trackPoint[i].point1.z);

        buffer.push_back(trackPoint[i+1].point1.x);
        buffer.push_back(trackPoint[i+1].point1.y);
        buffer.push_back(trackPoint[i+1].point1.z);





        buffer.push_back(trackPoint[i].point3.x);
        buffer.push_back(trackPoint[i].point3.y);
        buffer.push_back(trackPoint[i].point3.z);

        buffer.push_back(trackPoint[i+1].point1.x);
        buffer.push_back(trackPoint[i+1].point1.y);
        buffer.push_back(trackPoint[i+1].point1.z);

        buffer.push_back(trackPoint[i+1].point3.x);
        buffer.push_back(trackPoint[i+1].point3.y);
        buffer.push_back(trackPoint[i+1].point3.z);


        //left


        buffer.push_back(trackPoint[i].point4.x);
        buffer.push_back(trackPoint[i].point4.y);
        buffer.push_back(trackPoint[i].point4.z);

        buffer.push_back(trackPoint[i].point3.x);
        buffer.push_back(trackPoint[i].point3.y);
        buffer.push_back(trackPoint[i].point3.z);

        buffer.push_back(trackPoint[i+1].point3.x);
        buffer.push_back(trackPoint[i+1].point3.y);
        buffer.push_back(trackPoint[i+1].point3.z);

        buffer.push_back(trackPoint[i].point4.x);
        buffer.push_back(trackPoint[i].point4.y);
        buffer.push_back(trackPoint[i].point4.z);

        buffer.push_back(trackPoint[i+1].point3.x);
        buffer.push_back(trackPoint[i+1].point3.y);
        buffer.push_back(trackPoint[i+1].point3.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);



        //right

        buffer.push_back(trackPoint[i].point1.x);
        buffer.push_back(trackPoint[i].point1.y);
        buffer.push_back(trackPoint[i].point1.z);

        buffer.push_back(trackPoint[i].point2.x);
        buffer.push_back(trackPoint[i].point2.y);
        buffer.push_back(trackPoint[i].point2.z);

        buffer.push_back(trackPoint[i+1].point2.x);
        buffer.push_back(trackPoint[i+1].point2.y);
        buffer.push_back(trackPoint[i+1].point2.z);


        buffer.push_back(trackPoint[i].point1.x);
        buffer.push_back(trackPoint[i].point1.y);
        buffer.push_back(trackPoint[i].point1.z);

        buffer.push_back(trackPoint[i+1].point2.x);
        buffer.push_back(trackPoint[i+1].point2.y);
        buffer.push_back(trackPoint[i+1].point2.z);


        buffer.push_back(trackPoint[i+1].point1.x);
        buffer.push_back(trackPoint[i+1].point1.y);
        buffer.push_back(trackPoint[i+1].point1.z);









        //bottom
        buffer.push_back(trackPoint[i].point2.x);
        buffer.push_back(trackPoint[i].point2.y);
        buffer.push_back(trackPoint[i].point2.z);

        buffer.push_back(trackPoint[i].point4.x);
        buffer.push_back(trackPoint[i].point4.y);
        buffer.push_back(trackPoint[i].point4.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);


        buffer.push_back(trackPoint[i].point2.x);
        buffer.push_back(trackPoint[i].point2.y);
        buffer.push_back(trackPoint[i].point2.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);


        buffer.push_back(trackPoint[i+1].point2.x);
        buffer.push_back(trackPoint[i+1].point2.y);
        buffer.push_back(trackPoint[i+1].point2.z);









    }


    //last segment
    {
        //top
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point1.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.z);

        buffer.push_back(trackPoint[0].point1.x);
        buffer.push_back(trackPoint[0].point1.y);
        buffer.push_back(trackPoint[0].point1.z);





        buffer.push_back(trackPoint[trackPoint.size()-2].point3.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.z);

        buffer.push_back(trackPoint[0].point1.x);
        buffer.push_back(trackPoint[0].point1.y);
        buffer.push_back(trackPoint[0].point1.z);

        buffer.push_back(trackPoint[0].point3.x);
        buffer.push_back(trackPoint[0].point3.y);
        buffer.push_back(trackPoint[0].point3.z);


        //left

        buffer.push_back(trackPoint[trackPoint.size()-2].point4.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.z);


        buffer.push_back(trackPoint[trackPoint.size()-2].point3.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.z);

        buffer.push_back(trackPoint[0].point3.x);
        buffer.push_back(trackPoint[0].point3.y);
        buffer.push_back(trackPoint[0].point3.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point4.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.z);

        buffer.push_back(trackPoint[0].point3.x);
        buffer.push_back(trackPoint[0].point3.y);
        buffer.push_back(trackPoint[0].point3.z);

        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);


        //right

        buffer.push_back(trackPoint[trackPoint.size()-2].point1.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point2.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.z);

        buffer.push_back(trackPoint[0].point2.x);
        buffer.push_back(trackPoint[0].point2.y);
        buffer.push_back(trackPoint[0].point2.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point1.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.z);

        buffer.push_back(trackPoint[0].point2.x);
        buffer.push_back(trackPoint[0].point2.y);
        buffer.push_back(trackPoint[0].point2.z);

        buffer.push_back(trackPoint[0].point1.x);
        buffer.push_back(trackPoint[0].point1.y);
        buffer.push_back(trackPoint[0].point1.z);









        //bottom
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point4.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.z);

        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point2.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.z);


        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);

        buffer.push_back(trackPoint[0].point2.x);
        buffer.push_back(trackPoint[0].point2.y);
        buffer.push_back(trackPoint[0].point2.z);

    }



    //count normals
    for (int i=0; i<buffer.size()-18; i = i+18){

        float p1_x = buffer[i];
        float p1_y = buffer[i+1];
        float p1_z = buffer[i+2];
        float p2_x = buffer[i+3];
        float p2_y = buffer[i+4];
        float p2_z = buffer[i+5];
        float p3_x = buffer[i+6];
        float p3_y = buffer[i+7];
        float p3_z = buffer[i+8];

        // U = p2 - p1
        float u_x = p2_x - p1_x;
        float u_y = p2_y - p1_y;
        float u_z = p2_z - p1_z;

        // V = p3 - p1
        float v_x = p3_x - p1_x;
        float v_y = p3_y - p1_y;
        float v_z = p3_z - p1_z;

        // N = U x V

        float n_x = u_y*v_z - u_z*v_y;
        float n_y = u_z*v_x - u_x*v_z;
        float n_z = u_x*v_y - u_y*v_x;


        for (int j=0; j<6; j++){
            normal.push_back(n_x);
            normal.push_back(n_y);
            normal.push_back(n_z);
            normal.push_back(1.0f);
        }

    }


    //count average of normals
    for (int i=0; i<normal.size()-192-192; i = i+192){
        float current[192];
        float next[192];
        for (int j=0; j<192; j++){
            current[j]  = normal[i+j];
            next[j] = normal[i+j+192];
        }


        for (int j=0; j<192; j=j+4){
            vec3 curr,nex;
            curr = vec3(current[j], current[j+1],current[j+2]);
            nex = vec3(next[j], next[j+1],next[j+2]);

            vec3 norm = normalize(curr+nex);
            current[j] = next[j] = norm.x;
            current[j+1] = next[j+1] = norm.y;
            current[j+2] = next[j+2] = norm.z;
        }

        for (int j=0; j<192; j++){
            normal[i+j] = current[j];
            normal[i+j+192] = next[j];
        }






    }







    this->bufferCount = buffer.size()/3;


    cout<<"num of points: "<<trackPoint.size()<<endl;
    cout<<"num of points - 1 : "<<trackPoint.size() - 1<<endl;

    cout<<"size of buffer: "<<buffer.size()<<endl;
    cout<<"size of buffer/3 (points): "<<buffer.size()/3.0f<<endl;
    cout<<"size of buffer/9 (triangles): "<<buffer.size()/9.0f<<endl;
    cout<<"size of buffer/72 (sections): "<<buffer.size()/72.0f<<endl;




    //textture coords

    float array[(buffer.size()/3)*2];
    cout<<(buffer.size()/3)*2<<endl;

    for (int i=0; i < (buffer.size()/3)*2; i=i+12){ //6 points

        array[i] = 0;
        array[i+1] = 0;

        array[i+2] = 1;
        array[i+3] = 0;

        array[i+4] = 1;
        array[i+5] = 1;

        array[i+6] = 0;
        array[i+7] = 0;

        array[i+8] = 1;
        array[i+9] = 1;

        array[i+10] = 0;
        array[i+11] = 1;


    }

    this->textureCoord = array;





    lodepng::decode(this->texture, this->width, this->height, "images/ground.png");



    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


void Track::draw(mat4 V){

    mat4 M=mat4(1.0f);

    M = mat4(1.0f);
    glLoadMatrixf(glm::value_ptr(V*M));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)texture.data());


    float specReflection3[] = { 0.8f, 0.8f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specReflection3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, specReflection3);

    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 120);



    glNormalPointer(GL_FLOAT,sizeof(float)*4,&(this->normal[0]));
    glTexCoordPointer( 2, GL_FLOAT, 0, this->textureCoord);
    glVertexPointer(3,GL_FLOAT,0, &(this->buffer[0]));


    glDrawArrays(GL_TRIANGLES,0, this->bufferCount);


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    float specReflection2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specReflection2);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);


    //draw columns
    glColor3d(1.0f, 0.0, 0.0);

    for (int i=1; i<trackPoint.size()-5; i+=5){
        M = mat4(1.0f);
        float x = (trackPoint[i].point2.x + trackPoint[i].point4.x)/2.0f;
        float y = trackPoint[i].point2.y - 30.0f;
        float z = (trackPoint[i].point2.z + trackPoint[i].point4.z)/2.0f;;
        M = translate(M,  vec3(x,y,z));
        M = scale(M, vec3(0.3f, 30.0f, 0.3f));
        glLoadMatrixf(glm::value_ptr(V*M));
        Models::cube.drawSolid();
        /*

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3,GL_FLOAT,0, &(this->columnBuffer[0]));
        glNormalPointer(GL_FLOAT,0, &(this->columnNormal[0]));


        glDrawArrays(GL_QUADS,0, this->columnCount);


        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        */
    }





    /*

    M = mat4(1.0f);
    M = translate(M, vec3( 4,0,4));
    glLoadMatrixf(glm::value_ptr(V*M));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3,GL_FLOAT,0, &(this->columnBuffer[0]));
    glNormalPointer(GL_FLOAT,0, &(this->columnNormal[0]));


    glDrawArrays(GL_QUADS,0, this->columnCount);


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    */

}








void Track::generateColumn(){


        int numOfSegments = 10;

        vector<vec3> normals;

        columnCount = numOfSegments * 16;

        for (int i=0; i<numOfSegments; i++)
        {
            vec3 p1 = vec3(0, 0+i, 0);
            vec3 p2 = vec3(1, 0+i, 0);
            vec3 p3 = vec3(1, 0+i, 1);
            vec3 p4 = vec3(0, 0+i, 1);

            vec3 np1 = vec3(0, 1+i, 0);
            vec3 np2 = vec3(1, 1+i, 0);
            vec3 np3 = vec3(1, 1+i, 1);
            vec3 np4 = vec3(0, 1+i, 1);

            //FRONT
            //p1
            columnBuffer.push_back(p1.x);
            columnBuffer.push_back(p1.y);
            columnBuffer.push_back(p1.z);
            //p2
            columnBuffer.push_back(p2.x);
            columnBuffer.push_back(p2.y);
            columnBuffer.push_back(p2.z);
            //np2
            columnBuffer.push_back(np2.x);
            columnBuffer.push_back(np2.y);
            columnBuffer.push_back(np2.z);
            //np1
            columnBuffer.push_back(np1.x);
            columnBuffer.push_back(np1.y);
            columnBuffer.push_back(np1.z);

            //RIGHT
            //p2
            columnBuffer.push_back(p2.x);
            columnBuffer.push_back(p2.y);
            columnBuffer.push_back(p2.z);
            //p3
            columnBuffer.push_back(p3.x);
            columnBuffer.push_back(p3.y);
            columnBuffer.push_back(p3.z);
            //np3
            columnBuffer.push_back(np3.x);
            columnBuffer.push_back(np3.y);
            columnBuffer.push_back(np3.z);
            //np2
            columnBuffer.push_back(np2.x);
            columnBuffer.push_back(np2.y);
            columnBuffer.push_back(np2.z);

            //BACK
            //p3
            columnBuffer.push_back(p3.x);
            columnBuffer.push_back(p3.y);
            columnBuffer.push_back(p3.z);
            //pp4
            columnBuffer.push_back(p4.x);
            columnBuffer.push_back(p4.y);
            columnBuffer.push_back(p4.z);
            //np4
            columnBuffer.push_back(np4.x);
            columnBuffer.push_back(np4.y);
            columnBuffer.push_back(np4.z);
            //np3
            columnBuffer.push_back(np3.x);
            columnBuffer.push_back(np3.y);
            columnBuffer.push_back(np3.z);

            //LEFT
            //p4
            columnBuffer.push_back(p4.x);
            columnBuffer.push_back(p4.y);
            columnBuffer.push_back(p4.z);
            //p1
            columnBuffer.push_back(p1.x);
            columnBuffer.push_back(p1.y);
            columnBuffer.push_back(p1.z);
            //np1
            columnBuffer.push_back(np1.x);
            columnBuffer.push_back(np1.y);
            columnBuffer.push_back(np1.z);
            //np4
            columnBuffer.push_back(np4.x);
            columnBuffer.push_back(np4.y);
            columnBuffer.push_back(np4.z);




            //count normals:

            vec3 frontNormal = calcNormal(p1,p2,np2);
            vec3 rightNormal = calcNormal(p2,p3,np3);
            vec3 backNormal = calcNormal(p3,p4,np4);
            vec3 leftNormal = calcNormal(p4,p1,np1);

            for(int j=0; j<4; j++) {
                normals.push_back(frontNormal);
            }
            for(int j=0; j<4; j++) {
                normals.push_back(rightNormal);
            }
            for(int j=0; j<4; j++) {
                normals.push_back(backNormal);
            }
            for(int j=0; j<4; j++) {
                normals.push_back(leftNormal);
            }



            /*
            for(int j=0; j<4; j++){
                columnNormal.push_back(frontNormal.x);
                columnNormal.push_back(frontNormal.y);
                columnNormal.push_back(frontNormal.z);
                columnNormal.push_back(1.0f);

                columnNormal.push_back(rightNormal.x);
                columnNormal.push_back(rightNormal.y);
                columnNormal.push_back(rightNormal.z);
                columnNormal.push_back(1.0f);

                columnNormal.push_back(backNormal.x);
                columnNormal.push_back(backNormal.y);
                columnNormal.push_back(backNormal.z);
                columnNormal.push_back(1.0f);

                columnNormal.push_back(leftNormal.x);
                columnNormal.push_back(leftNormal.y);
                columnNormal.push_back(leftNormal.z);
                columnNormal.push_back(1.0f);

            }
            */



        }


        //count average normals and push them to buffor

    for(int i=1; i<numOfSegments-1; i++){

        vec3 p1normal;
        vec3 p2normal;
        vec3 p3normal;
        vec3 p4normal;

        p1normal += normals[i*16] + normals[i*16-13] + normals[i*16-2] + normals[i*16 + 13];
        p2normal += normals[i*16+1] + normals[i*16 - 15];
        p3normal += normals[i*16+2] + normals[i*16+16+2] + normals[i*16 +15+2] + normals[i*16+31+2];
        p4normal += normals[i*16+3] + normals[i*16+16+3] + normals[i*16 +15+3] + normals[i*16+31+3];

        normals[i*16] = normals[i*16-13] = normals[i*16-2] = normals[i*16 + 13] = normalize(p1normal);
        //normals[i*16+1] = normals[i*16+16+1] =normals[i*16 +15+1] = normals[i*16+31+1] =   normalize(p2normal);
        //normals[i*16+2] = normals[i*16+16+2] = normals[i*16 +15+2] = normals[i*16+31+2] =  normalize(p3normal);
        //normals[i*16+3] = normals[i*16+16+3] = normals[i*16 +15+3] = normals[i*16+31+3] = normalize(p4normal);
    }

    for(int i=0; i<normals.size(); i++){
        columnNormal.push_back(normals[i].x);
        columnNormal.push_back(normals[i].y);
        columnNormal.push_back(normals[i].z);
        columnNormal.push_back(1.0f);
    }


    cout<<"number of vertexes: "<<this->columnBuffer.size()/3.0f<<endl;
    cout<<"number of normals: "<<this->columnNormal.size()/4.0f<<endl;




};