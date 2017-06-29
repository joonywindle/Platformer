#include "MainGame.h"
#include "WindowManager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.h"

MainGame::MainGame() : time(0),state(GameState::PLAY), maxFPS(60), currentLevel(0)
{

}

MainGame::~MainGame()
{
	for (size_t i = 0; i < levels.size(); i++)
	{
		delete levels[i];
	}
}

void MainGame::run()
{
	initShaders();
	levels.push_back(new Level("../Levels/level1.txt"));
	sb.init();
	camera.init(WindowManager::WIDTH,WindowManager::HEIGHT);
	gameLoop();
}

void MainGame::gameLoop()
{

	while (state != GameState::EXIT)
	{
		for(int i  = 0; i < bullets.size();) {
			if(bullets[i].update())
			{
				bullets[i] = bullets.back();
				bullets.pop_back();
			}
			else
				i++;
		}
		drawGame();
		time += 0.1;
		processInput();
		camera.update();
		calculateFPS();
		static int frameCount = 0;
		if(++frameCount == 10)
		{
			frameCount = 0;
		}
	}
}

void MainGame::processInput()
{
	const float VELOCITY = 20.0f;
	const float SCALE_SPEED = 0.01f;
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
		if(inputManager.keyPressed(GLFW_KEY_ESCAPE))
			state = GameState::EXIT;
		if (inputManager.keyPressed(GLFW_KEY_W))
		{
			glm::vec2 pos = camera.getPosition();
			glm::vec2 direction(0.0f,VELOCITY);
			glm::vec2 offset = pos + direction;
			camera.setPosition(offset);
		}
		if(inputManager.keyPressed(GLFW_KEY_S))
		{
			glm::vec2 pos = camera.getPosition();
			glm::vec2 direction(0.0f,-VELOCITY);
			glm::vec2 offset = pos + direction;
			camera.setPosition(offset);
		}
		if(inputManager.keyPressed(GLFW_KEY_A))
		{
			glm::vec2 pos = camera.getPosition();
			glm::vec2 direction(-VELOCITY,0.0f);
			glm::vec2 offset = pos + direction;
			camera.setPosition(offset);
		}
		if(inputManager.keyPressed(GLFW_KEY_D))
		{
			glm::vec2 pos = camera.getPosition();
			glm::vec2 direction(VELOCITY,0.0f);
			glm::vec2 offset = pos + direction;
			camera.setPosition(offset);
		}
		if(inputManager.keyPressed(GLFW_KEY_Q))
		{
			camera.setZoom(camera.getZoom() - SCALE_SPEED);
		}
		if(inputManager.keyPressed(GLFW_KEY_E))
		{
			camera.setZoom(camera.getZoom() + SCALE_SPEED);
		}
		if(inputManager.keyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			glm::vec2 mouse = camera.screenToWorldCoords(inputManager.getMouseCoords());
			//glm::vec2 playerPos(0.0f,0.0f);
			glm::vec2 playerPos(0.0f);
			glm::vec2 direction = mouse - playerPos;

			direction = glm::normalize(direction);
			bullets.emplace_back(playerPos, direction, 30.0f, 1000);
		}
}

void MainGame::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorProg.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = colorProg.getUniformLocation("aSampler");
	glUniform1i(textureLocation,0);
	GLint pLocation = colorProg.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera.getCamMatrix();
	glUniformMatrix4fv(pLocation,1,GL_FALSE,&cameraMatrix[0][0]);

	// sb.begin();
	// static Texture text = ResourceManager::getTexture("../PNGs/GrassLand_Tree.png");
	// Color color;
	// color.r = 255;
	// color.g = 255;
	// color.b = 255;
	// color.alpha = 255;
	// //sb.draw(glm::vec4(WIDTH/2,HEIGHT/2,200,200),glm::vec4(0,0,1,1),text.id,0,color);
	// sb.draw(glm::vec4(0,0,100,100),glm::vec4(0,0,1,1),text.id,0,color);
	// sb.draw(glm::vec4(1000,1000,1000,1000),glm::vec4(0,0,1,1),text.id,0,color);
	// for(int i = 0; i < bullets.size();i++)
	// {
	// 	bullets[i].draw(sb);
	// }
	//
	// sb.end();
	// sb.renderBatch();

	levels[currentLevel]->draw();

	glBindTexture(GL_TEXTURE_2D, 0);


	colorProg.unuse();

	glfwSwapBuffers(WindowManager::window);
}

void MainGame::initShaders()
{
	colorProg.compileShaders("../Shaders/TextureShader.vert", "../Shaders/TextureShader.frag");
	colorProg.addAttribute("vertexPosition");
	colorProg.addAttribute("vertexColor");
	colorProg.addAttribute("vertexUV");
	colorProg.linkShaders();
}

void MainGame::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static int currentFrame = 0;
	static float frameTimes[NUM_SAMPLES];
	static float previousTime = glfwGetTime();
	float currentTime = glfwGetTime();

	deltaTime = currentTime - previousTime;

	frameTimes[currentFrame%NUM_SAMPLES] = deltaTime;

	previousTime = currentTime;
	currentFrame++;

	int count;
	if(currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;
	for(int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if(frameTimeAverage > 0)
		fps = 1000.0f / frameTimeAverage;
	else
		fps = 60.0f;
}
