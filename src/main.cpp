#include <math.h>
#include <ctime>
#include "mygl.h"
#include "shader.h"
#include "chapter3_cube.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main()
{
    SetGlobalResPath("E:/gitplace/LearnOpenGL/res/");
	GLFWwindow *window = GlfwInit();
    Chapter3Run(window);
	glfwTerminate(); 
	return 0;
}

