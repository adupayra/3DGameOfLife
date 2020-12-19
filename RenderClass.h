#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Grid.h"
#include <iostream>
#include <thread>
#include <chrono>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

static float step = 1/(float)SIZEOFWORLD;

static float vertices[] = {
	-step, -step, -step,  0.0f, 0.0f,
	 step, -step, -step,  1.0f, 0.0f,
	 step,  step, -step,  1.0f, 1.0f,
	 step,  step, -step,  1.0f, 1.0f,
	-step,  step, -step,  0.0f, 1.0f,
	-step, -step, -step,  0.0f, 0.0f,

	-step, -step,  step,  0.0f, 0.0f,
	 step, -step,  step,  1.0f, 0.0f,
	 step,  step,  step,  1.0f, 1.0f,
	 step,  step,  step,  1.0f, 1.0f,
	-step,  step,  step,  0.0f, 1.0f,
	-step, -step,  step,  0.0f, 0.0f,

	-step,  step,  step,  1.0f, 0.0f,
	-step,  step, -step,  1.0f, 1.0f,
	-step, -step, -step,  0.0f, 1.0f,
	-step, -step, -step,  0.0f, 1.0f,
	-step, -step,  step,  0.0f, 0.0f,
	-step,  step,  step,  1.0f, 0.0f,

	 step,  step,  step,  1.0f, 0.0f,
	 step,  step, -step,  1.0f, 1.0f,
	 step, -step, -step,  0.0f, 1.0f,
	 step, -step, -step,  0.0f, 1.0f,
	 step, -step,  step,  0.0f, 0.0f,
	 step,  step,  step,  1.0f, 0.0f,

	-step, -step, -step,  0.0f, 1.0f,
	 step, -step, -step,  1.0f, 1.0f,
	 step, -step,  step,  1.0f, 0.0f,
	 step, -step,  step,  1.0f, 0.0f,
	-step, -step,  step,  0.0f, 0.0f,
	-step, -step, -step,  0.0f, 1.0f,

	-step,  step, -step,  0.0f, 1.0f,
	 step,  step, -step,  1.0f, 1.0f,
	 step,  step,  step,  1.0f, 0.0f,
	 step,  step,  step,  1.0f, 0.0f,
	-step,  step,  step,  0.0f, 0.0f,
	-step,  step, -step,  0.0f, 1.0f


};

class RenderClass
{

public:

	RenderClass()
	{
		
	}


	void init()
	{
		initRenderGrid();
		initContext();
		initShaders();
		initTextures();
		initMemory();
		glEnable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		ourShader.use();
		ourShader.setInt("shaderTexture", 0);
		glActiveTexture(GL_TEXTURE0);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMatrix("projection", projection);
	}

	glm::vec3 renderGrid[SIZEOFWORLD][SIZEOFWORLD][SIZEOFWORLD];

	float getCubeSize()
	{
		return step * 2;
	}

	Shader getShader()
	{
		return ourShader;
	}

	GLFWwindow* getWindow()
	{
		return window;
	}

	void deleteBuffers()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void processInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
		}
	}

	unsigned int getVAO()
	{
		return VAO;
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

private:

	

	Shader ourShader;

	GLFWwindow* window;

	float mixValue = 0.2f;

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	unsigned int VAO, VBO;
	unsigned int texture;


	void initRenderGrid()
	{
		float cubeSize = getCubeSize();

		for (int i = 0; i < SIZEOFWORLD; i++)
		{
			float offsetx = i * cubeSize;
			for (int j = 0; j < SIZEOFWORLD; j++)
			{
				float offsetj = j * cubeSize;
				for (int z = 0; z < SIZEOFWORLD; z++)
				{
					float offsetz = -z * cubeSize;
					renderGrid[i][j][z] = glm::vec3(offsetx, offsetj, offsetz);
				}

			}
		}
	}

	void initTextures()
	{
		glGenTextures(1, &texture);
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		
	}

	void initShaders()
	{
		ourShader = Shader("shadervs.txt", "shaderfs.txt");
	}

	void initMemory()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void initContext()
	{
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw window creation
		// --------------------
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;

		}
	}
};




