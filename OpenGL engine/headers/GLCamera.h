enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

#define CAMERA_YAW                -90.0f
#define CAMERA_PITCH                0.0f
#define CAMERA_MOVEMENT_SPEED       2.0f
#define CAMERA_TURN_SENSITIVITY     0.1f
#define CAMERA_FOV                 45.0f
#define CAMERA_MAX_PITCH           89.0f

class Camera {
    public: 
        glm::vec3 Position, PositionOld;
        glm::vec3 Front, Up, Right, WorldUp;
        float Yaw, Pitch;
        float MovementSpeed, MouseSensitivity, Zoom;

        // init 
        Camera(glm::vec3 position = glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH);

        // class funcs
        glm::mat4 getViewMatrix();
        void processKeyboard(CameraMovement direction, float fpsNormalisation);
        void processMouseMovement(float xDelta, float yDelta, bool constrainPitch = true);
        void processMouseScroll(float delta);
        void obeyGravity(float delta, float floor);

    private:
        void updateCamera();
};