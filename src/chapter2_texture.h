#pragma once

#include "mygl.h"
#include "shader.h"

unsigned int Chapter2_CreateVAO(GLuint *vao);
void Chapter2_Update2Texture(const Shader *shader, GLuint vao, GLuint ebo, GLuint texture1, GLuint texture2, float mixPer);
void Chapter2_Update(const Shader *shader, GLuint vao, unsigned int texture, GLuint ebo);
void Chapter2_Test(GLFWwindow *window);