#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeClass
{
public:
	static const float vertices[];

	glm::vec3 position;

	CubeClass(float, float, float);
};

