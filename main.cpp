#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "cube/cube.h"
#include "player/player.h"
#include "element/ground.h"
#include "player/camera.h"

#include <stdio.h>
#include "loader/objLoader.h"


using namespace glm;
using namespace std;



Player player;
Ground ground;

Drawable suzanne((char*)"loader/untitled.obj");

void mouse_callback(GLFWwindow* window, double mouseX, double mouseY)
{
    //cout << "Mouse cursor is at position (" << mouseX << ", " << mouseY << endl;


}



void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mods){

    if (action == GLFW_RELEASE){
        switch (key){
            case GLFW_KEY_A:
                player.move(1.0f, 0,0);
                break;
            case GLFW_KEY_D:
                player.move(-1.0f, 0,0);
                break;
            case GLFW_KEY_W:
                player.move(0.0f, 0, 1.0f);
                break;
            case GLFW_KEY_S:
                player.move(0.0f, 0, -1.0f);
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


    glfwSetKeyCallback(window,key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glClearColor(0,1,1,1);


}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysujący obraz******************l
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)

    vec3 eye(player.posX, player.posY, player.posZ);
    vec3 look(player.lookX, player.lookY, player.lookZ);
    vec3 up(0,1,0);

    mat4 V = lookAt(
            eye,
            look,
            up
        );

    mat4 P = perspective(50*PI/180, 1.0f,1.0f,50.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);


    suzanne.draw(V);



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



    window = glfwCreateWindow(500, 500,"RollerCoaster", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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




    //Główna pętla
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {


        drawScene(window);
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
    return 0;
}