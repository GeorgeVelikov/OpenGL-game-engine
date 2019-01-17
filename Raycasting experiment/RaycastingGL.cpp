#include "stdafx.h"
#include <iostream>
#include <glew.h>
#include <glfw3.h>

void getBufferSize(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, getBufferSize);

    glfwMakeContextCurrent(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    while (!glfwWindowShouldClose(window)) { // game loop
        glfwSwapBuffers(window);
        glfwPollEvents();
        processInput(window);
    }
}