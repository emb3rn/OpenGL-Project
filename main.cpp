#include "include/glad.h"
#include "include/glfw3.h"
#include <iostream>



int main(){
    GLFWwindow* window = glfwCreateWindow( 640, 480, "Title", NULL, NULL );
    if( !window ){
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    glfwSetKeyCallback( window, key_callback );
    glfwMakeContextCurrent( window );
    gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress );

    while( !glfwWindowShouldClose( window ) ){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();
    return 0;
}

void error_callback( int error, const char* description ){
    fprintf( stderr, "Error: %s\n", description );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( window, GLFW_TRUE );
    }
}