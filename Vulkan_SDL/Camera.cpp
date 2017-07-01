#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

bool Camera::moving()
{
	return keys.left || keys.right || keys.up || keys.down;
}

void Camera::moved(float deltaTime)
{
	if (moving())
	{
		glm::vec3 camFront;
		camFront.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
		camFront.y = sin(glm::radians(rotation.x));
		camFront.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
		camFront = glm::normalize(camFront);

		float moveSpeed = movementSpeed;

		if (keys.up) {
			position -= glm::normalize(glm::cross(camFront, glm::vec3(1.0f, 0.0f, 0.0f)))  * moveSpeed;
		}
		if (keys.down) {
			position += glm::normalize(glm::cross(camFront, glm::vec3(1.0f, 0.0f, 0.0f)))  * moveSpeed;
		}
		if (keys.left) {
			position -= glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;
		}
		if (keys.right) {
			position += glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;
		}
		updateMatrix();
	}
};

void Camera::translate(glm::vec3 delta)
{
	position += delta;
	updateMatrix();
}

void Camera::rotate(glm::vec3 delta)
{
	rotation += delta;
	updateMatrix();
}

void Camera::updateMatrix()
{
	glm::mat4 rotM = glm::mat4();
	glm::mat4 transM;

	rotM = glm::rotate(rotM, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotM = glm::rotate(rotM, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotM = glm::rotate(rotM, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	transM = glm::translate(glm::mat4(), position);

	view = transM * rotM;
};

void Camera::setPerspective(float fov, float aspect, float znear, float zfar)
{
	this->fov = fov;
	this->znear = znear;
	this->zfar = zfar;
	perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
};
void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
	updateMatrix();
}