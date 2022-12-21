
#ifndef SPHERE_H
#define SPHERE_H
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include "../graphics_headers.h"
#include <string>
#include "../shader.h"
#include "../Texture.h"

using namespace std;
class Sphere
{
private:
	int numVertices;
	int numIndices;
	std::vector<Vertex> Vertices;
	std::vector<int> Indices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	float toRadians(float degrees);
	std::vector<float> pvalues;
	std::vector<float> tvalues;
	std::vector<float> nvalues;
	glm::mat4 model;
	glm::vec3 pivotLocation;
	string textureName;
	Texture* m_texture;
	Texture* m_normaltexture;

	GLuint VB;
	GLuint IB;

	GLuint vao;

	float angle;

	void setupVertices();
	void setupBuffers();
	void setupModelMatrix(glm::vec3 pl, float angle, float scale);
public:
	Sphere();
	Sphere(glm::vec3 pivot, int prec);
	Sphere(const char* s, const char* s2);
	int getNumVertices();
	int getNumIndices();
	bool loadTexture(const char* texFile, int textureType);
	void init(int);
	std::vector<unsigned int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();
	void Update(glm::mat4 model);
	int m_textureID;
	int m_NormalTextureID;
	Shader m_shader;
	bool hasTexture;
	bool hasNormal;
	~Sphere();
	void Render(GLint posAttribLoc, GLint colAttribLoc, GLint tcAttribLoc, GLint hasTextureLoc);
	bool InitBuffers();
	glm::mat4 GetModel() { return model; }
	GLuint getTextureID(bool normal) {
		if (normal)
			return m_normaltexture->getTextureID();
		else
			return m_texture->getTextureID();
	}
};
#endif
