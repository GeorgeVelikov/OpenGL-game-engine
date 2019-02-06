struct GameTime {
    float delta;
    float past;
    float current;
} time;

struct MouseLocation {
    float X;
    float Y;
} mouse;

Camera  camera;
Map     map;

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720


float        cubeVertices[]  = {
    // top pane
   -EDGE_SIZE,  EDGE_SIZE, -EDGE_SIZE, 0.0f, 0.0f,
    EDGE_SIZE,  EDGE_SIZE, -EDGE_SIZE, 1.0f, 0.0f,
   -EDGE_SIZE,  EDGE_SIZE,  EDGE_SIZE, 0.0f, 1.0f,
    EDGE_SIZE,  EDGE_SIZE,  EDGE_SIZE, 1.0f, 1.0f,
     // left pane
    -EDGE_SIZE, -EDGE_SIZE, -EDGE_SIZE, 0.0f, 0.0f,
     EDGE_SIZE, -EDGE_SIZE, -EDGE_SIZE, 1.0f, 0.0f,
    -EDGE_SIZE,  EDGE_SIZE, -EDGE_SIZE, 0.0f, 1.0f,
     EDGE_SIZE,  EDGE_SIZE, -EDGE_SIZE, 1.0f, 1.0f,
     // right pane
    -EDGE_SIZE, -EDGE_SIZE,  EDGE_SIZE, 0.0f, 0.0f,
     EDGE_SIZE, -EDGE_SIZE,  EDGE_SIZE, 1.0f, 0.0f,
    -EDGE_SIZE,  EDGE_SIZE,  EDGE_SIZE, 0.0f, 1.0f,
     EDGE_SIZE,  EDGE_SIZE,  EDGE_SIZE, 1.0f, 1.0f,
     // back pane
    -EDGE_SIZE,  EDGE_SIZE,  EDGE_SIZE, 0.0f, 0.0f,
    -EDGE_SIZE,  EDGE_SIZE, -EDGE_SIZE, 1.0f, 0.0f,
    -EDGE_SIZE, -EDGE_SIZE,  EDGE_SIZE, 0.0f, 1.0f,
    -EDGE_SIZE, -EDGE_SIZE, -EDGE_SIZE, 1.0f, 1.0f,
     // forward pane
     EDGE_SIZE,  EDGE_SIZE,  EDGE_SIZE, 0.0f, 0.0f,
     EDGE_SIZE,  EDGE_SIZE, -EDGE_SIZE, 1.0f, 0.0f,
     EDGE_SIZE, -EDGE_SIZE,  EDGE_SIZE, 0.0f, 1.0f,
     EDGE_SIZE, -EDGE_SIZE, -EDGE_SIZE, 1.0f, 1.0f,
     // bottom pane
    -EDGE_SIZE, -EDGE_SIZE, -EDGE_SIZE, 0.0f, 0.0f,
     EDGE_SIZE, -EDGE_SIZE, -EDGE_SIZE, 1.0f, 0.0f,
    -EDGE_SIZE, -EDGE_SIZE,  EDGE_SIZE, 0.0f, 1.0f,
     EDGE_SIZE, -EDGE_SIZE,  EDGE_SIZE, 1.0f, 1.0f,

};
unsigned int indices[]       = {
    0, 1, 2, // half of a square (triangle)
    1, 3, 2,

    4, 5, 6,
    5, 7, 6,

    8, 10, 9,
    9, 10, 11,

    12, 14, 13,
    13, 14, 15,

    16, 17, 18,
    17, 19, 18,

    20, 22, 21,
    21, 22, 23,
};

std::vector<glm::vec3> positions;

void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void keyboardCallback(GLFWwindow *window); // process all input
void getFrameTime(GameTime &gt);