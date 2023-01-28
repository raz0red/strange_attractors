#include "camera.hpp"
#include "points.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

GLFWwindow *window;
Camera camera = Camera();

float normalize(float x, float min, float max)
{
  return (x - min) / (max - min);
};

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  camera.trackKeys(key, scancode, action, mods);
};

void cursorCallback(GLFWwindow *window, double xpos, double ypos)
{
  camera.trackCursor(xpos, ypos);
};

std::set<Particle *> Particle::instances;
Coordinate3f initialPoints[20] = {
    {.x = 2.09f, .y = 2.1f, .z = -0.01f},
    {.x = 2.1f, .y = 2.1f, .z = -0.01f},
    {.x = 2.11f, .y = 2.1f, .z = -0.01f},
    {.x = 2.12f, .y = 2.1f, .z = -0.01f},
    {.x = 2.13f, .y = 2.1f, .z = -0.01f},
    {.x = 2.14f, .y = 2.1f, .z = -0.01f},
    {.x = 2.15f, .y = 2.1f, .z = -0.01f},
    {.x = 2.16f, .y = 2.1f, .z = -0.01f},
    {.x = 2.17f, .y = 2.1f, .z = -0.01f},
    {.x = 2.18f, .y = 2.1f, .z = -0.01f},
    {.x = 2.09f, .y = -5.1f, .z = -2.01f},
    {.x = 2.1f, .y = -5.1f, .z = -2.01f},
    {.x = 2.11f, .y = -5.1f, .z = -2.01f},
    {.x = 2.12f, .y = -5.1f, .z = -2.01f},
    {.x = 2.13f, .y = -5.1f, .z = -2.01f},
    {.x = 2.14f, .y = -5.1f, .z = -2.01f},
    {.x = 2.15f, .y = -5.1f, .z = -2.01f},
    {.x = 2.16f, .y = -5.1f, .z = -2.01f},
    {.x = 2.17f, .y = -5.1f, .z = -2.01f},
    {.x = 2.18f, .y = -5.1f, .z = -2.01f},
};
std::vector<Particle> particles;
ColorRGB3f particleColor = {.r = 0.58f, .g = 0.631f, .b = 0.31f};
void genParticles()
{
  for (int i = 0; i < 20; i++)
  {
    Particle newParticle = Particle(initialPoints[i], particleColor);
    particles.push_back(newParticle);
  }
}

static ParticleSystem particleSystem;

static void main_loop() {
  glClearColor(0.208, 0.231, 0.09, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  camera.updatePosition();

  particleSystem.Tick();

  glfwSwapBuffers(window);
  glfwPollEvents();
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
  window = glfwCreateWindow(640, 480, "Strange Attractors", NULL, NULL);
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

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  camera.ortho();

  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, cursorCallback);
  genParticles();

#ifdef __EMSCRIPTEN__
    // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0) {
      main_loop();
  }
#endif
  glfwTerminate();
  return 0;
}

// void halvorsen()
// {
// 	double a = 1.89;
// 	double h = 0.03;

// 	double dx = (-a * x - 4 * y - 4 * z - (y * y)) * dt;
// 	double dy = (-a * y - 4 * z - 4 * x - (z * z)) * dt;
// 	double dz = (-a * z - 4 * x - 4 * y - (x * x)) * dt;

// 	x += h * dx;
// 	y += h * dy;
// 	z += h * dz;
// 	createPoint(x, y, z);
// }

// void aizawa()
// {
// 	double a = 0.95;
// 	double b = 0.7;
// 	double c = 0.6;
// 	double d = 3.5;
// 	double e = 0.25;
// 	double f = 0.1;
// 	double h = 0.03;

// 	double dx = ((z - b) * x - d * y) * dt;
// 	double dy = (d * x + (z - b) * y) * dt;
// 	double dz = (c + (a * z) - ((z * z * z) / 3) -
// 							 ((x * x) + (y * y)) * (1 + (e * z)) // ((x * x) + (e * z * (x * x)) + (y * y) + (e * z * (y * y)))
// 							 + f * z * (x * x * x)) *
// 							dt;

// 	x += h * dx;
// 	y += h * dy;
// 	z += h * dz;
// 	createPoint(x, y, z);
// }
