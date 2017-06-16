#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "enum/directions.h"
#include "cube/cube.h"
#include "player/player.h"
#include "element/ground.h"
#include "element/skybox.h"
#include "element/track.h"
#include "element/cart.h"
#include "element/light.h"



#include <stdio.h>
#include "loader/objLoader.h"

#include "imgLoader/lodepng.h"

#include "enum/directions.h"

using namespace glm;
using namespace std;

float windowX = 800.0f;
float windowY = 600.0f;

Player player;
Skybox skybox;
Ground ground;
Track track;
Cart cart;
Light light;

Drawable suzanne((char*)"loader/suzanne.obj");



GLuint tex;// uchwyt



float deltaTime;
double currentTime;
double lastTime;







void mouse_callback(GLFWwindow* window, double mouseX, double mouseY) {
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
        if (key==GLFW_KEY_SPACE)
            player.goToTrack(track);

        if (key==GLFW_KEY_ENTER)
            player.leaveTrack();
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
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.7,0.7,0.7,1);
    glMatrixMode(GL_MODELVIEW);

    skybox.loadTextures();
    track.load();
    light.init();
    ground.loadTextures();

// Somewhere in the initialization part of your program…
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    float specReflection[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specReflection);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 96);



}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysujący obraz******************l
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)

    mat4 V = player.getCameraMatrix();

    mat4 P = perspective(50*PI/180, windowX/windowY,0.1f,300.0f);







    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));
    glMatrixMode(GL_MODELVIEW);



    mat4 M = mat4(1.0f);


    //light
    light.draw(V);


    //set position of main light
    float pos[] = {200.0f, 200.0f, 200.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    //ground

    ground.draw(V);


    //monkey
    glColor3d(0.4,0.0,0.8);
    suzanne.draw(V);

    //track
    glColor3d(1.0, 1.0, 0.0);
    track.draw(V);



    //cart
    glColor3d(0.0f, 1.0f, 1.0f);
    cart.update(deltaTime);
    cart.draw(V, track);

    if (player.isOnTrack)
        player.moveOnTrack(cart);

    //skybox

    M=mat4(1.0f);
    M = translate(M, player.getPosition());
    M = scale(M, vec3(150,150,150));
    glLoadMatrixf(glm::value_ptr(V*M));
    skybox.draw();

    //end of draw
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