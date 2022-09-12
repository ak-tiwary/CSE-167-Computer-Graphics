#ifndef GETTING_STARTED
#define GETTING_STARTED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
void CheckOpenGLError(const char *stmt, const char *fname, int line);

#ifdef _DEBUG
#define GL_CHECK(stmt)                               \
    do                                               \
    {                                                \
        stmt;                                        \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

#endif

// Use it like this :

//     GL_CHECK(glBindTexture2D(GL_TEXTURE_2D, id));
// If OpenGL function returns variable, then remember to declare it outside of GL_CHECK :

//     const char *vendor;
// GL_CHECK(vendor = glGetString(GL_VENDOR));
