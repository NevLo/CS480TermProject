
#include "engine.h"
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 1200.0f / 2.0;
float lastY = 1000.0 / 2.0;
float fov = 45.0f;

Engine::Engine(const char* name, int width, int height)
{
    m_WINDOW_NAME = name;
    m_WINDOW_WIDTH = width;
    m_WINDOW_HEIGHT = height;
 
}


Engine::~Engine()
{
    delete m_window;
    delete m_graphics;
    m_window = NULL;
    m_graphics = NULL;
}

bool Engine::Initialize()
{
    // Start a window
    m_window = new Window(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT);
    if (!m_window->Initialize())
    {
        printf("The window failed to initialize.\n");
        return false;
    }

    // Start the graphics
    m_graphics = new Graphics();
    if (!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
    {
        printf("The graphics failed to initialize.\n");
        return false;
    }
    glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window->getWindow(), cursorPositionCallBack);
    glfwSetScrollCallback(m_window->getWindow(), scroll_callback);

    // No errors
    return true;
}

void Engine::Run()
{
    m_running = true;
    std::cout << "Engine in:" << "\n";
    while (!glfwWindowShouldClose(m_window->getWindow()))
    {
        ProcessInput();
        Display(m_window->getWindow(), glfwGetTime());
        glfwPollEvents();
    }
    m_running = false;

}



unsigned int Engine::getDT()
{
    //long long TimeNowMillis = GetCurrentTimeMillis();
    //assert(TimeNowMillis >= m_currentTimeMillis);
    //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
    //m_currentTimeMillis = TimeNowMillis;
    //return DeltaTimeMillis;
    return glfwGetTime();
}

long long Engine::GetCurrentTimeMillis()
{
    //timeval t;
    //gettimeofday(&t, NULL);
    //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
    //return ret;
    return (long long)glfwGetTime();
}

void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render();
    m_window->Swap();

    // update graphics -> updates model
    m_graphics->Update(time);
    m_graphics->HierarchicalUpdate2(time);
}

void cursorPositionCallBack(GLFWwindow* window, double xposIn, double yposIn) {
     float xpos = static_cast<float>(xposIn);
     float ypos = static_cast<float>(yposIn);

    //e->m_graphics->getCamera()->ProcessMouseMovement(xposIn, yposIn);
}
 void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
 {
     fov -= (float)yoffset;
     if (fov < 1.0f)
         fov = 1.0f;
     if (fov > 45.0f)
         fov = 45.0f;
 }

 void Engine::ProcessInput()
 {
     //key input that moves triangle
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(m_window->getWindow(), true);
     double xpos;
     double ypos;
     glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
     glfwGetCursorPos(m_window->getWindow(), &xpos, &ypos);

     float xoffset = xpos - lastX;
     float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
     lastX = xpos;
     lastY = ypos;

     const float sensitivity = 0.1f;
     xoffset *= sensitivity;
     yoffset *= sensitivity;
     yaw += xoffset;
     pitch += yoffset;

     // make sure that when pitch is out of bounds, screen doesn't get flipped
     if (pitch > 89.0f)
         pitch = 89.0f;
     if (pitch < -89.0f)
         pitch = -89.0f;

     glm::vec3 front;
     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
     front.y = sin(glm::radians(pitch));
     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
     glm::vec3 cameraFront = glm::normalize(front);

     m_graphics->getCamera()->updateCameraVectors(cameraFront);
     m_graphics->getCamera()->Zoom = fov;

     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_RELEASE &&
         glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_RELEASE &&
         glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_RELEASE &&
         glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_RELEASE)
         m_graphics->getCamera()->Update(glm::vec3(0., 0., 0.));
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
         m_graphics->getCamera()->ProcessKeyboard(BACKWARD, getDT());
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
         m_graphics->getCamera()->ProcessKeyboard(FORWARD, getDT());
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
         m_graphics->getCamera()->ProcessKeyboard(LEFT, getDT());
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
         m_graphics->getCamera()->ProcessKeyboard(RIGHT, getDT());
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
         m_graphics->getCamera()->ProcessKeyboard(FASTER, getDT());
     if (glfwGetKey(m_window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
         m_graphics->getCamera()->ProcessKeyboard(SLOWER, getDT());
 
}