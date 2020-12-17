#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class CubeClass
{
public:
	

    CubeClass(float offsetx, float offsety, float offsetz)
    {
        position = glm::vec3(offsetx, offsety, offsetz);
    }

	glm::vec3 getPosition() const;

private:

	unsigned int status = 0;

	glm::vec3 position;
};

