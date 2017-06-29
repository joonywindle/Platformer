#include "Bullet.h"
#include "ResourceManager.h"
#include "Texture.h"
#include <iostream>
Bullet::Bullet(glm::vec2 _position, glm::vec2 _direction, float _speed, int _lifeTime)
{
	position = _position;
	direction = _direction;
	speed = _speed;
	lifeTime = _lifeTime;
}

Bullet::~Bullet()
{
}

void Bullet::draw(SpriteBatch& spriteBatch)
{
	Texture text = ResourceManager::getTexture("../PNGs/GrassLand_Trunk.png");
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.alpha = 255;
	//glm::vec4 posAndSize = glm::vec4(position.x,position.y,30,30);
	spriteBatch.draw(glm::vec4(position.x,position.y,30,30),glm::vec4(0,0,1,1),text.id,0,color);
}

bool Bullet::update()
{
	position += direction * speed;
	lifeTime--;
	return lifeTime == 0;
}
