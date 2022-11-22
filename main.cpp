/*
 * 0 = 255 if current_one >= next one
 * 1 = 0
 * 2 = 0

 current_one = 0;
 next_one = 1;

 if currrent_one = 0:
    current_one = next_one;
    next_one = next_one + 1;

    if (next_one >= 3):
        next_one = 0;

 if next_one < 255:
    next_one = next_one + 1;
 else:
    current_one = current_one - 1;

 */

#include "include/glad.h"
#include "include/glfw3.h"
#include <iostream>
#include <cstdio>
#include <cmath>

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Window [" << window << "]" << " now closing." << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

class ProgramClass {
public:
    float background_color[3] = {0.0, 0.0, 0.0};
    double prev_frametime;
    GLFWwindow* window;

    int current_color = 0;
    int next_color = 1;

    ProgramClass(GLFWwindow* win){ //constructor
        window = win;
        prev_frametime = 0;
    }

    static float RandFloat(float max_value){
        return rand() / (RAND_MAX / max_value);
    }

    void RGBColor(float* color){

        if (color[current_color] == 0){
            current_color = next_color;
            next_color = next_color + 1;

            if (next_color == 3){
                next_color = 0;
            }
        }

       if (color[next_color] < 255.0f){
           color[next_color] = color[next_color] + 1;
       }
       else{
           color[current_color] = color[current_color] - 1;
       }
    }

    void Main(){
        while (!glfwWindowShouldClose(window)){
            int width, height, framerate;

            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            //RainbowCycle(background_color, 10);
            RGBColor(background_color);

            glClearColor(background_color[0] / 255, background_color[1] / 255, background_color[2] / 255, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            framerate = (1000/(glfwGetTime() - prev_frametime));
            prev_frametime = glfwGetTime();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main(){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {std::cout << "Init failed." << std::endl;}

    GLFWwindow* window = glfwCreateWindow(640, 480, "Voxel Renderer", NULL, NULL);
    if (!window) {std::cout << "Window creation failed" << std::endl;}

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetKeyCallback(window, key_callback);

    ProgramClass Program(window);
    Program.Main();
}