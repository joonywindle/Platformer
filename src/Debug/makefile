all:
	g++ -c ../Bullet.cpp -std=c++11 -Wall
	g++ -c ../Camera2D.cpp -std=c++11 -Wall
	g++ -c ../GLSLProg.cpp -std=c++11 -Wall
	g++ -c ../ImageLoader.cpp -std=c++11 -Wall
	g++ -c ../InputManager.cpp -std=c++11 -Wall
	g++ -c ../IOManager.cpp -std=c++11 -Wall
	g++ -c ../MainGame.cpp -std=c++11 -Wall
	g++ -c ../picopng.cpp -std=c++11 -Wall
	g++ -c ../ResourceManager.cpp -std=c++11 -Wall
	g++ -c ../Sprite.cpp -std=c++11 -Wall
	g++ -c ../SpriteBatch.cpp -std=c++11 -Wall
	g++ -c ../TextureCache.cpp -std=c++11 -Wall
	g++ -c ../WindowManager.cpp -std=c++11 -Wall
	g++ -c ../main.cpp -std=c++11 -Wall
	g++ main.o Bullet.o Camera2D.o GLSLProg.o ImageLoader.o InputManager.o IOManager.o MainGame.o picopng.o ResourceManager.o Sprite.o SpriteBatch.o TextureCache.o WindowManager.o -std=c++11 -Wall -L ../../../../../glfw-3.2.1/src/ -l glfw3 -l GL -l GLEW -l dl -l GLU -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread
run:
	./a.out
