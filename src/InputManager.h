#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static bool keyPressed(unsigned int keyID);
	static void setMouseCoords(float x, float y);

	glm::vec2 getMouseCoords();
private:
	static std::unordered_map<unsigned int, bool> keyMap;
	static glm::vec2 mouseCoords;
};

#endif // INPUTMANAGER_H
