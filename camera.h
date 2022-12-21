#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = .025f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 40.0f;

class Camera
{
public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    void Update(glm::vec3 speed);
    void ProcessKeyboard(Camera_Movement direction, float dt);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void updateCameraVectors();
private:
    glm::mat4 projection;
    glm::mat4 view;

};

#endif /* CAMERA_H */
