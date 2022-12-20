#include "Pyramid.h"

Pyramid::Pyramid()
{
	createVertices();
}

void Pyramid::createVertices() {
	Vertices = {
				{{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
				{{1.0f, -1.0f, 1.0f}, {1.0f, 0.8f, 0.0f}},
				{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
				{{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
				{{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
	};

	Indices = {
	  0, 1, 2,
	  1, 2, 3,
	  4, 0, 1,
	  4, 1, 3,
	  4, 3, 2,
	  4, 2, 0
	};
}

void Pyramid::Initialize(GLint posAttribLoc, GLint colAttribLoc) {

	// Set up your VOA
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// setting the Vertex VBO
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Setting the Index VBO
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	// Computing the model matrix
	// Model orientation
	angle = 1 * 3.1415f;

	float tvec1 = 0;
	float tvec2 = 0;
	float tvec3 = 0;

	model = glm::translate(glm::mat4(1.0f), glm::vec3(tvec1, tvec2, tvec3));
	model *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1.0f, .0f));

}

Pyramid::~Pyramid()
{
	Vertices.clear();
	Indices.clear();
}

void Pyramid::Update(unsigned int dt)
{


	model = glm::translate(model, m_speed);

	//Rotates around the Z axis based on what key is pressed (key pressed changes m_rotation_speed)
	model = glm::rotate(model, m_rotation_speed, glm::vec3(0, 0, 1.f));
	//To Do: Extra credit / Grad Only
	//	Make the object move in a circle around the origin

}

glm::mat4 Pyramid::GetModel()
{
	return model;
}

void Pyramid::Render(GLint posAttribLoc, GLint colAttribLoc)
{
	// Bind VAO
	glBindVertexArray(vao);

	// Bind VBO(s)
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	// enable the vertex attribute arrays 
	// this is the poistion attrib in the vertex shader
	glEnableVertexAttribArray(posAttribLoc);
	// this is the color attribe in the vertex shader
	glEnableVertexAttribArray(colAttribLoc);

	// Draw call to OpenGL
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// disable the vertex attributes
	glDisableVertexAttribArray(posAttribLoc);
	glDisableVertexAttribArray(colAttribLoc);

	// unbind VBO(s) and ElementBuffer(s)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

