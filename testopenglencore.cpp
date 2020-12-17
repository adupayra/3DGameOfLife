#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float mixValue = 0.2f;

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shadervs.txt", "shaderfs.txt");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    -0.3f, -0.3f, -0.3f,  0.0f, 0.0f,
     0.3f, -0.3f, -0.3f,  1.0f, 0.0f,
     0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
     0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
    -0.3f,  0.3f, -0.3f,  0.0f, 1.0f,
    -0.3f, -0.3f, -0.3f,  0.0f, 0.0f,

    -0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
     0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
     0.3f,  0.3f,  0.3f,  1.0f, 1.0f,
     0.3f,  0.3f,  0.3f,  1.0f, 1.0f,
    -0.3f,  0.3f,  0.3f,  0.0f, 1.0f,
    -0.3f, -0.3f,  0.3f,  0.0f, 0.0f,

    -0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
    -0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
    -0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
    -0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
    -0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
    -0.3f,  0.3f,  0.3f,  1.0f, 0.0f,

     0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
     0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
     0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
     0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
     0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
     0.3f,  0.3f,  0.3f,  1.0f, 0.0f,

    -0.3f, -0.3f, -0.3f,  0.0f, 1.0f,
     0.3f, -0.3f, -0.3f,  1.0f, 1.0f,
     0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
     0.3f, -0.3f,  0.3f,  1.0f, 0.0f,
    -0.3f, -0.3f,  0.3f,  0.0f, 0.0f,
    -0.3f, -0.3f, -0.3f,  0.0f, 1.0f,

    -0.3f,  0.3f, -0.3f,  0.0f, 1.0f,
     0.3f,  0.3f, -0.3f,  1.0f, 1.0f,
     0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
     0.3f,  0.3f,  0.3f,  1.0f, 0.0f,
    -0.3f,  0.3f,  0.3f,  0.0f, 0.0f,
    -0.3f,  0.3f, -0.3f,  0.0f, 1.0f


    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(-0.6f,  0.0f, 0.0f),
    glm::vec3(0.6f, -0.0f, -0.0f),
    glm::vec3(0.0f, 0.6f, -0.0f),
    glm::vec3(0.0f, -0.6f, -0.0f),
    glm::vec3(-0.6f,  0.6f, 0.0f),
    glm::vec3(-0.6f, -0.6f, 0.0f),
    glm::vec3(0.6f,  -0.6f, -0.0f),
    glm::vec3(0.6f,  0.6f, -0.0f),

    glm::vec3(0.0f,  0.0f,  -0.6f),
    glm::vec3(-0.6f,  0.0f, -0.6f),
    glm::vec3(0.6f, -0.0f, -0.6f),
    glm::vec3(0.0f, 0.6f, -0.6f),
    glm::vec3(0.0f, -0.6f, -0.6f),
    glm::vec3(-0.6f,  0.6f, -0.6f),
    glm::vec3(-0.6f, -0.6f, -0.6f),
    glm::vec3(0.6f,  -0.6f, -0.6f),
    glm::vec3(0.6f,  0.6f, -0.6f),

    glm::vec3(0.0f,  0.0f,  0.6f),
    glm::vec3(-0.6f,  0.0f, 0.6f),
    glm::vec3(0.6f, -0.0f, 0.6f),
    glm::vec3(0.0f, 0.6f, 0.6f),
    glm::vec3(0.0f, -0.6f, 0.6f),
    glm::vec3(-0.6f,  0.6f, 0.6f),
    glm::vec3(-0.6f, -0.6f, 0.6f),
    glm::vec3(0.6f,  -0.6f, 0.6f),
    glm::vec3(0.6f,  0.6f, 0.6f),

    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture, texture2;
    glGenTextures(1, &texture);
    
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    //glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed loading texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();

    ourShader.setInt("shaderTexture", 0);
    ourShader.setInt("shaderTexture2", 1);
    
    unsigned int model = glGetUniformLocation(ourShader.ID, "model");
    unsigned int view = glGetUniformLocation(ourShader.ID, "view");
    unsigned int perspective = glGetUniformLocation(ourShader.ID, "perspective");

    
    glm::mat4 persp = glm::mat4(1.0f);

    persp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(perspective, 1, GL_FALSE, glm::value_ptr(persp));
    
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        ourShader.setFloat("step", mixValue);


        // render container
        ourShader.use();
        

        
        glm::mat4 vi = glm::mat4(1.0f);
        vi = glm::translate(vi, glm::vec3(0.0f, 0.0f, -5.0f));
        vi = glm::rotate(vi, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(vi));

        glBindVertexArray(VAO);
        for (int i = 0; i < 27; i++)
        {
            glm::mat4 mod = glm::mat4(1.0f);

            mod = glm::translate(mod, cubePositions[i]);
            float angle = glm::radians(25.0f) * i;
            mod = glm::rotate(mod, 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(mod));

            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        

       


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.001f;
        if (mixValue > 1.0f)
            mixValue = 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.001f;
        if (mixValue < 0.0f)
            mixValue = 0.0f;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}