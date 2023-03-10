#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{

    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    Position = glm::vec3(0, 10, -16);
    WorldUp = glm::vec3(0, 1, 0);
    Yaw = YAW;
    Pitch = PITCH;
    Zoom = ZOOM;
    MovementSpeed = SPEED;

    view = glm::lookAt(glm::vec3(0), //Eye Position
        glm::vec3(0.0, 0.0, 0.0), //Focus point
        WorldUp); //Positive Y is up
    //updateCameraVectors();



    projection = glm::perspective(Zoom, //the FoV typically 90 degrees is good which is what this is set to
        float(w) / float(h), //Aspect Ratio, so Circles stay Circular
        0.01f, //Distance to the near plane, normally a small value like this
        100.0f); //Distance to the far plane, 
    return true;
}

glm::mat4 Camera::GetProjection()
{
    return  glm::perspective(Zoom, //the FoV typically 90 degrees is good which is what this is set to
        float(1200) / float(1000), //Aspect Ratio, so Circles stay Circular
        0.01f, //Distance to the near plane, normally a small value like this
        100.0f); //Distance to the far plane, 
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::Update(glm::vec3 speed)
{

    view = glm::lookAt(Position, Position + Front, Up);
    //view = glm::translate(view, speed);

}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        pitch(direction, deltaTime);
    if (direction == BACKWARD)
        pitch(direction, deltaTime);
    if (direction == LEFT)
        yaw(direction, deltaTime);
    if (direction == RIGHT)
        yaw(direction, deltaTime);
    if (direction == FASTER)
        Position += Front * velocity;
    if (direction == SLOWER) {
        Position -= Front * velocity;
    }
}
void Camera::yaw(Camera_Movement type, float dt) {
    Yaw = type == LEFT ? Yaw + dt * 0.5: Yaw - dt * 0.5;
    
}
void Camera::pitch(Camera_Movement type, float dt) {
    Pitch = type == FORWARD ? Pitch + dt * MovementSpeed : Pitch - dt * MovementSpeed;
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    //updateCameraVectors();

}
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}
void Camera::updateCameraVectors(glm::vec3 camUpdate)
{
    // calculate the new Front vector
    glm::vec3 front;
    front = camUpdate;
    Front = glm::normalize(front);
    view = glm::lookAt(Position, Front + Position, Up);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

