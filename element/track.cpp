//
// Created by matt on 13.06.17.
//

#include "track.h"

using namespace std;

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

        buffer.push_back(trackPoint[i].point1.x);
        buffer.push_back(trackPoint[i].point1.y);
        buffer.push_back(trackPoint[i].point1.z);

        buffer.push_back(trackPoint[i+1].point1.x);
        buffer.push_back(trackPoint[i+1].point1.y);
        buffer.push_back(trackPoint[i+1].point1.z);

        buffer.push_back(trackPoint[i].point3.x);
        buffer.push_back(trackPoint[i].point3.y);
        buffer.push_back(trackPoint[i].point3.z);



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

        buffer.push_back(trackPoint[i].point3.x);
        buffer.push_back(trackPoint[i].point3.y);
        buffer.push_back(trackPoint[i].point3.z);

        buffer.push_back(trackPoint[i+1].point3.x);
        buffer.push_back(trackPoint[i+1].point3.y);
        buffer.push_back(trackPoint[i+1].point3.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);

        buffer.push_back(trackPoint[i].point3.x);
        buffer.push_back(trackPoint[i].point3.y);
        buffer.push_back(trackPoint[i].point3.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);

        buffer.push_back(trackPoint[i].point4.x);
        buffer.push_back(trackPoint[i].point4.y);
        buffer.push_back(trackPoint[i].point4.z);

        //right

        buffer.push_back(trackPoint[i].point1.x);
        buffer.push_back(trackPoint[i].point1.y);
        buffer.push_back(trackPoint[i].point1.z);

        buffer.push_back(trackPoint[i+1].point1.x);
        buffer.push_back(trackPoint[i+1].point1.y);
        buffer.push_back(trackPoint[i+1].point1.z);

        buffer.push_back(trackPoint[i+1].point2.x);
        buffer.push_back(trackPoint[i+1].point2.y);
        buffer.push_back(trackPoint[i+1].point2.z);


        buffer.push_back(trackPoint[i].point1.x);
        buffer.push_back(trackPoint[i].point1.y);
        buffer.push_back(trackPoint[i].point1.z);

        buffer.push_back(trackPoint[i+1].point2.x);
        buffer.push_back(trackPoint[i+1].point2.y);
        buffer.push_back(trackPoint[i+1].point2.z);

        buffer.push_back(trackPoint[i].point2.x);
        buffer.push_back(trackPoint[i].point2.y);
        buffer.push_back(trackPoint[i].point2.z);


        //bottom

        buffer.push_back(trackPoint[i+1].point2.x);
        buffer.push_back(trackPoint[i+1].point2.y);
        buffer.push_back(trackPoint[i+1].point2.z);

        buffer.push_back(trackPoint[i].point2.x);
        buffer.push_back(trackPoint[i].point2.y);
        buffer.push_back(trackPoint[i].point2.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);

        buffer.push_back(trackPoint[i].point2.x);
        buffer.push_back(trackPoint[i].point2.y);
        buffer.push_back(trackPoint[i].point2.z);

        buffer.push_back(trackPoint[i+1].point4.x);
        buffer.push_back(trackPoint[i+1].point4.y);
        buffer.push_back(trackPoint[i+1].point4.z);

        buffer.push_back(trackPoint[i].point4.x);
        buffer.push_back(trackPoint[i].point4.y);
        buffer.push_back(trackPoint[i].point4.z);

    }


    //last segment
    {
        //top

        buffer.push_back(trackPoint[trackPoint.size()-2].point1.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.z);

        buffer.push_back(trackPoint[0].point1.x);
        buffer.push_back(trackPoint[0].point1.y);
        buffer.push_back(trackPoint[0].point1.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point3.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.z);



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

        buffer.push_back(trackPoint[trackPoint.size()-2].point3.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.z);

        buffer.push_back(trackPoint[0].point3.x);
        buffer.push_back(trackPoint[0].point3.y);
        buffer.push_back(trackPoint[0].point3.z);

        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point3.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point3.z);

        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point4.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.z);

        //right

        buffer.push_back(trackPoint[trackPoint.size()-2].point1.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.z);

        buffer.push_back(trackPoint[0].point1.x);
        buffer.push_back(trackPoint[0].point1.y);
        buffer.push_back(trackPoint[0].point1.z);

        buffer.push_back(trackPoint[0].point2.x);
        buffer.push_back(trackPoint[0].point2.y);
        buffer.push_back(trackPoint[0].point2.z);


        buffer.push_back(trackPoint[trackPoint.size()-2].point1.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point1.z);

        buffer.push_back(trackPoint[0].point2.x);
        buffer.push_back(trackPoint[0].point2.y);
        buffer.push_back(trackPoint[0].point2.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point2.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.z);


        //bottom

        buffer.push_back(trackPoint[0].point2.x);
        buffer.push_back(trackPoint[0].point2.y);
        buffer.push_back(trackPoint[0].point2.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point2.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.z);

        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point2.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point2.z);

        buffer.push_back(trackPoint[0].point4.x);
        buffer.push_back(trackPoint[0].point4.y);
        buffer.push_back(trackPoint[0].point4.z);

        buffer.push_back(trackPoint[trackPoint.size()-2].point4.x);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.y);
        buffer.push_back(trackPoint[trackPoint.size()-2].point4.z);
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
    for (int i=0; i<normal.size(); i = i+48){
        float current[24];
        float next[24];
        for (int j=0; j<24; j++){
            current[j]  = normal[i+j];
            next[j] = normal[i+j+24];
        }

    }







    this->bufferCount = buffer.size()/3;


    cout<<"num of points: "<<trackPoint.size()<<endl;
    cout<<"num of points - 1 : "<<trackPoint.size() - 1<<endl;

    cout<<"size of buffer: "<<buffer.size()<<endl;
    cout<<"size of buffer/3 (points): "<<buffer.size()/3.0f<<endl;
    cout<<"size of buffer/9 (triangles): "<<buffer.size()/9.0f<<endl;
    cout<<"size of buffer/72 (sections): "<<buffer.size()/72.0f<<endl;
}


void Track::draw(mat4 V){


    mat4 M=mat4(1.0f);

    M = mat4(1.0f);
    glLoadMatrixf(glm::value_ptr(V*M));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glNormalPointer(GL_FLOAT,sizeof(float)*4,&(this->normal[0]));

    glVertexPointer(3,GL_FLOAT,0, &(this->buffer[0]));
    glDrawArrays(GL_TRIANGLES,0, this->bufferCount);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);



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
    }

 /*
    //draw at center
    glColor3d(0.0f, 0.0f, 1.0f);

    for (int i=1; i<trackPoint.size()-1; i++){
        M = mat4(1.0f);
        M = translate(M, trackPoint[i].center);
        M = scale(M, vec3(0.1f, 0.1f, 0.1f));
        glLoadMatrixf(glm::value_ptr(V*M));
        Models::cube.drawSolid();
    }


*/
}
