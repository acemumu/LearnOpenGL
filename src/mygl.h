#pragma once

#ifndef __MYGL__
#define __MYGL__

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

// ´°¿Ú²ÎÊý
#define WIN_WIDTH		800
#define WIN_HEIGHT		600
#define WINDOW_NAME		"LearnOpenGL"



void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int w, int h);
GLFWwindow* GlfwInit();

std::string GetGlobalResPath();
void SetGlobalResPath(std::string path);

#endif // !__MYGL__

