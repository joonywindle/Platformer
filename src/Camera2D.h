#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();
	
	void update();
	
	void init(int screenWidth, int screenHeight);
	
	void setPosition(const glm::vec2& newPosition);
	
	glm::vec2 getPosition();
	
	float getZoom();
	
	void setZoom(float newZoom);

	glm::mat4 getCamMatrix();
	
	glm::vec2 screenToWorldCoords(glm::vec2 screenCoords);
	
	
private:
	bool needsUpdate;
	glm::vec2 position;
	glm::mat4 camMatrix;
	float zoom;
	int sWidth;
	int sHeight;
	glm::mat4 orthoMat;
};

#endif // CAMERA2D_H
