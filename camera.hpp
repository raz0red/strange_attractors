#ifndef camera_hpp
#define camera_hpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <cmath>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

float degToRad(float degrees)
{
	return degrees * (M_PI / 180);
}

class Camera
{
private:
	// if it is the first instance of the cursor being measured
	bool firstMouse;
	// the last x pos of the camera
	float lastX;
	// the last y pos of the camera
	float lastY;
	// the x axis rotation of the camera
	float pitch;
	// the y axis rotation of the camera
	float yaw;
	// the z axis rotation of the camera
	float roll;
	// the cam position vector
	float camPos[3];

	void updateCamPos()
	{
		camPos[0] = cos(degToRad(yaw)) * cos(degToRad(pitch));
		camPos[1] = sin(degToRad(pitch));
		camPos[2] = sin(degToRad(yaw)) * cos(degToRad(pitch));
	}

public:
	Camera()
	{
		firstMouse = true;
		lastX = 400;
		lastY = 300;
		pitch = 0.2;
		yaw = 0.2;
		roll = 0.0;
		camPos[0] = cos(degToRad(yaw)) * cos(degToRad(pitch));
		camPos[1] = sin(degToRad(pitch));
		camPos[2] = sin(degToRad(yaw)) * cos(degToRad(pitch));
	};
	~Camera(){}; // deconstructor
	void ortho()
	{
		// set up the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-5, 5, -5, 5, 10, -10);
	};
	void trackCursor(double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

#ifndef __EMSCRIPTEN__
		float sensitivity = 0.15f;
#else
		float sensitivity = 0.55f;
#endif
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// clamp pitch to prevent auto flipping due to "up" vector
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		updateCamPos();
	};

	void trackKeys(int key, int scancode, int action, int mods)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT:
			roll -= 0.1;
			if (roll < -1)
			{
				roll = -1;
			}
			break;
		case GLFW_KEY_RIGHT:
			roll += 0.1;
			if (roll > 1)
			{
				roll = 1;
			}
			break;
		default:
			break;
		}
		updateCamPos();
	};
#ifdef __EMSCRIPTEN__
	#define PI 3.14159
	float rotation(float in) {
		return (in > 0 ? in : (2*PI + in)) * 360 / (2*PI);
	}
#endif
	void updatePosition()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
#ifndef __EMSCRIPTEN__
		gluLookAt(camPos[0], camPos[1], camPos[2],
							0, 0, 0,
							0, 1, roll);
#else
		float rot_y = rotation(atan2(-camPos[0], camPos[2]));
		float len_xz = hypot(-camPos[0], -camPos[2]);
		float rot_x = rotation(atan2(-camPos[1], len_xz));
		glRotatef(rot_x, -1, 0, 0);
		glRotatef(rot_y, 0, 1, roll);
		glTranslatef(-camPos[0], -camPos[1], -camPos[2]);
#endif
	};
};
// end class Camera

#endif
