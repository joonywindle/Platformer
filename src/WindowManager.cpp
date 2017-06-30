#include "WindowManager.h"
#include "InputManager.h"
#include <iostream>
GLFWwindow* WindowManager::window = nullptr;
const GLuint WindowManager::WIDTH = 1200;
const GLuint WindowManager::HEIGHT = 700;

WindowManager::WindowManager()
{
}
WindowManager::~WindowManager()
{
}
void WindowManager::initSystems()
{
  // Init glfw
  glfwInit();
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Game Engine", nullptr, nullptr);

  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
  glewExperimental = GL_TRUE;
  glfwMakeContextCurrent(window);
  // Set input methods
  glfwSetKeyCallback(window, InputManager::key_callback);
  glfwSetMouseButtonCallback(window,InputManager::mouse_button_callback);
  glfwSetCursorPosCallback(window, InputManager::mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
  // Initialize GLEW to setup the OpenGL Function pointers
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    exit(EXIT_FAILURE);
  }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  std::printf("OPEN GL VERSION: %s", glGetString(GL_VERSION));
  glClearColor(0.0f, 0.9f, 0.9f, 1.0f);
}
