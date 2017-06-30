#ifndef USER_H
#define USER_H
#include <glm/glm.hpp>
#include "Texture.h"
#include "Player.h"
class User : public Player
{
public:
  User();
  ~User();
  void init(float speed, glm::vec2 position);
  void update(const std::vector<std::string>& levelData);

private:
  Texture texture;
};
#endif
