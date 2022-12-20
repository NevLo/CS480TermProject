
#include "graphics_headers.h"
#include <vector>
class Mesh
{
public:
    Mesh();
    Mesh(glm::vec3 pivot);

    ~Mesh();
    void Update(glm::mat4 model);
    void Render(GLint posAttrib, GLint colAttrib);

    glm::mat4 GetModel();

    bool InitBuffers();
    bool loadModelFromFile(const char* path);

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    GLuint vao;

    float angle;


};