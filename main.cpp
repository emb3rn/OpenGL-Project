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
    float backgroundColor[3] = {255.0, 0.0, 0.0};

    double prev_frametime;
    GLFWwindow* window;

    ProgramClass(GLFWwindow* win){ //constructor
        window = win;
        prev_frametime = 0;
    }

    static float RandFloat(float max_value){
        return rand() / (RAND_MAX / max_value);
    }


    int current_color = 0;
    int next_color = 1;
    void RainbowCycle(float* color, float speed) {
        if (color[next_color] <= 255 - speed){ //if loop because it repeats every frame
            color[next_color] = color[next_color] + speed;
        }
        else{
            if (color[current_color] > 0){
                color[current_color] = color[current_color] - speed;
            }
            else{
                current_color = next_color;
                if (next_color + 1 > 3){
                    next_color = 0;
                }
                else{
                    next_color = current_color + 1;
                }
            }
        }
    }

    void Main(){
        while (!glfwWindowShouldClose(window)){
            int width, height, framerate;

            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            RainbowCycle(backgroundColor, 5);
            for (int i = 0; i < 3; ++i) {
                std::cout << backgroundColor[i] << std::endl;
            }
            glClearColor(backgroundColor[0]/255, backgroundColor[1]/255, backgroundColor[2]/255, 1);
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