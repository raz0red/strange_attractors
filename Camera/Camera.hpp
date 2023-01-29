#ifndef Camera_hpp
#define Camera_hpp

using namespace cmn;

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
	Coordinate3f camPos;

	void updateCamPos()
	{
		Coordinate3f newPos = {
				.x = cos(degToRad(yaw)) * cos(degToRad(pitch)),
				.y = sin(degToRad(pitch)),
				.z = sin(degToRad(yaw)) * cos(degToRad(pitch))};
		camPos = newPos;
	};

public:
	Camera()
	{
		firstMouse = true;
		lastX = 400;
		lastY = 300;
		pitch = 0.2;
		yaw = 0.2;
		roll = 0.0;
		updateCamPos();
	};
	~Camera(){}; // deconstructor
	void ortho()
	{
		// set up the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10, 10, -10, 10, 200, -200);
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

		float sensitivity = 0.15f;
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
	void updatePosition()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camPos.x, camPos.y, camPos.z,
							0, 0, 0,
							0, 1, roll);
	};
};
// end class Camera

#endif
