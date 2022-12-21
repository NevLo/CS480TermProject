#include "graphics_headers.h"
#include <vector>
#include "Texture.h"
class Mesh
{
public:
    Mesh();
    Mesh(glm::vec3 pivot);
    Mesh(glm::vec3 pivot, const char* file, const char* texture);

    ~Mesh();
    void Update(glm::mat4 model);
    void Render(GLint positionAttribLoc, GLint colorAttribLoc, GLint tcAttribLoc, GLint hasTex);

    glm::mat4 GetModel();

    bool InitBuffers();
    bool loadModelFromFile(const char* path);
    bool hasTex;
    GLuint getTextureID() { return m_texture->getTextureID(); }
private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    GLuint vao;

    float angle;
    Texture* m_texture;

};

