#include "stdafx.h"
#include "headers/GLMain.h"


int main()
{
    mouse = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    time  = { 0.f, 0.f, 0.f};

    std::vector<std::string> map;
    map.push_back("################################");
    map.push_back("#.......#.......##.............#");
    map.push_back("#.......#..##.....#....#.#.#...#");
    map.push_back("#..#############...#...........#");
    map.push_back("#....#..............#...#.#....#");
    map.push_back("#....#....######...............#");
    map.push_back("#....#...##..........#####.....#");
    map.push_back("####.######.....##.............#");
    map.push_back("#....#....##.....##...#####....#");
    map.push_back("#..........##.....##.......##..#");
    map.push_back("#...#.......##....##......#....#");
    map.push_back("#...#........##..##.......#.#..#");
    map.push_back("#...#.........###....##...#....#");
    map.push_back("#...#####..........#....###..#.#");
    map.push_back("#.............##...............#");
    map.push_back("################################");

    // save 3d world
    for (int x = 0; x < map.size(); x++) {
        for (int z = 0; z < map[x].size(); z++) {
            if (map[x][z] == '#')
                positions.push_back(glm::vec3(EDGE_SIZE * 2 * x, EDGE_SIZE * 2, EDGE_SIZE * 2 * z));
            else if(map[x][z] == '.')
                positions.push_back(glm::vec3(EDGE_SIZE * 2 * x, 0.f, EDGE_SIZE * 2 * z));
            else continue;
        }
    }

    setupGLFW();
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferCheck);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
   
    // render loop    
    while (!glfwWindowShouldClose(window))
    {
        std::cout << 1 / time.delta << '\n';
        time.current = glfwGetTime();
        time.delta = time.current - time.past;
        time.past = time.current;

        // input
        keyboardCallback(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on tex units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureWood);

        // get marix uniform loc
        glShader.use();        

        // pass transformation matrices to the shader
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glShader.setMat4("projection", projection);

        glm::mat4 view = camera.getViewMatrix();
        glShader.setMat4("view", view);

        // render shape
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < positions.size(); i++) {
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, positions[i]);
            float angle = 0;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.f, .3f, .5f));
            glShader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        camera.obeyGravity(time.delta, EDGE_SIZE);

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


void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    mouseLocation offset;
    offset  = { float(xpos - mouse.X), float(ypos - mouse.Y) };
    mouse   = { float(xpos)          ,           float(ypos) };
    camera.processMouseMovement(offset.X, offset.Y);
}

void keyboardCallback(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, time.delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, time.delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, time.delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, time.delta);
}