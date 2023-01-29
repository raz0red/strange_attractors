
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <cmath>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Common/Types.hpp"
#include "Common/Utilites.hpp"

#include "Camera/Camera.hpp"

#include "Attractors/Attractor.hpp"
#include "Attractors/Thomas.hpp"
#include "Attractors/Lorenz.hpp"
#include "Attractors/Halvorsen.hpp"
#include "Attractors/Aizawa.hpp"

#include "ParticleSystem/ParticleSystem.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace cmn;

GLFWwindow *window;
Camera camera = Camera();
std::set<Particle *> Particle::instances;
static ParticleSystem<Attractors::Thomas> particleSystem;

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	camera.trackKeys(key, scancode, action, mods);
};

static void cursorCallback(GLFWwindow *window, double xpos, double ypos)
{
	camera.trackCursor(xpos, ypos);
};

std::vector<Particle> particles;
static void genParticles()
{
	auto initialPoints = genCoordinates(10.0, 10.0, 10.0, 2.5);
	for (int i = 0; i < initialPoints.size(); i++)
	{
		ColorRGB3f color = genRandomPastel();
		Particle newParticle = Particle(initialPoints[i], color);
		particles.push_back(newParticle);
	}
}

extern "C" void main_loop()
{
	glClearColor(0.18f, 0.188f, 0.278f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.updatePosition();

	particleSystem.Tick();

	glfwSwapBuffers(window);
	glfwPollEvents();
};

extern "C" void setWindowSize(int w, int h)
{
	printf("%d, %d\n", w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSetWindowSize(window, w, h);
	glViewport(0, 0, w, h);
}

int main(int argc, const char *argv[])
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

#ifdef __EMSCRIPTEN__
	window = glfwCreateWindow(1280, 969, "Strange Attractors", NULL, NULL);
#else
	window = glfwCreateWindow(1440, 1440, "Strange Attractors", NULL, NULL);
#endif

	if (window == NULL)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	camera.ortho();

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	genParticles();

#ifdef __EMSCRIPTEN__
	// 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
	// emscripten_set_main_loop(main_loop, 0, 1);
#else
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
				 glfwWindowShouldClose(window) == 0)
	{
		main_loop();
	}
	glfwTerminate();
#endif
	return 0;
}
