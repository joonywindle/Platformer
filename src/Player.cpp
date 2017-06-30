#include "Player.h"
#include "ResourceManager.h"
#include "Level.h"
#include <iostream>
#include <algorithm>
Player::Player()
{

}

Player::~Player()
{

}

void Player::draw(SpriteBatch& batch)
{
  glm::vec4 uvRect(0,0,1,1);
  glm::vec4 destRect;
  destRect.x = position.x;
  destRect.y = position.y;
  destRect.z = PLAYER_WIDTH;
  destRect.w = PLAYER_WIDTH;

  Color color;
  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.alpha = 255;

  batch.draw(destRect,uvRect, ResourceManager::getTexture("../PNGs/playerBlue_duck.png").id, 0, color);
}

void Player::collideWithLevel(const std::vector<std::string>& levelData)
{
  std::vector<glm::vec2> tilePositions;
  checkTileCollision(tilePositions, levelData, position.x, position.y);
  checkTileCollision(tilePositions, levelData, position.x + PLAYER_WIDTH, position.y);
  checkTileCollision(tilePositions, levelData, position.x, position.y + PLAYER_WIDTH);
  checkTileCollision(tilePositions, levelData, position.x + PLAYER_WIDTH, position.y + PLAYER_WIDTH);
  //std::cout << "POS: " << position.x << "," << position.y << std::endl;
  for (size_t i = 0; i < tilePositions.size(); i++)
  {
    collideWithTile(tilePositions[i]);
  }

}

void Player::checkTileCollision(std::vector<glm::vec2>& tilePositions, const std::vector<std::string>& levelData, float x, float y)
{
  glm::vec2 cornerPos = glm::vec2(floor((float)x/(float)TILE_WIDTH),floor((float)y/(float)TILE_WIDTH));

  if(levelData.size() <= cornerPos.y || levelData[0].size() <= cornerPos.x || cornerPos.y < 0 || cornerPos.x < 0)
    return;
  // {
    if(levelData[cornerPos.y][cornerPos.x] != '.')
    {
      std::cout << "TILE: " << cornerPos.x << "," << cornerPos.y << std::endl;
      std::cout << "SIZE: " << levelData.size() << "," << levelData[cornerPos.y].size() << std::endl;
      tilePositions.push_back(cornerPos * (float) TILE_WIDTH + glm::vec2(TILE_WIDTH/2.0f,TILE_WIDTH/2.0f));
    }
  // }
}

void Player::collideWithTile(glm::vec2 tilePos)
{
  //std::cout << "TILE: " << tilePos.x << "," << tilePos.y << std::endl;
  float minDistance = ((float)PLAYER_WIDTH/2) + ((float)TILE_WIDTH/2);
  glm::vec2 centrePos = position + glm::vec2((float)PLAYER_WIDTH/2);
  glm::vec2 distVec = centrePos - tilePos;
  float xDepth = minDistance - abs(distVec.x);
  float yDepth = minDistance - abs(distVec.y);
  if(xDepth > 0 || yDepth > 0)
  {
    if(std::max(xDepth,0.0f) < std::max(yDepth,0.0f))
    {
      if(distVec.x < 0)
      position.x -= xDepth;
      else
      position.x += xDepth;
    }
    else
    {
      if(distVec.y < 0)
      position.y -= yDepth;
      else
      position.y += yDepth;
    }
  }
}
