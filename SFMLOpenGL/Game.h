#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <MyVector3.h>
#include <InitialMyMatrix3.h>

using namespace std;
using namespace sf;


class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void initializeVertexes();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	float m_rotationY = 0.0f;
	float m_rotationX = 0.0f;
	float m_rotationZ = 0.0f;
	float m_scalar = 1.0f;
	MyVector3 m_displacement{ 0,0,1 };
	MyVector3 translationVector = { 0,0,1 };
};