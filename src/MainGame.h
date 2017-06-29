#ifndef MAINGAME_H
#define MAINGAME_H

#include <cmath>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Sprite.h"
#include "GLSLProg.h"
#include "Texture.h"
#include <vector>
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Bullet.h"
enum class GameState {PLAY, EXIT};
class MainGame
{
public:
	MainGame();
	void run();
private:
	void gameLoop();
	void initShaders();

	void calculateFPS();

	void processInput();
	void drawGame();
	GameState state;
	GLSLProg colorProg;
	float time;
	float fps;
	float maxFPS;
	float deltaTime;
	Camera2D camera;
	SpriteBatch sb;
	InputManager inputManager;
	std::vector<Bullet> bullets;
};

#endif // MAINGAME_H
