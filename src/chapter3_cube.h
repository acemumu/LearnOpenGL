#pragma once
#include "mygl.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Chapter3CreateObject(GLuint *VAO, GLuint *VBO, GLuint *EBO);
void Chapter3Draw(const Shader * shader, GLuint VAO, GLuint EBO, GLuint texture1, GLuint texture2,
    glm::vec3* v_rotate, glm::vec3* v_pos);
void Chapter3Run(GLFWwindow *window);