#ifndef ENGINE_H
#define ENGINE_H


#include <assert.h>
#include "window.h"
#include "graphics.h"



class Engine
{
  public:
      
      //constructor
      Engine();
    Engine(const char*  name, int width, int height);
    //destructor
    ~Engine();
    bool Initialize();
    void Run();
    void ProcessInput();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void Display(GLFWwindow*, double);
    static void cursorPositionCallBack(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
   
    void setSpeed(glm::vec3 spd) { speed = spd; };
    const char* m_WINDOW_NAME; //window name
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN; // is fullscreen.
    float lastX;
    float lastY;
    bool firstMouse;


  private:
    // Window related variables
    Window *m_window;    //variable for the window.


    glm::vec3 speed = glm::vec3(0.f,0.f,0.f);


    static Graphics* m_graphics;

    bool m_running;
};

#endif // ENGINE_H
