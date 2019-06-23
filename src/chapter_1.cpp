
#include "chapter_1.h"
#include "shader.h"


char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aCol;\n"
"out vec3 vcolor;\n"
"void main(){ \n"
"gl_Position = vec4(aPos, 1.0);\n"
"vcolor = aCol;\n"
" }";

char* fragmentShaderSource = "#version 330 core\n"
"in vec3 vcolor;\n"
"out vec4 fragColor; \n"
"void main() { fragColor = vec4(vcolor, 1.0f); }";

char* framgementShaderSource2 ="#version 330 core\n"
"in vec3 vcolor;\n"
"out vec4 fragColor; \n"
"void main() { fragColor = vec4(vcolor, 1.0f); }";


int Chapter1_Shader1()
{
	return _Chapter1_ShaderProgram(fragmentShaderSource);
}

int Chapter1_Shader2()
{
	return _Chapter1_ShaderProgram(framgementShaderSource2);
}


int _Chapter1_ShaderProgram(char * fragmentShaderSource)
{
	// 创建顶点shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int succ;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succ);
	if (!succ)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infolog), NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILETION_FAILED\n" << infolog << std::endl;
	}
	else
	{
		std::cout << "INFO::SHADER::VERTEX::SUCC" << std::endl;
	}

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succ);
	if (!succ)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infolog), NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILETION_FAILED\n" << infolog << std::endl;
	}
	else
	{
		std::cout << "INFO::SHADER::FRAGMENT::SUCC" << std::endl;
	}

	//link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for link error
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succ);
	if (!succ)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infolog), NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
	}
	else
	{
		std::cout << "INFO::SHADER::PROGRAM::LINK_SUCC" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}


int Chapter1_CreateVAOVBO(unsigned int *vao, unsigned int *vbo, unsigned count)
{
	// 顶点元
	float verteices[] = {
		//-0.5f, -0.5f, 0.0f,
		//0.5f, -0.5f, 0.0f,
		//0.0f,  0.5f, 0.0f,   
		// pos				// color			
		1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,	
		0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-.5f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		.5f, -.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};


	glGenVertexArrays(count, vao);
	glGenBuffers(count, vbo);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*18, verteices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*18, verteices+18, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(0);

	// clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//*vao = VAO;
	//*vbo = VBO;
	return 0;
}


int Chapter1_CreateEBO(unsigned int *vao, unsigned int *vbo)
{
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	unsigned int VBO, VAO;
	unsigned int EBO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	*vao = VAO;
	*vbo = VBO;
	return EBO;
}


void Chapter1_Test(GLFWwindow * window)
{
	unsigned int VBO[2], VAO[2], EBO;
	EBO = Chapter1_CreateVAOVBO(VAO, VBO, 2);
	//EBO = Chapter1_CreateEBO(&VAO, &VBO);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Shader shader = Shader("shaders/chapter1.vs", "shaders/chapter1.fs");

	while (!glfwWindowShouldClose(window))
	{
		//processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (0 == EBO)
		{
			//float timeValue = glfwGetTime();
			//float green = sin(timeValue) / 2 + 0.5f;
			//float red = cos(timeValue) / 2 + 0.5f;
			//float blue = (green + red) / 2;
			//int vcolorLoc = glGetUniformLocation(shaderProgram1, "vcolor");
			glUseProgram(shader.ID);
			//glUniform4f(vcolorLoc, red, green, blue, 1.0f);

			glBindVertexArray(VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//vcolorLoc = glGetUniformLocation(shaderProgram2, "vcolor");
			//glUseProgram(shaderProgram2);
			//glUniform4f(vcolorLoc, green, blue, red, 1.0f);

			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		//glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	if (EBO) {
		glDeleteBuffers(1, &EBO);
	}
}