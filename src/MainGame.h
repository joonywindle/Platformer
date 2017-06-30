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
#include "Level.h"
#include "Player.h"
#include "User.h"
enum class GameState {PLAY, EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
private:
	void gameLoop();
	void initShaders();
	void initLevel();
	void calculateFPS();

	void processInput();
	void drawGame();
	void updatePlayers();
	GameState state;
	GLSLProg colorProg;
	float time;
	float fps;
	float maxFPS;
	float deltaTime;
	Camera2D camera;
	SpriteBatch playersBatch;
	InputManager inputManager;
	std::vector<Bullet> bullets;
	std::vector<Level*> levels;
	int currentLevel;
	User* user;
	std::vector<Player*> players;
};

#endif // MAINGAME_H
