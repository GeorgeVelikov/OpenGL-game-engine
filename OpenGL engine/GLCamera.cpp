#include "stdafx.h"
#include <math.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/GLCamera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    MovementSpeed = CAMERA_MOVEMENT_SPEED;
    MouseSensitivity = CAMERA_TURN_SENSITIVITY;
    Zoom = CAMERA_FOV;
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCamera();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(CameraMovement direction, float fpsNormalisation) {
    float velocity = MovementSpeed * fpsNormalisation;
    // movement goes here
    if (direction == FORWARD)   Position    += Front * velocity;
    if (direction == BACKWARD)  Position    -= Front * velocity;
    if (direction == RIGHT)     Position    += Right * velocity;
    if (direction == LEFT)      Position    -= Right * velocity;
}

void Camera::processMouseMovement(float xDelta, float yDelta, bool constrainPitch) {
    xDelta  *= MouseSensitivity;    yDelta  *= MouseSensitivity;
    Yaw     += xDelta;              Pitch   -= yDelta;

    if (constrainPitch) {
        if (Pitch > CAMERA_MAX_PITCH)       Pitch = CAMERA_MAX_PITCH;
        else if (Pitch < -CAMERA_MAX_PITCH) Pitch = -CAMERA_MAX_PITCH;
    }

    updateCamera();
}

void Camera::processMouseScroll(float delta) {
    // scroll controls
    return; 
}

void Camera::obeyGravity(float delta, float floor) {
    if (Position.y > floor+1.f) Position.y -= 0.2*delta;
    else Position.y = floor+1.f;
}

// private
void Camera::updateCamera() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front   = glm::normalize(front);
    Right   = glm::normalize(glm::cross(Front, WorldUp)); 
    Up      = glm::normalize(glm::cross(Right, Front));
}
