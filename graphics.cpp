#include "graphics.h"
#include <vector>
#include <SOIL2/SOIL2.h>

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
	for (int i = 0; i < sizeof(rs) / sizeof(float); i++) {
		rs[i] = rand();
	}
	// Init Camera
	m_camera = new Camera();
	if (!m_camera->Initialize(width, height))
	{
		printf("Camera Failed to Initialize\n");
		return false;
	}

	// Set up the shaders
	m_shader = new Shader();
	if (!m_shader->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if (!m_shader->AddShader(GL_VERTEX_SHADER))
	{
		printf("Vertex Shader failed to Initialize\n");
		return false;
	}
	
	// Add the fragment shader
	if (!m_shader->AddShader(GL_FRAGMENT_SHADER))
	{
		printf("Fragment Shader failed to Initialize\n");
		return false;
	}
	
	// Connect the program
	if (!m_shader->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}

	// Populate location bindings of the shader uniform/attribs
	if (!collectShPrLocs()) {
		printf("Some shader attribs not located!\n");
	}

	// Create a sun
	m_sun = new Sphere("../assets/2k_sun.jpg", "../assets/2k_sun.jpg");

	m_mercury = new Sphere("../assets/Mercury.jpg", "../assets/Mercury-n.jpg");
	m_venus = new Sphere("../assets/Venus.jpg", "../assets/Venus-n.jpg");
	m_earth = new Sphere("../assets/2k_earth_daymap.jpg", "../assets/2k_earth_daymap-n.jpg");
	m_earth_moon = new Sphere("../assets/2k_moon.jpg", "../assets/2k_moon-n.jpg");
	m_mars = new Sphere("../assets/Mars.jpg", "../assets/Mars-n.jpg");
	m_mars_moon1 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg"); //decide which is which if it matters, Ceres used as place-holder
	m_mars_moon2 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");
	m_jupiter = new Sphere("../assets/Jupiter.jpg", "../assets/Jupiter-n.jpg");
	m_jupiter_moon1 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");
	m_jupiter_moon2 = new Sphere("../assets/Eris.jpg", "../assets/Eris-n.jpg");
	m_saturn = new Sphere("../assets/Saturn.jpg", "../assets/Saturn.jpg");
	m_saturn_moon1 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");//this is the only Ceres that really belongs
	m_saturn_moon2 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");
	m_uranus = new Sphere("../assets/Uranus.jpg", "../assets/Uranus-n.jpg");
	m_uranus_moon1 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");
	m_uranus_moon2 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");
	m_neptune = new Sphere("../assets/Neptune.jpg", "../assets/Neptune-n.jpg");
	m_neptune_moon1 = new Sphere("../assets/Haumea.jpg", "../assets/Haumea-n.jpg");
	m_comet_halleys = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");
	m_neptune_moon2 = new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg");

	m_rocket = new Mesh(glm::vec3(0.0f, 0.0f, 0.0f), "../assets/SpaceShip-1.obj", "../assets/SpaceShip-1.png");
	m_skybox = new Sphere("../assets/Galaxy.jpg", "../assets/Galaxy.jpg");

	spheres.push_back(m_sun);
	spheres.push_back(m_mercury);
	spheres.push_back(m_venus);
	spheres.push_back(m_earth);
	spheres.push_back(m_earth_moon);
	spheres.push_back(m_mars);
	spheres.push_back(m_mars_moon1);
	spheres.push_back(m_mars_moon2);
	spheres.push_back(m_jupiter);
	spheres.push_back(m_jupiter_moon1);
	spheres.push_back(m_jupiter_moon2);
	spheres.push_back(m_saturn);
	spheres.push_back(m_saturn_moon1);
	spheres.push_back(m_saturn_moon2);
	spheres.push_back(m_uranus);
	spheres.push_back(m_uranus_moon1);
	spheres.push_back(m_uranus_moon2);
	spheres.push_back(m_neptune);
	spheres.push_back(m_neptune_moon1);
	spheres.push_back(m_neptune_moon2);
	spheres.push_back(m_pluto);
	spheres.push_back(m_pluto_moon1);
	spheres.push_back(m_pluto_moon2);
	spheres.push_back(m_comet_halleys);
	/*
	for (int i = 0; i < 40; i++) {
		spheres.push_back(new Sphere("../assets/Ceres.jpg", "../assets/Ceres-n.jpg"));
	}
	std::cout << spheres.size() << "\n";
	*/
	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}

void Graphics::Update(double dt)
{
	//getCamera()->updateCameraVectors();
}



void Graphics::HierarchicalUpdate2(double dt){
	//update planet stuff.
	std::vector<float> speed, dist, rotSpeed, scale;
	glm::vec3 rotVector;
	glm::mat4 localTransform; // position of the sun	
	modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // push sun's coordinate
	modelStack.push(modelStack.top());
	localTransform = modelStack.top();		// The sun origin
	localTransform *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(0.f, 1.f, 0.f));
	localTransform *= glm::scale(glm::vec3(.75, .75, .75));
	if (m_sun != NULL)
		m_sun->Update(localTransform);

	// position of mercury
	speed = { 1.6, 1.6, 1.6 };
	dist = { 5., 0, 5. };
	rotVector = { 1.,1.,1. };
	rotSpeed = { 1., 1., 1. };
	scale = { .5,.5,.5 };
	localTransform = modelStack.top(); // start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_mercury != NULL)
		m_mercury->Update(localTransform);
	modelStack.pop(); //pop - planet

	// position of venus
	speed = { .6, .6, .6 };
	dist = { 10, 1.25, 10. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_venus != NULL)
		m_venus->Update(localTransform);
	modelStack.pop();//pop back to sun coords.
	//position of earth
	speed = { 1, 1, 1 };
	dist = { 15, 0, 15. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	modelStack.push(localTransform); // store rot planet - sun 
	if (m_earth != NULL)
		m_earth->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_earth_moon != NULL)
		m_earth_moon->Update(localTransform);
	modelStack.pop(); //pop to planet-sun
	modelStack.pop(); //pop to sun
	modelStack.pop();
	//position of mars
	speed = { 0.5, 0.5, 0.5 };
	dist = { 20, 0, 20. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_mars != NULL)
		m_mars->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	modelStack.pop();
	if (m_mars_moon1 != NULL)
		m_mars_moon1->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_mars_moon2 != NULL)
		m_mars_moon2->Update(localTransform);

	modelStack.pop();

	modelStack.pop();
	//position of jupiter
	speed = { 0.08, 0.08, 0.08 };
	dist = { 25, 0, 25. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_jupiter != NULL)
		m_jupiter->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_jupiter_moon1 != NULL)
		m_jupiter_moon1->Update(localTransform);
	modelStack.pop();
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_jupiter_moon2 != NULL)
		m_jupiter_moon2->Update(localTransform);

	modelStack.pop();
	modelStack.pop();
	//position of saturn
	speed = { 0.03, 0.03, 0.03 };
	dist = { 30, 0, 30. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_saturn != NULL)
		m_saturn->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_saturn_moon1 != NULL)
		m_saturn_moon1->Update(localTransform);
	modelStack.pop();
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_saturn_moon2 != NULL)
		m_saturn_moon2->Update(localTransform);

	modelStack.pop();
	modelStack.pop();
	//position of uranus
	speed = { 0.011, 0.011, 0.011 };
	dist = { 35, 0, 35. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_uranus != NULL)
		m_uranus->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_uranus_moon1 != NULL)
		m_uranus_moon1->Update(localTransform);
	modelStack.pop();
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_uranus_moon2 != NULL)
		m_uranus_moon2->Update(localTransform);

	modelStack.pop();
	modelStack.pop();
	//position of neptune
	speed = { 0.006, 0.006, 0.006 };
	dist = { 40, 0, 40. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_neptune != NULL)
		m_neptune->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_neptune_moon1 != NULL)
		m_neptune_moon1->Update(localTransform);
	modelStack.pop();
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_neptune_moon2 != NULL)
		m_neptune_moon2->Update(localTransform);
	modelStack.pop();
	modelStack.pop();
	//position of pluto
	speed = { 0.003, 0.003, 0.003 };
	dist = { 45, 0, 45. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .25, .25, .25 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_pluto != NULL)
		m_pluto->Update(localTransform);
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_pluto_moon1 != NULL)
		m_pluto_moon1->Update(localTransform);
	modelStack.pop();
	speed = { 1, 1, 1 };
	dist = { 1, 0, 1. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_pluto_moon2 != NULL)
		m_pluto_moon2->Update(localTransform);
	modelStack.pop();
	modelStack.pop();
	//Halleys comet
	speed = { 1, 1, 1 };
	dist = { 50, 0, 50. };
	rotVector = { 1.,0.,1. };
	rotSpeed = { .5, 0, .5 };
	scale = { .27f, .27f, .27f };
	localTransform = modelStack.top();
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
	modelStack.push(localTransform);			// store moon-planet-sun coordinate
	localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

	if (m_pluto_moon2 != NULL)
		m_pluto_moon2->Update(localTransform);
	modelStack.pop();
 	// back to the planet coordinate
	modelStack.pop();
	//srand(50);
	/*
	for (int i = 24; i < 44; i++) {
		// t = b1 + ((s-a1)(b2-b1))/(a2-a1)
		
		float r  = -0.01 + ((rs[i]) * (0.02)) / (1);
		speed = { 0.01f + r, 0.01f + r, 0.01f + r };
		dist = { 22, 0, 22. };
		rotVector = { .01f + r,0.,.01f + r };
		rotSpeed = { .005, 0, .005 };
		scale = { .27f, .27f, .27f };
		localTransform = modelStack.top();
		localTransform *= glm::translate(glm::mat4(1.f),
			glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
		modelStack.push(localTransform);			// store moon-planet-sun coordinate
		localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
		localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
		spheres[i]->Update(localTransform);
		modelStack.pop();
	}
	//srand(100);

	for (int i = 44; i < spheres.size(); i++) {
		float r;
		
		r = -0.01 + ((rs[i]) * (0.02)) / (1);
		speed = { 0.01f+r, 0.01f + r, 0.01f + r };
		dist = { 47, 0, 47. };
		rotVector = { 1 + r,0.,1 + r };
		rotSpeed = { .5, 0, .5 };
		scale = { .27f, .27f, .27f };
		localTransform = modelStack.top();
		localTransform *= glm::translate(glm::mat4(1.f),
			glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2]));
		modelStack.push(localTransform);			// store moon-planet-sun coordinate
		localTransform *= glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
		localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
		spheres[i]->Update(localTransform);
		modelStack.pop();
	}
	*/

	 	// back to the sun coordinate
	// empy stack

	/*
	localTransform = glm::translate(glm::mat4(1.f),glm::vec3(getCamera()->Position + getCamera()->Front));

	localTransform *= glm::inverse(glm::lookAt(glm::vec3(0,0,0), -getCamera()->Front, glm::vec3(0, 1, 0)));
	localTransform *= glm::scale(glm::vec3(0.2, 0.2, 0.2));
	m_rocket->Update(localTransform);
	*/
	localTransform = glm::translate(glm::mat4(1.f), m_camera->Position);
	localTransform *= glm::scale(glm::vec3(0.005, 0.005, 0.005));
	localTransform *= glm::translate(glm::mat4(1.f), glm::vec3(0.0, -25.0, -40.0));
	if (m_rocket != NULL)
		m_rocket->Update(localTransform);
	if (first) {
		first = !first;
	}
}


void Graphics::ComputeTransforms(double dt, std::vector<float> speed, std::vector<float> dist,
	std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat) {
	tmat = glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2])
	);
	rmat = glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	smat = glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
}
void Graphics::addLights() {
	currentLightPos = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 transformed = glm::vec3(m_camera->GetView() * glm::vec4(currentLightPos, 1.0));
	lightPos[0] = transformed.x;
	lightPos[1] = transformed.y;
	lightPos[2] = transformed.z;

	globalAmbLoc = glGetUniformLocation(m_shader->m_shaderProg, "globalAmbient");
	ambLoc = glGetUniformLocation(m_shader->m_shaderProg, "light.ambient");
	diffLoc = glGetUniformLocation(m_shader->m_shaderProg, "light.diffuse");
	specLoc = glGetUniformLocation(m_shader->m_shaderProg, "light.specular");
	posLoc = glGetUniformLocation(m_shader->m_shaderProg, "light.position");
	mambLoc = glGetUniformLocation(m_shader->m_shaderProg, "material.ambient");
	mdiffLoc = glGetUniformLocation(m_shader->m_shaderProg, "material.diffuse");
	mspecLoc = glGetUniformLocation(m_shader->m_shaderProg, "material.specular");
	mshiLoc = glGetUniformLocation(m_shader->m_shaderProg, "material.shininess");


	glProgramUniform4fv(m_shader->m_shaderProg, globalAmbLoc, 1, globalAmbient);
	glProgramUniform4fv(m_shader->m_shaderProg, ambLoc, 1, lightAmbient);
	glProgramUniform4fv(m_shader->m_shaderProg, diffLoc, 1, lightDiffuse);
	glProgramUniform4fv(m_shader->m_shaderProg, specLoc, 1, lightSpecular);
	glProgramUniform3fv(m_shader->m_shaderProg, posLoc, 1, lightPos);
	glProgramUniform4fv(m_shader->m_shaderProg, mambLoc, 1, matAmb);
	glProgramUniform4fv(m_shader->m_shaderProg, mdiffLoc, 1, matDif);
	glProgramUniform4fv(m_shader->m_shaderProg, mspecLoc, 1, matSpe);
	glProgramUniform1f(m_shader->m_shaderProg, mshiLoc, matShi);
}
void Graphics::Render()
{
	//clear the screen
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the correct program
	m_shader->Enable();

	// Send in the projection and view to the shader (stay the same while camera intrinsic(perspective) and extrinsic (view) parameters are the same
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

	addLights();

	// Render the objects
	for (Sphere* s : spheres) {
		if (s == NULL) return;
		GLuint hasNormal = m_shader->GetUniformLocation("hasNormalMap");
		if (s->hasTexture) {
			glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(s->GetModel()));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, s->getTextureID(false));
			GLuint sampler = m_shader->GetUniformLocation("samp0");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			s->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(s->GetModel()));
		if (s->hasTexture) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, s->getTextureID(true));
			GLuint sampler = m_shader->GetUniformLocation("samp1");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 1);
			glUniform1i(hasNormal, true);
			s->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	if (m_rocket != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_rocket->GetModel()));
		if (m_rocket->hasTex) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_rocket->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("samp0");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_rocket->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}/*
	if (m_skybox != NULL) {
		GLuint hasN = m_shader->GetUniformLocation("hasNormalMap");
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_skybox->GetModel()));
		if (m_skybox->hasTexture) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_skybox->m_textureID);
			GLuint sampler = m_shader->GetUniformLocation("samp0");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			glUniform1i(hasN, false);
			m_skybox->Render(m_positionAttrib, m_colorAttrib, m_tcAttrib, m_hasTexture);
		}
	}
	*/
	// Get any errors from OpenGL
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string val = ErrorString(error);
		std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
	}
}



bool Graphics::collectShPrLocs() {

	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
	if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_projectionMatrix not found\n");
		return false;
	}

	// Locate the view matrix in the shader
	m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
	if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_viewMatrix not found\n");
		return false;
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
	if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_modelMatrix not found\n");
		return false;
	}

	// Locate the position vertex attribute
	m_positionAttrib = m_shader->GetAttribLocation("v_position");
	if (m_positionAttrib == -1)
	{
		printf("v_position attribute not found\n");
		return false;
	}

	// Locate the color vertex attribute
	m_colorAttrib = m_shader->GetAttribLocation("v_color");
	if (m_colorAttrib == -1)
	{
		printf("v_color attribute not found\n");
		return false;
	}

	return true;
}

std::string Graphics::ErrorString(GLenum error)
{
	if (error == GL_INVALID_ENUM)
	{
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	}

	else if (error == GL_INVALID_VALUE)
	{
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	}

	else if (error == GL_INVALID_OPERATION)
	{
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	}

	else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	}

	else if (error == GL_OUT_OF_MEMORY)
	{
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	}
	else
	{
		return "None";
	}
}

