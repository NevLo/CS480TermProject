#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include "Texture.h"
class Object
{
  public:
    Object();
    ~Object();
    void Initialize(GLint posAttribLoc, GLint colAttribLoc);
    void Update(unsigned int dt);
    void Render(GLint positionAttribLoc, GLint colorAttribLoc, GLint tcAttribLoc, GLint hasTextre);
    void createVertices();
    bool InitBuffers();
    glm::mat4 GetModel();

    void setSpeed(glm::vec3 spd) { m_speed = spd; }
    std::vector<glm::vec2> getTexCoords();
    bool hasTexture;
    bool hasNormal;
    GLuint getTextureID(bool normal) {
        return normal ? m_normaltexture->getTextureID() : m_texture->getTextureID();
    }
  private:
      glm::vec3 pivotLoc;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normalVals;
    std::vector<unsigned int> Indices;
    std::vector<glm::vec2> textureCoordinates;
    Texture* m_texture;
    Texture* m_normaltexture;
    GLuint vao;

    GLuint VB;
    GLuint IB;

    glm::vec3 m_speed = glm::vec3(0., 0., 0.);

    float angle;
};

#endif /* OBJECT_H */
