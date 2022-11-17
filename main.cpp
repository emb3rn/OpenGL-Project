#include "include/glad.h"
#include "include/glfw3.h"
#include <iostream>
#include <cstdio>
#include <cmath>

struct rgb_int{
    int order;
    bool checked = false;
};

class ProgramClass{
public:
    signed int backgroundColor[4] = {1, 0, 0, 255};
    int prevFrametime = 0;
    rgb_int* order;

};

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Window [" << window << "]" << " now closing." << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

float rand_number(float max_value){
    return rand() / (RAND_MAX / max_value);
}

float rgb_cycle(int* color){
    int order[7] = {1, 2, 1, 3, 2, 1, 3}; //1=r, 2=g, 3=b

    for (int i = 0; i < 7; ++i) {
        if (color[i] > 0){
            color[i] = color[i] + (0.1*speed);
        }
        else{

        }
    }
}

int main(){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {std::cout << "Init failed." << std::endl;}

    GLFWwindow* window = glfwCreateWindow(640, 480, "Voxel Renderer", NULL, NULL);
    if (!window) {std::cout << "Window creation failed" << std::endl;}

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetKeyCallback(window, key_callback);

    int prevFrametime = 0; //used for fps calc
    rgb_int* rgbOrder = new rgb_int[7];

    signed int backgroundColor[4] = {1, 0, 0, 255};

    while (!glfwWindowShouldClose(window)){
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(rand_number(255.0/255.0f), rand_number(255.0/255.0f), rand_number(255.0/255.0f), 1);
        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << "[fps]: " << 1000/(glfwGetTime() - prevFrametime) << std::endl;
        //std::cout << "[random color]: " << rand_number(255.0) << std::endl;

        prevFrametime = glfwGetTime();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}