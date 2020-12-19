#pragma once


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <direct.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

	Shader()
	{

	}

	//Constructor which will create a program by creating and linking a vertex and a fragment shader (by using the files indicated as parameters to compile each shader)
	Shader(const char* pathToVertex, const char* pathToFragment)
	{

		/*-------------------------------------------*/

		//File opening and reading stuff

		/*--------------------------------------------*/
		std::string vertexCode;
		std::string fragmentCode;

		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			//Open files
			vShaderFile.open(pathToVertex);
			fShaderFile.open(pathToFragment);

			std::stringstream vShaderStream, fShaderStream;

			//Read the files
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			//Convert files streams into usable type
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR READING FILES" << std::endl;
		}


		/*----------------------------------------------------*/
		
		//Creation compilation, and error checking of the two shaders

		/*----------------------------------------------------*/
		int succes;
		char log[512];

		//Creation of the specific shaders
		int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		//Convert the strings into C string
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//Binding of the shader object with the compile string
		glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);
		glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);
		//Compile the shader and check for error
		glCompileShader(vertexShaderID);
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &succes);

		if (!succes)
		{
			glGetShaderInfoLog(vertexShaderID, 512, NULL, log);
			std::cout << "ERROR COMPILING VERTEX " << log << std::endl;
		}

		glCompileShader(fragmentShaderID);

		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &succes);

		if (!succes)
		{
			glGetShaderInfoLog(fragmentShaderID, 512, NULL, log);
			std::cout << "ERROR COMPILING FRAGMENT " << log << std::endl;
		}


		/*-----------------------------------*/

		//Creation of the associated program and linking of the shaders

		/*-----------------------------------*/
		ID = glCreateProgram();

		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &succes);

		if (!succes)
		{
			glGetProgramInfoLog(ID, 512, NULL, log);
			std::cout << "ERROR LINKING SHADERS" << std::endl;
		}

		//We can delete the shaders when the program is craeted and the links are made
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void use() const
	{
		glUseProgram(ID);
	}

	unsigned int getID()
	{
		return ID;
	}

	
	//Shaders' uniform values setters
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setMatrix(const std::string& name, const glm::mat4 matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1, GL_FALSE, &matrix[0][0]);
	}

	void setVec3(const std::string& name, const glm::vec3 vec) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
	}
private:

	unsigned int ID;

};

