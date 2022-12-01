#include "include/glad.h"
#include "include/glfw3.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <sstream>

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Window [" << window << "]" << " now closing." << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static std::string GetGLSLShaderCode(char* file_name){
    std::ifstream file(file_name);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

class ProgramClass {
public:
    float background_color[3] = {0.0, 0.0, 0.0};
    double prev_frametime;
    int current_color, next_color;
    GLFWwindow* window;

    ProgramClass(GLFWwindow* win){ //constructor
        window = win;
        prev_frametime = 0;
        current_color = 0;
        next_color = 1;
    }

    static float RandFloat(float max_value){
        return rand() / (RAND_MAX / max_value);
    }

    void RGBColor(float* color, int speed){

        if (color[current_color] == 0){
            current_color = next_color;
            next_color = next_color + 1;

            if (next_color == 3){
                next_color = 0;
            }
        }

       if (color[next_color] < 255.0f - speed){
           color[next_color] = color[next_color] + (speed + 1);
       }
       else{
           color[current_color] = color[current_color] - (1 + speed);
       }
    }

    void DrawTriangle(){
        // I'm going to use GPU buffers for now, although I'll probably try a simpler method later
        float triangle_vertices[6] = {
                 0.0f,  0.5f,
                 0.5f, -0.5f,
                -0.5f, -0.5f
        };

        GLuint VertBuffObject;

        glGenBuffers(1, &VertBuffObject); //Create one buffer, with a gl pointer using p_VertBugObj.
        glBindBuffer(GL_ARRAY_BUFFER, VertBuffObject); // This causes the buffer object to be the current GL ARRAY BUFFER, see line 70

        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW); // Instead of referencing p_VertBufferObj

    }

    void Main(){
        while (!glfwWindowShouldClose(window)){
            int width, height, framerate;

            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            RGBColor(background_color, 5);

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