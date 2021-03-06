#include "Camera.h"
#include <iostream>


glm::vec3 input(0);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);


float pitch = 0.0f;
float yaw = -90.0f;


float lastX = 400, lastY = 400;
bool firstMouse = false;
bool jump = false;



glm::vec3 p1(0, 0, 0);
glm::vec3 p2(0, -4, 0);


bool kak = false;





void processInput(GLFWwindow *window, float deltaTime)
{
	input = glm::vec3(0,0,0);
	jump = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		input.z += 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		input.z -= 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		input.x -= 1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		input.x += 1;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		jump = true;


	if(input.x != 0 || input.y != 0)
		input = glm::normalize(input);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}






Camera::Camera(GLFWwindow* window) : window(window), cameraPos(0.0f, 55.0f, 0.0f), currentChunk(nullptr)
{
	glfwSetCursorPosCallback(window, mouse_callback);
	yVelocity = 0;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	hitbox[0] = glm::vec3(-0.3f, 0.05f, -0.3f);
	hitbox[1] = glm::vec3(0.3f, 0.05f, -0.3f);
	hitbox[2] = glm::vec3(0.3f, 0.05f, 0.3f);
	hitbox[3] = glm::vec3(-0.3f, 0.05f, 0.3f);

	hitbox[4] = glm::vec3(-0.3f, -1.9f, -0.3f);
	hitbox[5] = glm::vec3(0.3f, -1.9f, -0.3f);
	hitbox[6] = glm::vec3(0.3f, -1.9f, 0.3f);
	hitbox[7] = glm::vec3(-0.3f, -1.9f, 0.3f);



}

glm::mat4 Camera::getView(const float & deltaTime)
{

	processInput(window, deltaTime);


	glm::vec3 direction(1.0f);
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	glm::vec3 camFront = glm::normalize(direction);
	cameraFront = camFront;


	yVelocity -= deltaTime * 25;
	


	glm::vec3 velocity = (input.z * (deltaTime * 7.0f) * glm::normalize(glm::vec3(camFront.x, 0, cameraFront.z)));
	velocity += (input.x * (deltaTime * 7.0f) * glm::normalize(glm::cross(glm::vec3(camFront.x,0,cameraFront.z), glm::vec3(0,1,0))));
	glm::vec3 nextPos = glm::vec3(velocity.x, yVelocity * deltaTime, velocity.z);


	//X
	if(!CheckAll(glm::vec3(cameraPos.x + nextPos.x,cameraPos.y, cameraPos.z)))
		cameraPos.x += velocity.x;

	//Y
	if (!CheckAll(glm::vec3(cameraPos.x, cameraPos.y + nextPos.y, cameraPos.z))) {

		cameraPos.y += yVelocity * deltaTime;
	}
	else {

		if (yVelocity <= 0) {
			if (jump) {
				yVelocity = 8.0f;
			}
			else {
				yVelocity = 0;
			}
		}
		else {
			yVelocity = 0;
		}

		
		
	}

	//Z
	if (!CheckAll(glm::vec3(cameraPos.x,cameraPos.y, cameraPos.z + nextPos.z)))
		cameraPos.z += velocity.z;

	

	//std::cout << relativeCamPos.x << "  " << relativeCamPos.y << "  " << relativeCamPos.z << std::endl;
	//std::cout << cameraPos.x << "  " << cameraPos.y << "  " << cameraPos.z << std::endl;



	return glm::lookAt(cameraPos, cameraPos + camFront, cameraUp);
}

bool Camera::CheckAll(glm::vec3 pos) {

	bool temp = false;
	for (int i = 0; i < 8; i++)
	{
		if (CheckCollision(hitbox[i] + pos)) {
			temp = true;
			break;
		}
	}
	
	return temp;

}


bool Camera::CheckCollision(glm::vec3 pos)
{   
	
	glm::vec3 gridPos(std::round(pos.x), std::round(pos.y), std::round(pos.z));
	Block b = m->GetBlock(gridPos.x, gridPos.y, gridPos.z);
	int type = b.getType();

	if (b.getType() == blockType::Air) {
			
			return false;	
			
	}

	return true;

}


