#include <iostream>
#include <cmath>
#include <vector>

#include <GLFW/glfw3.h>

const int WIDTH = 640;
const int HEIGHT = 480;

void drawParabola(float a, float b, float c)
{
	glBegin(GL_POINTS);
	for (float x = -10.0f; x <= 10.0f; x += 0.01f)
	{
		float y = a * x * x + b * x + c;
		glVertex2f(x, y);
	}
	glEnd();
}

void drawX(float cx, float cy)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(cx - 100.0f, cy);
	glVertex2f(cx + 100.0f, cy);
	glEnd();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab3Task1", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	resize(WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw something here
		drawX(0.0f, 0.0f);
		drawParabola(5.0f, 2.0f, 2.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}