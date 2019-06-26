
#include "shader.h"
#include "mygl.h"

//extern std::string g_res_path;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::cout << "INFO: start compile shader :\n\t'" << vertexPath << "', \n\t'" << fragmentPath << "'" << std::endl;
    //std::cout << g_res_path << std::endl;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

    std::string str_vpath = GetGlobalResPath() + std::string(vertexPath);
    std::string str_fpath = GetGlobalResPath() + std::string(fragmentPath);

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(str_vpath);
		fShaderFile.open(str_fpath);

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
		std::cout << "ERROR: read shader file failed!" << std::endl;
	}

	const char * vShaderSource = vertexCode.c_str();
	const char * fShaderSource = fragmentCode.c_str();
	int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glCompileShader(vShader);

	int succ;
	char info[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &succ);
	if (!succ) {
		glGetProgramInfoLog(ID, sizeof(info), NULL, info);
		std::cout << "ERROR: vertex shader compile failed, path: " << str_vpath << std::endl;
		std::cout << "\t\t" << info << std::endl;
	}

	int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderSource, NULL);
	glCompileShader(fShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &succ);
	if (!succ) {
		glGetProgramInfoLog(ID, sizeof(info), NULL, info);
		std::cout << "ERROR: vertex shader compile failed, path: " << str_fpath << std::endl;
		std::cout << "\t\t" << info << std::endl;
	}

	this->ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);
	// check for link error
	glGetProgramiv(ID, GL_LINK_STATUS, &succ);
	if (!succ) {
		glGetProgramInfoLog(ID, sizeof(info), NULL, info);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << info << std::endl;
	}
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	std::cout << "INFO:[SUCC] end compile shader :\n\t'" << str_vpath << "', \n\t'" << str_fpath << "'" << std::endl;
}


void Shader::Use() const
{
	glUseProgram(this->ID);
}

void Shader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float v1, float v2) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform2f(loc, v1, v2);
}

void Shader::SetFloat(const std::string &name, float v1, float v2, float v3) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform3f(loc, v1, v2, v3);
}

void Shader::SetFloat(const std::string &name, float v1, float v2, float v3, float v4) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform4f(loc, v1, v2, v3, v4);
}