#include "stdafx.h"
#include "headers/GLFunctions.h"
#include "headers/GLShader.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    setupGLFW();
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferCheck);

    initGLAD(); // load all OpenGL function pointers glad

    // build and compile our shader program
    Shader glShader("shaders/shader.vs", "shaders/shader.fs");

    float vertices[] = {
        // first triangle
        -.5f, -.5f, .0f, 0.f, 0.f, .0f,
         .5f, -.5f, .0f, .0f, 1.f, .0f,
        -.5f, .5f, .0f,  .0f, .0f, 1.f,
        // second triangle
        .5f, -.5f, .0f, .0f, 1.f, .0f,
        .5f, .5f, .0f, 1.f, .0f, .0f,
        -.5f, .5f,  .0f, .0f, .0f, 1.f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    // put vertice array in a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE//GL_FILL solids
    // render loop    
    while (!glfwWindowShouldClose(window))
    {
        glShader.use();
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render shape
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 6); 
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}