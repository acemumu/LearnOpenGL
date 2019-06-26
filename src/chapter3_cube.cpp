#include "chapter3_cube.h"
#include <ctime>
#include "texture.h"


void Chapter3CreateObject(GLuint *VAO, GLuint *VBO, GLuint *EBO)
{
	float z = 0.5f;
	float f = -0.5f;
    float r = 0.4f;
    float g = 0.0f;
    float b = 0.0f;
    float min_t = 0.0f, max_t = 1.0f;
	float verteices[] = {
        // 正面正方形4点
		z, z, z, r, g, b, max_t, max_t,
        z, f, z, r, g, b, max_t, min_t,
        f, f, z, r, g, b, min_t, min_t,
        f, z, z, r, g, b, min_t, max_t,

        // 上
        z, z, f, r, g, b, max_t, max_t,
        z, z, z, r, g, b, max_t, min_t,
        f, z, z, r, g, b,  min_t, min_t,
        f, z, f, r, g, b,  min_t, max_t,

      
        // 背面正方形4点
        z, z, f, r, g, b, max_t, max_t,
        f, z, f, r, g, b, max_t, min_t,
        f, f, f, r, g, b,  min_t, min_t,
        z, f, f, r, g, b,  min_t, max_t,
        // 下
        z, f, f, r, g, b, max_t, max_t,
        f, f, f, r, g, b, max_t, min_t,
        f, f, z, r, g, b,  min_t, min_t,
        z, f, z, r, g, b,  min_t, max_t,
       // 左
       f, z, z, r, g, b, max_t, max_t,
       f, f, z, r, g, b, max_t, min_t,
       f, f, f, r, g, b,  min_t, min_t,
       f, z, f, r, g, b,  min_t, max_t,
       // 右
       z, z, f, r, g, b, max_t, max_t,
       z, f, f, r, g, b, max_t, min_t,
       z, f, z, r, g, b,  min_t, min_t,
       z, z, z, r, g, b,  min_t, max_t,  
	};
    unsigned int index[36];
    unsigned int front[6] = {
        0, 1, 3, 1, 2, 3,
    };
    
    std::cout << std::endl;
    for (size_t i = 0, k=0; i < sizeof(index)/sizeof(unsigned int); i += 6, ++k)
    {
        for (size_t j = 0; j < 6; ++j) {
            index[i + j] = front[j] + 4 * k;
            std::cout << index[i + j] << " ";
        }
        std::cout << std::endl;
    }    

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verteices), verteices, GL_STATIC_DRAW);

    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
    
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);     
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 8 * sizeof(float),(void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

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
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(30.0f), *v_rotate);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
    projection = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH)/WIN_HEIGHT, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shader->ID, "model");
    int viewLoc = glGetUniformLocation(shader->ID, "view");
    int projLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    shader->SetFloat("mixPer", 0.3f);
    shader->SetInt("texture1", 0);
    shader->SetInt("texture2", 1);

    shader->Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void Chapter3Run(GLFWwindow * window)
{
    Shader shader("shaders/chp3.vs", "shaders/chp3.fs");
    GLuint VAO, VBO, EBO;
    Chapter3CreateObject(&VAO, &VBO, &EBO);

    int width, height;
    GLuint texture1 = CreateTexture("image/container.jpg", &width, &height, GL_RGB);
    GLuint texture2 = CreateTexture("image/awesomeface.png", &width, &height, GL_RGBA);

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

    clock_t last_tick_time = 0, cur_tick = 0;
    clock_t start_tick = clock();
    clock_t last_input_tick = 0;
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
            Chapter3Draw(&shader, VAO, EBO, texture1, texture2, rotate_vec_arr+i, pos_vec_arr+i);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}   