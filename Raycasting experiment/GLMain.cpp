#include "stdafx.h"
#include "headers/GLMain.h"


int main()
{

    mouse = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    time  = {              0.f,               0.f };

    setupGLFW();
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferCheck);
    glfwSetCursorPosCallback(window, mouseCallback);
    
    // load all OpenGL function pointers for glad
    setupGLAD();

    // build and compile our shader program
    Shader glShader("shaders/shader.vs", "shaders/shader.fs");
    glEnable(GL_DEPTH_TEST);

    // vertex buffer, vertex array and element buffer
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // put vertice array in a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // create shapes by the vertex id 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // textures
    unsigned int textureWood;
    load2DImageAsTexture(&textureWood, 1, "textures/wood.png");

    glShader.use();
    glShader.setInt("texture1", 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE//GL_FILL solids
    // render loop    

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on tex units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureWood);

        // get marix uniform loc
        glShader.use();

        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // pass transformation matrices to the shader
        glShader.setMat4("projection", projection);
        glShader.setMat4("view", view);

        // render shape
        for (unsigned int i = 0; i <= 10; i++) {
            glBindVertexArray(VAO);
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, positions[i]);
            float angle = float(glfwGetTime()) * 25.f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.f, .3f, .5f));
            glShader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

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