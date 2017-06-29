#include "InputManager.h"
#include <iostream>
std::unordered_map<unsigned int, bool> InputManager::keyMap = {};
glm::vec2 InputManager::mouseCoords(0);

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
//    if(action == GLFW_PRESS)
//      MainGame::keys[key] = true;
//    else if(action == GLFW_RELEASE)
//      MainGame::keys[key] = false;
	if(action == GLFW_PRESS)
		keyMap[key] = true;
	else if(action == GLFW_RELEASE)
		keyMap[key] = false;
}

void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(action == GLFW_PRESS)
		keyMap[button] = true;
	else if(action == GLFW_RELEASE)
		keyMap[button] = false;
}

void InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	setMouseCoords(xpos,ypos);
}

bool InputManager::keyPressed(unsigned int keyID)
{
	auto it = keyMap.find(keyID);
	if(it != keyMap.end())
		return it->second;
	else
		return false;
}

void InputManager::setMouseCoords(float x, float y)
{
	mouseCoords.x = x;
	mouseCoords.y = y;
}

glm::vec2 InputManager::getMouseCoords()
{
	return mouseCoords;
}
