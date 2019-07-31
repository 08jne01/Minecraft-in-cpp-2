#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>
class EventHandler

{
public:
	EventHandler(Camera& cam);
	void keyHandler(int action, int button);
	void mouseHandler(double x, double y);

private:

	Camera& camera;
};