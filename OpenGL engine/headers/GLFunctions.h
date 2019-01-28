void frameBufferCheck(GLFWwindow* window, int width, int height); // make sure the viewport matches the new window dimensions;
void setupGLFW(); // initialize and configure glfw
void setupGLAD(); // load all OpenGL function pointers glad
void load2DImageAsTexture(unsigned int *texture, int id, const char* path);