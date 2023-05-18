#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <ctime>
#include <chrono>

#include <GLFW/glfw3.h>

#define M_PI 3.14159265358979323846

const int WIDTH = 640;
const int HEIGHT = 480;

void getCurrentTime(int& hours, int& minutes, int& seconds) {
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	std::tm localtime;
	
	localtime_s(&localtime, &time);

	hours = localtime.tm_hour;
	minutes = localtime.tm_min;
	seconds = localtime.tm_sec;
}

void drawCircle(float x, float y, float radius)
{
	int sides = 100;
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255, 255, 255);
	glVertex2f(x, y);
	for (int i = 0; i <= sides; i++)
	{
		float angle = i / (float)sides * 2.0f * 3.14159f;
		float px = x + radius * cosf(angle);
		float py = y + radius * sinf(angle);
		glVertex2f(px, py);
	}
	glEnd();
}

void drawLine(float x1, float y1, float angle, float length, float width)
{
	float x2 = x1 + length * cos(angle * M_PI / 180);
	float y2 = y1 + length * sin(angle * M_PI / 180);
	float dx = width * sin(angle * M_PI / 180);
	float dy = width * cos(angle * M_PI / 180);

	glPushMatrix();
	glTranslatef(x1, y1, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x1, -y1, 0.0f);

	glBegin(GL_QUADS);
	glColor3ub(0, 255, 0);
	glVertex2f(x1 - dx, y1 + dy);
	glVertex2f(x1 + dx, y1 - dy);
	glVertex2f(x2 + dx, y2 - dy);
	glVertex2f(x2 - dx, y2 + dy);
	glEnd();

	glPopMatrix();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
	glOrtho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f); // изменение направления оси Y
    glMatrixMode(GL_MODELVIEW);
}

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab3Task2", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	resize(WIDTH, HEIGHT);

	int hours, minutes, seconds;
	while (!glfwWindowShouldClose(window)) {
		getCurrentTime(hours, minutes, seconds);

		float hoursAngle = (hours * 30.0f) + (minutes / 2.0f);
		float minutesAngle = minutes * 3.0f;
		float secondsAngle = seconds * 3.0f;

		glClear(GL_COLOR_BUFFER_BIT);

		// Draw something here
		drawCircle(WIDTH / 2, HEIGHT / 2, 100.0f);
		drawLine(WIDTH / 2, HEIGHT / 2, minutesAngle, 60.0f, 2.0f);
		drawLine(WIDTH / 2, HEIGHT / 2, -hoursAngle, 40.0f, 2.0f);
		drawLine(WIDTH / 2, HEIGHT / 2, secondsAngle, 80.0f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}