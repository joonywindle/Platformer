#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "SpriteBatch.h"
const int TILE_WIDTH = 64;
class Level
{
public:
  Level(const std::string filename);
  ~Level();
  void draw();
private:
  std::vector<std::string> levelData;
  SpriteBatch levelBatch;
  glm::vec2 startPos;
  std::vector<glm::vec2> enemyStarts;
};

#endif
