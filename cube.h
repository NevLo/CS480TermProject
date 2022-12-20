
#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "graphics_headers.h"

class Cube
{
public:
    Cube();
    Cube(float scale);
    ~Cube();
    void Initialize(GLint posAttribLoc, GLint colAttribLoc);
    void Initialize(GLint posAttribLoc, GLint colAttribLoc, glm::vec3 pos);
    void Update(unsigned int dt);
    void Render(GLint posAttribLoc, GLint colAttribLoc);
    void createVertices();

    glm::mat4 GetModel();

    void setSpeed(glm::vec3 spd) { m_speed = spd; }
    void setRotation(float ang) { m_rotation_speed = ang; }
    void setScale(float scale) { m_scale = scale; }
private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    GLuint vao;

    GLuint VB;
    GLuint IB;

    glm::vec3 m_speed = glm::vec3(0., 0., 0.);
    float m_rotation_speed = 0;
    float angle;
    float m_scale = 1;
};

#endif /* CUBE_H */
