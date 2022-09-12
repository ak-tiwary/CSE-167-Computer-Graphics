#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "getting_started.hpp"
#include "shader_s.hpp"
#include "stb_image.h"

using std::cout;
using std::endl;

namespace textures
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
}

int main()
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
    GLFWwindow *window = glfwCreateWindow(textures::SCR_WIDTH, textures::SCR_HEIGHT, "Hello Rectangle", NULL, NULL);

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
    Shader ourshader = Shader("../src/learnopengl/getting_started/shaders_vertex_shader.vs", "../src/learnopengl/getting_started/shaders_frag_shader.fs");

    // DATA: Vertices and Indices
    //-----------------

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };

    float texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f};

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2, // first Triangle  // second Triangle
    };

    // load texture

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../data/container.jpeg", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // we can now generate a teture using the loaded image data

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // free image data after generating texture object
    stbi_image_free(data);

    // VAO, VBO, and EBO
    //  ----------------------------

    // create and obtain ID
    //--------------------
    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO and Buffers
    //------------------
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set VertexAttribArrayPointer and enable VertexAttribArray
    //--------------------------

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind GL_ARRAY_BUFFER but NOT!!! GL_ELEMENT_ARRAY_BUFFER
    // ---------------
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
        ourshader.use();

        // float timeValue = glfwGetTime();
        //  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        // glUseProgram(shaderProgram);
        //  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Bind VAO and DrawElements
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Bind VAO to 0
        glBindVertexArray(0);

        // Swap Buffers and Poll Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // deallocate buffers, vertex array, program
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);

    // terminate GLFW
    glfwTerminate();

    return 0;
}