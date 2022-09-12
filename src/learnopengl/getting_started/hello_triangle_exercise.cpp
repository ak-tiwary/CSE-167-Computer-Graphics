#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "getting_started.hpp"

using std::cout;
using std::endl;

namespace hello_triangle_exercise
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f,0.2f, 1.0f);\n"
                                       "}\0";

    const char *fragmentShaderSource2 = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    FragColor = vec4(1.0f, 1.0f,0.0f, 1.0f);\n"
                                        "}\0";
}

int main_triangle_ex()
{
    // Initialize GLFW and OpenGL version
    // -------------------------------------
    //
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Create GLFW window and check for failure
    // -------------------------------------
    //
    GLFWwindow *window = glfwCreateWindow(hello_triangle_exercise::SCR_WIDTH, hello_triangle_exercise::SCR_HEIGHT, "Hello Rectangle", NULL, NULL);

    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Test if glad works
    // -------------------------------------
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize glad" << endl;
        return -1;
    }

    // SHADERS:
    // -------------------------------------
    // vertex shader
    // ---------------
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &hello_triangle_exercise::vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    // unsigned int vertexShader2 = glCreateShader(GL_VERTEX_SHADER);

    /*glShaderSource(vertexShader2, 1, &hello_triangle_exercise::vertexShaderSource, NULL);
    glCompileShader(vertexShader2);

    glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader2, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX2::COMPILATION_FAILED\n"
             << infoLog << endl;
    }*/

    // fragment shader
    // --------------
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &hello_triangle_exercise::fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader2, 1, &hello_triangle_exercise::fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
             << infoLog << endl;
    }
    // link shaders by creating a shader program
    // ------------

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER2::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    // delete shader
    // -------------

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader2);

    // DATA: Vertices and Indices
    //-----------------

    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.75f, 0.0f, 0.0f,
        0.0f, 0.88f, 0.0f};

    float vertices2[] = {
        0.0f, 0.0f, 0.0f,
        -0.75f, 0.0f, 0.0f,
        0.0f, -0.88f, 0.0f};

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2, // first Triangle
    };

    unsigned int indices2[] = {
        0, 1, 2};
    // VAO, VBO, and EBO
    //  ----------------------------

    // create and obtain ID
    //--------------------
    unsigned int VAOs[2], VBOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);

    // Bind VAO, bind buffers, bind data
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // second triangle

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // to draw in wireframe polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // alt: GL_FILL

    // rendering loop
    // -------------------------------------
    //
    while (!glfwWindowShouldClose(window))
    {

        // Process Inputs
        process_input(window);

        // render

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use ShaderProgram

        glUseProgram(shaderProgram);

        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram2);

        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Swap Buffers and Poll Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // deallocate buffers, vertex array, program

    // terminate GLFW
    glfwTerminate();

    return 0;
}