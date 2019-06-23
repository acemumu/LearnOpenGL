#include "chapter2_texture.h"
#include "texture.h"

#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int Chapter2_CreateVAO(GLuint *vao)
{	
	float max_coord = 0.5f;
	float min_coord = 0.4f;
	float max_size = 0.5f;
	float vertices[] = {
		// positions          // colors           // texture coords
		max_size,  max_size, 0.0f,   1.0f, 0.0f, 0.0f,   max_coord, max_coord,   // top right
		max_size, -max_size, 0.0f,   0.0f, 1.0f, 0.0f,   max_coord, min_coord,   // bottom right
		-max_size, -max_size, 0.0f,   0.0f, 0.0f, 1.0f,   min_coord, min_coord,   // bottom left
		-max_size,  max_size, 0.0f,   1.0f, 1.0f, 0.0f,   min_coord, max_coord    // top left 
	};
	unsigned int indices[] = {0, 1, 3, 1, 2, 3}; // …µ£¨”√¥Ì¿‡–Õ£ª
	std::cout << sizeof(vertices) / sizeof(float) << " " << sizeof(indices) / sizeof(unsigned int) << std::endl;
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
	for (int i = 0; i < 3; ++i)
		glEnableVertexAttribArray(i);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*vao = VAO;
	std::cout << *vao << " " << VBO << " " << EBO << std::endl;
	return EBO;
}
 

void Chapter2_Update(const Shader *shader, GLuint vao, unsigned int texture, GLuint ebo)
{
	glBindTexture(GL_TEXTURE_2D, texture);

	//glUseProgram(shader->ID);
	shader->Use();
	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Chapter2_Update2Texture(const Shader *shader, GLuint vao, GLuint ebo, GLuint texture1, GLuint texture2, float mixPer)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	shader->Use();
	//shader->SetFloat("mixPer", mixPer);
	shader->SetInt("texture1", 0);
	shader->SetInt("texture2", 1);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Chapter2_Test(GLFWwindow *window)
{

	Shader shader("shaders/texture.vs", "shaders/texture.fs");
	GLuint vao, ebo;
	ebo = Chapter2_CreateVAO(&vao);

	int width, height;
	GLuint texture1 = CreateTexture("image/container.jpg", &width, &height, GL_RGB);
	GLuint texture2 = CreateTexture("image/awesomeface.png", &width, &height, GL_RGBA);
	std::cout << "vao: " << vao << " ebo: " << ebo << " texture: " << texture1 << " " << texture2 << std::endl;

	shader.Use();
	//shader.SetInt("texture1", 0);  // only once
	//shader.SetInt("texture2", 1);
	float mixPer = 0.2f;
	shader.SetFloat("mixPer", mixPer);



	clock_t start_tick = 0, last_tick_time = 0, cur_tick;
	start_tick = clock();
	clock_t last_input_tick = 0;
	glm::mat4 trans;

	while (!glfwWindowShouldClose(window))
	{
		cur_tick = clock();

		if (cur_tick - last_tick_time < 30) {
			Sleep(3);
			continue;
		}
		last_tick_time = cur_tick;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			mixPer += 0.05f;
			std::cout << mixPer << std::endl;
			if (mixPer <= 1.0f)
				shader.SetFloat("mixPer", mixPer);
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			mixPer -= 0.05f;
			std::cout << mixPer << std::endl;
			if (mixPer >= 0.0f)
				shader.SetFloat("mixPer", mixPer);
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		trans = glm::rotate(trans, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

		unsigned int transformloc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformloc, 1, GL_FALSE, glm::value_ptr(trans));

		//Chapter2_Update(&shader, vao, texture2, ebo);
		Chapter2_Update2Texture(&shader, vao, ebo, texture1, texture2, mixPer);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ebo);
}