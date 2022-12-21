#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <stack>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "pyramid.h"
#include "MyFirstGLProgram\sphere.h"
#include "mesh.h"

#define numVBOs 2;
#define numIBs 2;


class Graphics
{
public:
    Graphics();
    ~Graphics();
    bool anyProblem;
    bool Initialize(int width, int height);
    void Update(double dt);
    void HierarchicalUpdate(double dt);
    void HierarchicalUpdate2(double dt);
    void Render();
    Camera* getCamera() { return m_camera; }
    bool first;	float rs[64];
    void addLights();
private:
    std::string ErrorString(GLenum error);
    std::vector<Sphere*> spheres;
    bool collectShPrLocs();
    void ComputeTransforms(double dt, std::vector<float> speed, std::vector<float> dist,
        std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale,
        glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat);

    stack<glm::mat4> modelStack;

    Camera* m_camera;
    Shader* m_shader;
    glm::vec3 currentLightPos;
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_positionAttrib;
    GLint m_colorAttrib;
    GLint m_tcAttrib;
    GLint m_hasTexture;
    GLint m_normalMatrix;
    GLint m_tfLoc;

    Sphere* m_sun;
    Sphere* m_mercury;
    Sphere* m_venus;
    Sphere* m_earth;
    Sphere* m_earth_moon;
    Sphere* m_mars;
    Sphere* m_mars_moon1;
    Sphere* m_mars_moon2;
    Sphere* m_jupiter;
    Sphere* m_jupiter_moon1;
    Sphere* m_jupiter_moon2;
    Sphere* m_saturn;
    Sphere* m_saturn_moon1;
    Sphere* m_saturn_moon2;
    Sphere* m_uranus;
    Sphere* m_uranus_moon1;
    Sphere* m_uranus_moon2;
    Sphere* m_neptune;
    Sphere* m_neptune_moon1;
    Sphere* m_neptune_moon2;
    Sphere* m_pluto;
    Sphere* m_pluto_moon1;
    Sphere* m_pluto_moon2;

    Sphere* m_comet_halleys;
    
    Mesh* m_rocket;
    Sphere* m_skybox;
    GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mambLoc, mdiffLoc, mspecLoc, mshiLoc;
    float globalAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float lightAmbient[4] = { .15f, .15f, .15f, .15f };
    float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lightSpecular[4] = { .20f, .15f, .10f, 1.0f };
    float lightPos[3] = { 0.0, 0.0, 0.0 };

    float matAmb[4] = { 3.20, 3.20, 3.20, 1.0 };
    float matDif[4] = { 1.0, 1.0, 1.0, 1.0 };
    float matSpe[4] = { 5.0, 5.0, 5.0, 1.0 };
    float matShi = 2.0;

};

#endif /* GRAPHICS_H */
