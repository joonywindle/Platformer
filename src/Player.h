#ifndef PLAYER_H
#define PLAYER_H
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include <string>
const float PLAYER_WIDTH = 40;

class Player
{
public:
  Player();
  virtual ~Player();
  void draw(SpriteBatch& batch);
  virtual void update(const std::vector<std::string>& levelData) = 0;
  void collideWithLevel(const std::vector<std::string>& levelData);
  glm::vec2 getPosition() const {return position;}
protected:
  glm::vec2 position;
  float speed;
  void collideWithTile(glm::vec2 tilePos);
  void checkTileCollision(std::vector<glm::vec2>& tilePositions, const std::vector<std::string>& levelData, float x, float y);
};
#endif
