#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
class WindowManager
{
public:
  WindowManager();
  ~WindowManager();
  void initSystems();
  static GLFWwindow* window;
  static const GLuint WIDTH;
  static const GLuint HEIGHT;
};

#endif
