//#include <gl\GL.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//http://www.glfw.org/docs/latest/


struct AppConfiguration
{
	int Width;
	int Height;

	AppConfiguration()
		: Width(1024)
		, Height(768)
	{
	}
};

struct Paddles
{
	float Paddle1Color[3];
	float Paddle1Vertices[8];
	float Paddle2Color[3];
	float Paddle2Vertices[8];
};

struct GameState
{

};

void Setup(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(3);
}

void InitPaddleContent(Paddles& PaddleData)
{
	PaddleData.Paddle1Color[0] = 1.0f;
	PaddleData.Paddle1Color[1] = 0.0f;
	PaddleData.Paddle1Color[2] = 0.0f;

	PaddleData.Paddle1Vertices[0] = -0.9f;
	PaddleData.Paddle1Vertices[1] = 0.9f;
	PaddleData.Paddle1Vertices[2] = -0.9f;
	PaddleData.Paddle1Vertices[3] = 0.5f;
	PaddleData.Paddle1Vertices[4] = -0.8f;
	PaddleData.Paddle1Vertices[5] = 0.5f;
	PaddleData.Paddle1Vertices[6] = -0.8f;
	PaddleData.Paddle1Vertices[7] = 0.9f;

	PaddleData.Paddle2Color[0] = 0.0f;
	PaddleData.Paddle2Color[1] = 0.0f;
	PaddleData.Paddle2Color[2] = 1.0f;

	PaddleData.Paddle2Vertices[0] = 0.8f;
	PaddleData.Paddle2Vertices[1] = 0.0f;
	PaddleData.Paddle2Vertices[2] = 0.8f;
	PaddleData.Paddle2Vertices[3] = -0.4f;
	PaddleData.Paddle2Vertices[4] = 0.9f;
	PaddleData.Paddle2Vertices[5] = -0.4f;
	PaddleData.Paddle2Vertices[6] = 0.9f;
	PaddleData.Paddle2Vertices[7] = 0.0f;
}

void Render(const Paddles& PaddleData)
{
	// Draw paddle 1
	glBegin(GL_POLYGON);
	glColor3f(PaddleData.Paddle1Color[0], PaddleData.Paddle1Color[1], PaddleData.Paddle1Color[2]);
	glVertex3f(PaddleData.Paddle1Vertices[0], PaddleData.Paddle1Vertices[1], 0.0f);
	glVertex3f(PaddleData.Paddle1Vertices[2], PaddleData.Paddle1Vertices[3], 0.0f);
	glVertex3f(PaddleData.Paddle1Vertices[4], PaddleData.Paddle1Vertices[5], 0.0f);
	glVertex3f(PaddleData.Paddle1Vertices[6], PaddleData.Paddle1Vertices[7], 0.0f);
	glEnd();

	// Draw paddle 2
	glBegin(GL_POLYGON);
	glColor3f(PaddleData.Paddle2Color[0], PaddleData.Paddle2Color[1], PaddleData.Paddle2Color[2]);
	glVertex3f(PaddleData.Paddle2Vertices[0], PaddleData.Paddle2Vertices[1], 0.0f);
	glVertex3f(PaddleData.Paddle2Vertices[2], PaddleData.Paddle2Vertices[3], 0.0f);
	glVertex3f(PaddleData.Paddle2Vertices[4], PaddleData.Paddle2Vertices[5], 0.0f);
	glVertex3f(PaddleData.Paddle2Vertices[6], PaddleData.Paddle2Vertices[7], 0.0f);
	glEnd();
}

int main(void)
{
    // Initialize the library
    if (!glfwInit())
        return -1;

	AppConfiguration Settings;
	Paddles P;

    // Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(Settings.Width, Settings.Height, "Pong", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current 
	glfwMakeContextCurrent(window);

	Setup();
	InitPaddleContent(P);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
		}

		glfwGetFramebufferSize(window, &Settings.Width, &Settings.Height);
		glViewport(0, 0, Settings.Width, Settings.Height);
		glClearColor(0.2f, 0.2f, 0.2f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render here
		Render(P);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

	glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}