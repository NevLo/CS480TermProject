
#ifndef SPHERE_H
#define SPHERE_H
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include "../graphics_headers.h"
#include <string>
using namespace std;
class Sphere
{
private:
	int numVertices;
	int numIndices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	float toRadians(float degrees);
	glm::mat4 model;
	glm::vec3 pivotLocation;
	string textureName;
	

	GLuint VB;
	GLuint IB;

	GLuint vao;

	float angle;
public:
	Sphere();
	Sphere(glm::vec3 pivot, int prec);
	Sphere(string s);
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
	glm::mat4 GetModel();



	~Sphere();

	void Render(GLint posAttrib, GLint colAttrib);



	bool InitBuffers();

};
#endif
