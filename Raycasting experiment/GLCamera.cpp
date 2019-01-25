#include "stdafx.h"
#include "headers/GLCamera.h"


glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(cameraMovement direction, float fpsNormalisation) {
    float velocity = MovementSpeed * fpsNormalisation;
    // movement goes here
}

void Camera::processMouseMovement(float xDelta, float yDelta, bool constrainPitch = true) {
    xDelta  *= MouseSensitivity;    yDelta  *= MouseSensitivity;
    Yaw     += xDelta;              Pitch   += yDelta;

    if (constrainPitch)
        if (Pitch > MAXPITCH) Pitch = MAXPITCH;
        else if (Pitch < -MAXPITCH) Pitch = -MAXPITCH;
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