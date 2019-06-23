#include "chapter3_cube.h"
#include <ctime>



void Chapter3CreateObject(GLuint *VAO, GLuint *VBO, GLuint *EBO)
{
	float z = 0.5f;
	float f = -0.5f;
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
	float verteices[] = {
        // 正面正方形4点
		z, z, z, r, g, b, 
        z, f, z, r + 0.2f, g + 0.2f, b + 0.2f,
        f, f, z, r + 0.4f, g + 0.4f, b + 0.4f,
        f, z, z, r + 0.6f, g + 0.6f, b + 0.6f,
        // 背面正方形4点
        z, z, f, r, 1.0f, b+0.3f,
        z, f, f, r+0.8f, 1.0f, b,
        f, f, f, r, .5f, b+0.2f,
        f, z, f, r+0.2f, 1.0f, b+0.5f,
	};
    unsigned int index[] = {
        // 正
        0, 1, 3, 
        1, 2, 3,   
        // 上
        4, 0, 7,
        0, 3, 7,   
        // 背
        7, 6, 4, 
        6, 5, 4,
        // 底
        2, 1, 5, 
        6, 2, 5,
        // 右
        1, 0, 4, 
        5, 1, 4,
        // 左
        3, 2, 7,
        2, 6, 7,
    };

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verteices), verteices, GL_STATIC_DRAW);

    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
    
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);     
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 6 * sizeof(float),(void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Chapter3Draw(const Shader * shader, GLuint VAO, GLuint EBO, GLuint texture1, GLuint texture2, 
    glm::vec3* v_rotate, glm::vec3* v_pos)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat2(1.0f);
    model = glm::translate(model, *v_pos);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(texture1 * 18.0f), *v_rotate);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
    projection = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH)/WIN_HEIGHT, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shader->ID, "model");
    int viewLoc = glGetUniformLocation(shader->ID, "view");
    int projLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    shader->Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void Chapter3Run(GLFWwindow * window)
{
    Shader shader("shaders/chp3.vs", "shaders/chp3.fs");
    GLuint VAO, VBO, EBO;
    Chapter3CreateObject(&VAO, &VBO, &EBO);

    clock_t last_tick_time = 0, cur_tick = 0;
    clock_t start_tick = clock();
    clock_t last_input_tick = 0;

    glm::vec3 rotate_vec_arr[] = {
        glm::vec3(1.0f, 0, 0),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.3333f, 0.3333f, 0.3333f),
        glm::vec3(-0.3333f, 0.3333f, 0.3333f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };

    glm::vec3 pos_vec_arr[] = {
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(2.0f, 1.0f, 2.0f),
        glm::vec3(-2.0f, 0.0f, 2.0f),
        glm::vec3(0.0f, -1.0f, 3.0f),
        glm::vec3(-2.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
    };

    int count = sizeof(pos_vec_arr) / sizeof(pos_vec_arr[0]);
    std::cout << "count=" << count << std::endl;
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
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < count; ++i) {
            Chapter3Draw(&shader, VAO, EBO, i+1, i, rotate_vec_arr+i, pos_vec_arr+i);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}   