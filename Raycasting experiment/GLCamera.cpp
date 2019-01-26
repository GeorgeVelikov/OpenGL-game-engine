#include "stdafx.h"
#include <math.h>
#include "headers/GLCamera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = FOV;
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCamera();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(cameraMovement direction, float fpsNormalisation) {
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
        if (Pitch > MAXPITCH)       Pitch = MAXPITCH;
        else if (Pitch < -MAXPITCH) Pitch = -MAXPITCH;
    }

    updateCamera();
}

void Camera::processMouseScroll(float delta) {
    // scroll controls
    return; 
}

void Camera::updateCamera() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front   = glm::normalize(front);
    Right   = glm::normalize(glm::cross(Front, WorldUp)); 
    Up      = glm::normalize(glm::cross(Right, Front));
}