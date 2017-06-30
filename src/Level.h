#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include "SpriteBatch.h"
const int TILE_WIDTH = 40;
class Level
{
public:
  Level(const std::string filename);
  ~Level();
  void draw();
  glm::vec2 getStartPos() const{return startPos;};
  const std::vector<std::string>& getLevelData() const {return levelData;};
private:
  std::vector<std::string> levelData;
  SpriteBatch levelBatch;
  glm::vec2 startPos;
  std::vector<glm::vec2> enemyStarts;
};

#endif
