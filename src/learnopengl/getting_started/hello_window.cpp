#include <glad/glad.h> //glad should be included before glfw
#include <GLFW/glfw3.h>
#include <iostream>
#include "getting_started.hpp"

using std::cout;
using std::endl;

int main2()
{

    // instantiate the glfw window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // for OSX only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // cout << "Here " << endl;

    // create a window object
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize GLAD before calling OpenGL Functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // telling OpenGL about the rendering window size
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // rendering loop
    while (!glfwWindowShouldClose(window))
    {

        process_input(window);

        // here we render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // delete all GLFW resources allocated
    glfwTerminate();

    // rendering loop exited after user closes window
    cout << "Exiting..." << endl;
    return 0;
}
