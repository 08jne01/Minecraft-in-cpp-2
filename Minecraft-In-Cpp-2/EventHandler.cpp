#include "EventHandler.h"
#include <iostream>
EventHandler::EventHandler(Camera& cam) : camera(cam)

{

}

void EventHandler::keyHandler(int action, int button)

{
	if (action == GLFW_PRESS)

	{
		switch (button)

		{
		case GLFW_KEY_W:
		{
			camera.setVel(2, 1.0);
			break;
		}

		case GLFW_KEY_A:
		{
			camera.setVel(0, 1.0);
			break;
		}

		case GLFW_KEY_S:
		{
			camera.setVel(2, -1.0);
			break;
		}

		case GLFW_KEY_D:
		{
			camera.setVel(0, -1.0);
			break;
		}

		case GLFW_KEY_LEFT_SHIFT:
		{
			camera.speed = 0.5;
			break;
		}

		case GLFW_KEY_SPACE:
		{
			camera.setVel(1, -1.0);
			break;
		}

		case GLFW_KEY_LEFT_CONTROL:
		{
			camera.setVel(1, 1.0);
			break;
		}
		}
	}

	if (action == GLFW_RELEASE)

	{
		switch (button)

		{
			case GLFW_KEY_W:
			{
				camera.setVel(2, 0.0);
				break;
			}

			case GLFW_KEY_A:
			{
				camera.setVel(0, 0.0);
				break;
			}

			case GLFW_KEY_S:
			{
				camera.setVel(2, 0.0);
				break;
			}

			case GLFW_KEY_D:
			{
				camera.setVel(0, 0.0);
				break;
			}

			case GLFW_KEY_LEFT_SHIFT:
			{
				camera.speed = 0.1;
				break;
			}

			case GLFW_KEY_SPACE:
			{
				camera.setVel(1, 0.0);
				break;
			}

			case GLFW_KEY_LEFT_CONTROL:
			{
				camera.setVel(1, 0.0);
				break;
			}
		}
	}
}

void EventHandler::mouseHandler(double x, double y)

{
	camera.setAngVel(x, y);
}