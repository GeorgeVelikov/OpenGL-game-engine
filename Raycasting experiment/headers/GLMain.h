
#include <iostream>  
#include <math.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <glfw3.h>

#include "headers/GLFunctions.h"
#include "headers/GLShader.h"
#include "headers/GLCamera.h"

struct gameTime {
    float delta;
    float past;
    float current;
} time;
struct mouseLocation {
    float X;
    float Y;
} mouse;

Camera camera;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CUBE_SIZE 0.5f

float        cubeVertices[]  = {
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  0.0f, 0.0f,
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  1.0f, 0.0f,
    -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,  0.0f, 1.0f,
    CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,  1.0f, 1.0f,

    -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,  0.0f, 0.0f,
    CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,  1.0f, 0.0f,
    -CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,  0.0f, 1.0f,
    CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,  1.0f, 1.0f,

    -CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,  1.0f, 0.0f,
    -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,  1.0f, 1.0f,
    -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,  0.0f, 0.0f,
    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  0.0f, 1.0f,

    CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,  1.0f, 0.0f,
    CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,  1.0f, 1.0f,
    CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,  0.0f, 0.0f,
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  0.0f, 1.0f,

    -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  0.0f, 1.0f,
    CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,  1.0f, 1.0f,
    -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,  0.0f, 0.0f,
    CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,  1.0f, 0.0f,

    -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,  0.0f, 1.0f,
    CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,  1.0f, 1.0f,
    -CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,  0.0f, 0.0f,
    CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,  1.0f, 0.0f,
};
unsigned int indices[]       = {
    0, 1, 2, // half of a square (triangle)
    1, 2, 3,

    4, 5, 6,
    5, 6, 7,

    8, 9, 10,
    9, 10, 11,

    12, 13, 14,
    13, 14, 15,

    16, 17, 18,
    17, 18, 19,

    20, 21, 22,
    21, 22, 23,
};
glm::vec3    positions[]     = {
    glm::vec3(0.0f,  0.0f,  -2.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

std::vector<glm::vec3> vecs;


void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void keyboardCallback(GLFWwindow *window); // process all input