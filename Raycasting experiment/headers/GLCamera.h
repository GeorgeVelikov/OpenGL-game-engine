#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

enum cameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

#define YAW         -90.0f
#define PITCH         0.0f
#define SPEED         2.5f
#define SENSITIVITY   0.1f
#define FOV          45.0f
#define MAXPITCH     90.0f

class Camera {
    public: 
        glm::vec3 Position;
        glm::vec3 Front, Up, Right, WorldUp;
        float Yaw, Pitch;
        float MovementSpeed, MouseSensitivity, Zoom;

        // init
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
            Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(FOV) {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCamera();
        }

        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
            Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(FOV) {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;
            updateCamera();
        }

        // class funcs
        glm::mat4 getViewMatrix();
        void processKeyboard(cameraMovement direction, float fpsNormalisation);
        void processMouseMovement(float xDelta, float yDelta, bool constrainPitch);
        void processMouseScroll(float delta);

    private:
        void updateCamera();
};