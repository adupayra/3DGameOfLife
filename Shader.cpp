#include "Shader.h"


Shader::Shader (const char* pathToVertex, const char* pathToFragment)
{

	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(pathToVertex);
		fShaderFile.open(pathToFragment);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		
		
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR READING FILES" << std::endl;
	}

	int succes;
	char log[512];

	int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	
	glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);
	glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);

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

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

