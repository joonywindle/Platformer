#include "User.h"
#include "InputManager.h"
User::User()
{

}
User::~User()
{

}
void User::init(float _speed, glm::vec2 _position)
{
  speed = _speed;
  position = _position;

}
void User::update(const std::vector<std::string>& levelData)
{
  if(InputManager::keyPressed(GLFW_KEY_D))
    position.x += speed;
  if(InputManager::keyPressed(GLFW_KEY_A))
    position.x -= speed;
  if(InputManager::keyPressed(GLFW_KEY_W))
    position.y += speed;
  if(InputManager::keyPressed(GLFW_KEY_S))
    position.y -= speed;
  collideWithLevel(levelData);
}
