#include <Game.h>



Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
	initialize();
}

Game::~Game() {}

void Game::run()
{


	Event event;

	while (isRunning)
	{

		//cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
			update();
			render();
		}
	}
}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vert;

Vert initialVertex[36];
Vert finalVertexes[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	initializeVertexes();
	//setup colours
	for (int i = 0; i < 36; i++)
	{
		// this makes them pink. i like pink
		initialVertex[i].color[0] = (rand() % 31) / 10.0f;
		initialVertex[i].color[1] = (rand() % 31) / 10.0f;
		initialVertex[i].color[2] = (rand() % 31) / 10.0f;
	}

	//setup index
	for (int i = 0; i < 36; i++)
	{
		triangles[i] = i;
	}

	for (int i = 0; i < 36; i++)
	{
		finalVertexes[i] = initialVertex[i];
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, finalVertexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Game::update()
{
	if (Keyboard::isKeyPressed(Keyboard::Y))
	{
		m_rotationZ += 2.0f;
		m_rotationX += 2.0f;
		// IT NO WORK I GIVE UP AAAARGH i know the problem is me probably not updating the right thing but aaaaah
	}

		
	for (int i = 0; i < 36; i++)
	{
		MyVector3 vertCalc{ initialVertex[i].coordinate[0], initialVertex[i].coordinate[1],initialVertex[i].coordinate[2] };
		vertCalc = MyMatrix3::scale(m_scalar) * vertCalc;
		vertCalc += m_displacement;
		vertCalc = MyMatrix3::rotationX(m_rotationX) * vertCalc;
		vertCalc = MyMatrix3::rotationY(m_rotationY) * vertCalc;
		vertCalc = MyMatrix3::rotationZ(m_rotationZ) * vertCalc;

		finalVertexes[i].coordinate[0] = vertCalc.x;
		finalVertexes[i].coordinate[1] = vertCalc.y;
		finalVertexes[i].coordinate[2] = vertCalc.z;
	}
}

void Game::render()
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
	CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, initialVertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
	model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	

	glDeleteBuffers(1, vbo);
}


void Game::initializeVertexes()
{
	// i could do this with only 8 points
	// but that's what i call mental gymnastics. 
	// and i'm not flexible 

	// well it is technically 8 points, they're just repeated. 
	initialVertex[0].coordinate[0] = -0.5f;
	initialVertex[0].coordinate[1] = -0.5f;
	initialVertex[0].coordinate[2] = -0.5f;

	initialVertex[1].coordinate[0] = -0.5f;
	initialVertex[1].coordinate[1] = -0.5f;
	initialVertex[1].coordinate[2] = 0.5f;

	initialVertex[2].coordinate[0] = -0.5f;
	initialVertex[2].coordinate[1] = 0.5f;
	initialVertex[2].coordinate[2] = -0.5f;

	initialVertex[3].coordinate[0] = 0.5f;
	initialVertex[3].coordinate[1] = 0.5f;
	initialVertex[3].coordinate[2] = -0.5f;

	initialVertex[4].coordinate[0] = -0.5f;
	initialVertex[4].coordinate[1] = -0.5f;
	initialVertex[4].coordinate[2] = -0.5f;

	initialVertex[5].coordinate[0] = -0.5f;
	initialVertex[5].coordinate[1] = 0.5f;
	initialVertex[5].coordinate[2] = -0.5f;

	initialVertex[6].coordinate[0] = 0.5f;
	initialVertex[6].coordinate[1] = -0.5f;
	initialVertex[6].coordinate[2] = 0.5f;

	initialVertex[7].coordinate[0] = -0.5f;
	initialVertex[7].coordinate[1] = -0.5f;
	initialVertex[7].coordinate[2] = -0.5f;

	initialVertex[8].coordinate[0] = 0.5f;
	initialVertex[8].coordinate[1] = -0.5f;
	initialVertex[8].coordinate[2] = -0.5f;

	initialVertex[9].coordinate[0] = 0.5f;
	initialVertex[9].coordinate[1] = 0.5f;
	initialVertex[9].coordinate[2] = -0.5f;

	initialVertex[10].coordinate[0] = 0.5f;
	initialVertex[10].coordinate[1] = -0.5f;
	initialVertex[10].coordinate[2] = -0.5f;

	initialVertex[11].coordinate[0] = -0.5f;
	initialVertex[11].coordinate[1] = -0.5f;
	initialVertex[11].coordinate[2] = -0.5f;

	initialVertex[12].coordinate[0] = -0.5f;
	initialVertex[12].coordinate[1] = -0.5f;
	initialVertex[12].coordinate[2] = 0.5f;

	initialVertex[13].coordinate[0] = -0.5f;
	initialVertex[13].coordinate[1] = 0.5f;
	initialVertex[13].coordinate[2] = 0.5f;

	initialVertex[14].coordinate[0] = -0.5f;
	initialVertex[14].coordinate[1] = 0.5f;
	initialVertex[14].coordinate[2] = -0.5f;

	initialVertex[15].coordinate[0] = 0.5f;
	initialVertex[15].coordinate[1] = -0.5f;
	initialVertex[15].coordinate[2] = 0.5f;

	initialVertex[16].coordinate[0] = -0.5f;
	initialVertex[16].coordinate[1] = -0.5f;
	initialVertex[16].coordinate[2] = 0.5f;

	initialVertex[17].coordinate[0] = -0.5f;
	initialVertex[17].coordinate[1] = -0.5f;
	initialVertex[17].coordinate[2] = -0.5f;

	initialVertex[18].coordinate[0] = -0.5f;
	initialVertex[18].coordinate[1] = 0.5f;
	initialVertex[18].coordinate[2] = 0.5f;

	initialVertex[19].coordinate[0] = -0.5f;
	initialVertex[19].coordinate[1] = -0.5f;
	initialVertex[19].coordinate[2] = 0.5f;

	initialVertex[20].coordinate[0] = 0.5f;
	initialVertex[20].coordinate[1] = -0.5f;
	initialVertex[20].coordinate[2] = 0.5f;

	initialVertex[21].coordinate[0] = 0.5f;
	initialVertex[21].coordinate[1] = 0.5f;
	initialVertex[21].coordinate[2] = 0.5f;

	initialVertex[22].coordinate[0] = 0.5f;
	initialVertex[22].coordinate[1] = -0.5f;
	initialVertex[22].coordinate[2] = -0.5f;

	initialVertex[23].coordinate[0] = 0.5f;
	initialVertex[23].coordinate[1] = 0.5f;
	initialVertex[23].coordinate[2] = -0.5f;

	initialVertex[24].coordinate[0] = 0.5f;
	initialVertex[24].coordinate[1] = -0.5f;
	initialVertex[24].coordinate[2] = -0.5f;

	initialVertex[25].coordinate[0] = 0.5f;
	initialVertex[25].coordinate[1] = 0.5f;
	initialVertex[25].coordinate[2] = 0.5f;

	initialVertex[26].coordinate[0] = 0.5f;
	initialVertex[26].coordinate[1] = -0.5f;
	initialVertex[26].coordinate[2] = 0.5f;

	initialVertex[27].coordinate[0] = 0.5f;
	initialVertex[27].coordinate[1] = 0.5f;
	initialVertex[27].coordinate[2] = 0.5f;

	initialVertex[28].coordinate[0] = 0.5f;
	initialVertex[28].coordinate[1] = 0.50f;
	initialVertex[28].coordinate[2] = -0.5f;

	initialVertex[29].coordinate[0] = -0.5f;
	initialVertex[29].coordinate[1] = 0.5f;
	initialVertex[29].coordinate[2] = -0.5f;

	initialVertex[30].coordinate[0] = 0.5f;
	initialVertex[30].coordinate[1] = 0.5f;
	initialVertex[30].coordinate[2] = 0.5f;

	initialVertex[31].coordinate[0] = -0.5f;
	initialVertex[31].coordinate[1] = 0.5f;
	initialVertex[31].coordinate[2] = -0.5f;

	initialVertex[32].coordinate[0] = -0.5f;
	initialVertex[32].coordinate[1] = 0.5f;
	initialVertex[32].coordinate[2] = 0.5f;

	initialVertex[33].coordinate[0] =0.5f;
	initialVertex[33].coordinate[1] = 0.5f;
	initialVertex[33].coordinate[2] = 0.5f;

	initialVertex[34].coordinate[0] = -0.5f;
	initialVertex[34].coordinate[1] = 0.5f;
	initialVertex[34].coordinate[2] = 0.5f;

	initialVertex[35].coordinate[0] = 0.5f;

	initialVertex[35].coordinate[1] = -0.5f;
	initialVertex[35].coordinate[2] = 00.5f;
}