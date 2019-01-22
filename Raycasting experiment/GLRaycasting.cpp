#include "stdafx.h"
#include <iostream>  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"

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

    // load all OpenGL function pointers for glad
    setupGLAD(); 

    // build and compile our shader program
    Shader glShader("shaders/shader.vs", "shaders/shader.fs");
    unsigned int tex1;


    float vertices[] = {
        // first triangle
        -.5f, -.5f, .0f, 0.f, 0.f, .0f, 0.f, 0.f,
         .5f, -.5f, .0f, .0f, 1.f, .0f, 1.f, .0f,
        -.5f, .5f, .0f,  .0f, .0f, 1.f, .0f, 1.f,
         .5f, .5f, .0f,  1.f, .0f, .0f, 1.f, 1.f
    };

    unsigned int indices[] = {
        0, 1, 2, // first triangle
        1, 2, 3 // second triangle
    };

    // vertex buffer, vertex array and element buffer
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // put vertice array in a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // create shapes by the vertex id 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    
    // set colour attribute pointers
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int textureTile;
    load2DImageAsTexture(&textureTile, 1, "textures/tile.png");

    glShader.use();
    glUniform1i(glGetUniformLocation(glShader.id, "texture1"), 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE//GL_FILL solids
    // render loop    
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureTile);

        // render shape
        glShader.use();
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}