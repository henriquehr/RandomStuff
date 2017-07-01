#pragma once

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();
	bool moving();
	void moved(float deltaTime);
	void translate(glm::vec3 delta);
	void rotate(glm::vec3 delta);
	void setPerspective(float fov, float aspect, float znear, float zfar);
	void setPosition(glm::vec3 position);
	glm::mat4 view = glm::mat4();
	glm::mat4 perspective = glm::mat4();
	struct
	{
		bool up = false;
		bool left = false;
		bool down = false;
		bool right = false;
	}keys;
private:
	float movementSpeed = 0.005;
	glm::vec3 position = glm::vec3();
	glm::vec3 rotation = glm::vec3();
	float fov, zfar, znear;

	void updateMatrix();
};

