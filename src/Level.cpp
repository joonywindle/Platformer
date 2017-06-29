#include "Level.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>

Level::Level(const std::string filename)
{
  std::ifstream file;
  file.open(filename);
  if(file.fail())
  {
    std::cout << "Could not open file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  int lineNums = 0;
  while(std::getline(file,line))
  {
    levelData.push_back(line);
    lineNums++;
  }
  levelBatch.init();
  levelBatch.begin();
  glm::vec4 uvRect(0,0,1,1);
  Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.alpha = 255;
  for (size_t i = 0; i < levelData.size(); i++) {
    for (size_t j = 0; j < levelData[i].size(); j++) {
      char tile = levelData[i][j];
      glm::vec4 destRect(j * TILE_WIDTH,i * TILE_WIDTH,TILE_WIDTH, TILE_WIDTH);
      switch (tile) {
        case 'L':
          levelBatch.draw(destRect,uvRect,ResourceManager::getTexture("../PNGs/tileGreen_15.png").id,0.0f,color);
          break;
        case 'M':
          levelBatch.draw(destRect,uvRect,ResourceManager::getTexture("../PNGs/tileGreen_22.png").id,0.0f,color);
          break;
        case 'R':
          levelBatch.draw(destRect,uvRect,ResourceManager::getTexture("../PNGs/tileGreen_16.png").id,0.0f,color);
          break;
        case 'T':
          levelBatch.draw(destRect,uvRect,ResourceManager::getTexture("../PNGs/GrassLand_Tree.png").id,0.0f,color);
          break;
        case 'S':
          startPos.x = j * TILE_WIDTH;
          startPos.y = i * TILE_WIDTH;
          break;
        case 'E':
          enemyStarts.emplace_back(j * TILE_WIDTH, i * TILE_WIDTH);
          break;
        default:
          break;
      }
    }
  }
  levelBatch.end();
}

Level::~Level()
{

}
void Level::draw()
{
  levelBatch.renderBatch();
}
