#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


class Shader
{
public:
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	void Use() const;
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;

	void SetFloat(const std::string &name, float value) const;
	void SetFloat(const std::string &name, float v1, float v2) const;
	void SetFloat(const std::string &name, float v1, float v2, float v3) const;
	void SetFloat(const std::string &name, float v1, float v2, float v3, float v4) const;

public:
	unsigned int ID;	
};


#endif