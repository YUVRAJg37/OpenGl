#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <../imageLoader/stb_image/stb_image.h>

#include <../Shader/shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tinkering", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("shader.vert", "shader.frag");

    unsigned int verticesCount = 36;
    float xRot = 0.0f;

    float vertices[] = {
    	-1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,       0.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f, 1.0f,       1.0f, 1.0f, 
		 1.0f, -1.0f, 1.0f,     0.0f, 1.0f, 0.0f, 1.0f,       1.0f, 0.0f,
		 1.0f, -1.0f, 1.0f,     0.0f, 1.0f, 0.0f, 1.0f,       1.0f, 0.0f,
		-1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,       0.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f,       0.0f, 0.0f,

        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,       0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,       1.0f, 0.0f,

        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 0.0f,       0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 0.0f,       0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 0.0f,       0.0f, 0.0f,

         1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 0.0f,       0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 0.0f,       0.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 0.0f,       1.0f, 0.0f,

        -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 0.0f,       0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 0.0f,       1.0f, 1.0f,

        -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 0.0f,       1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 0.0f,       0.0f, 1.0f,
    };

    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    int height, width, nrChannels;
    unsigned char* data = stbi_load("textures/image.jpeg", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    if(!data)
    {
        std::cout << "Image Load Failed" << std::endl;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(55.0f), (float)WIDTH / HEIGHT, 0.01f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
    unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        model = glm::rotate(model, glm::radians(0.01f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(0.02f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(0.03f), glm::vec3(0.0f, 0.0f, 1.0f));
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);


        ImGui::Begin("Window");
        ImGui::SliderFloat("Rot", &xRot, 0.0f, 360.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}