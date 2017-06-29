#ifndef BULLET_H
#define BULLET_H
#include <glm/glm.hpp>
#include "SpriteBatch.h"
class Bullet
{
public:
	Bullet(glm::vec2 _position, glm::vec2 _direction, float _speed, int _lifeTime);
	~Bullet();
	void draw(SpriteBatch& spriteBatch);
	bool update();
private:
	int lifeTime;
	float speed;
	glm::vec2 direction;
	glm::vec2 position;

};

#endif // BULLET_H
