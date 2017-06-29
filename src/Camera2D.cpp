#include "Camera2D.h"
#include <iostream>

Camera2D::Camera2D() : needsUpdate(true), position(0.0f,0.0f),camMatrix(1.0f),zoom(1.0f),sWidth(500),sHeight(500)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::update()
{
	if(needsUpdate)
	{
		glm::vec3 translate(-position.x,-position.y,0.0f);
		camMatrix = glm::translate(orthoMat,translate);
		glm::vec3 scale(zoom,zoom,0.0f);
		camMatrix = glm::scale(camMatrix,scale);
		// Make focal point center of screen
		translate = glm::vec3(sWidth/2,sHeight/2,0.0f);
		camMatrix = glm::translate(camMatrix,translate);
		needsUpdate  = false;
	}
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	sWidth = screenWidth;
	sHeight = screenHeight;
	orthoMat = glm::ortho(0.0f,(float)sWidth,0.0f,(float)sHeight);
}

void Camera2D::setPosition(const glm::vec2& newPosition)
{
	this->needsUpdate = true;
	position = newPosition;
}

glm::vec2 Camera2D::getPosition() 
{
	return position;
}

float Camera2D::getZoom() 
{
	return zoom;
}

void Camera2D::setZoom(float newZoom)
{
	this->needsUpdate = true;
	zoom = newZoom;
}

glm::mat4 Camera2D::getCamMatrix()
{
	return camMatrix;
}

glm::vec2 Camera2D::screenToWorldCoords(glm::vec2 screenCoords)
{
	screenCoords.y = sHeight - screenCoords.y;
	// 0 is center
	screenCoords -= glm::vec2(sWidth/2,sHeight/2);
	// Scale coordinates
	screenCoords /= zoom;
	// Translate with camera position
	screenCoords += position;
	
	return screenCoords;
	
}