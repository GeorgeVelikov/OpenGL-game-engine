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

    float vertices[] = {
        // positions      //texture coords
        -.5f, -.5f, .0f,  0.f, 0.f,
         .5f, -.5f, .0f,  1.f, 0.f,
        -.5f,  .5f, .0f,  0.f, 1.f,
         .5f,  .5f, .0f,  1.f, 1.f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int textureTile;
    load2DImageAsTexture(&textureTile, 1, "textures/tile.png");

    glShader.use();
    glShader.setInt("texture1", 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE//GL_FILL solids
    // render loop    
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on tex units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureTile);

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(.2f, -.2f, .0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(.7f, -.9f, .5f));

        // get marix uniform loc
        glShader.use();
        unsigned int transformLoc = glGetUniformLocation(glShader.id, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // render shape
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
        // swap buffers and poll for io events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate and clearing all previously allocated resources.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}