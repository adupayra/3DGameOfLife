#pragma once

#ifndef DEF_SHADER
#define DEF_SHADER

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <direct.h> 

class Shader
{
public:

	unsigned int ID;

	Shader(const char* , const char* );

	void use() const;

	void setBool(const std::string& , bool )const;

	void setInt(const std::string& , int ) const;

	void setFloat(const std::string& , float ) const;
};

#endif

