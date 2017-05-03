#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>


#include "enum/directions.h"
#include "cube/cube.h"
#include "player/player.h"
#include "element/ground.h"


#include <stdio.h>
#include "loader/objLoader.h"

#include "imgLoader/lodepng.h"

#include "enum/directions.h"

using namespace glm;
using namespace std;

float windowX = 800.0f;
float windowY = 600.0f;

Player player;

Drawable suzanne((char*)"loader/untitled.obj");



GLuint tex;// uchwyt



float deltaTime;
double currentTime;
double lastTime;




void mouse_callback(GLFWwindow* window, double mouseX, double mouseY)
{
    if (mouseX > windowX/2.0f)
        player.rotate(RIGHT,deltaTime);
    if (mouseX < windowX/2.0f)
        player.rotate(LEFT,deltaTime);
    if (mouseY < windowY/2.0f)
        player.rotate(UP,deltaTime);
    if (mouseY > windowY/2.0f)
        player.rotate(DOWN,deltaTime);
    glfwSetCursorPos(window, windowX/2.0f, windowY/2.0f);
}



void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mods){

    if(action == GLFW_PRESS){

        if (key == GLFW_KEY_ESCAPE)
            exit(0);
    }


    if (action == GLFW_REPEAT){
        switch (key){
            case GLFW_KEY_A:
            case GLFW_KEY_LEFT:
                player.move(LEFT,deltaTime);
                break;
            case GLFW_KEY_D:
            case GLFW_KEY_RIGHT:
                player.move(RIGHT,deltaTime);
                break;
            case GLFW_KEY_W:
            case GLFW_KEY_UP:
                player.move(FORWARD,deltaTime);
                break;
            case GLFW_KEY_S:
            case GLFW_KEY_DOWN:
                player.move(BACKWARD,deltaTime);
                break;
        }

    }
}


//Procedura obsługi błędów
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {

    glfwSetCursorPos(window, windowX/2.0f, windowY/2.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(window,key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);

    glClearColor(0.4,0.2,1,1);




    vector<unsigned char> image;
    unsigned width,height;
    unsigned error = lodepng::decode(image,width,height, "imgLoader/brick.png");

    GLuint tex;// uchwyt

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysujący obraz******************l
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)

    mat4 V = player.getCameraMatrix();

    mat4 P = perspective(50*PI/180, windowX/windowY,1.0f,50.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);

    glColor3d(1,0.4,0.3);

    suzanne.draw(V);


    Ground ground;
    ground.draw(V);
    glfwSwapBuffers(window);
}


int main() {
    std::cout << "Roller Coaster Demo start!" << std::endl;

    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno
    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów
    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }



    window = glfwCreateWindow(windowX, windowY,"RollerCoaster", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    GLenum err;
    if ((err=glewInit()) != GLEW_OK) { //Zainicjuj bibliotekę GLEW
        fprintf(stderr, "Nie można zainicjować GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window); //Operacje inicjujące


    lastTime = 0;



    //Główna pętla
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {
        currentTime = glfwGetTime();
        deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        drawScene(window);
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
    return 0;
}