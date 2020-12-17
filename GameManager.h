#pragma once

#include "RenderClass.h"
#include "Grid.h"

#include <iostream>

class GameManager
{
public:

    RenderClass renderVar = RenderClass();
    Grid gridVar;

	GameManager()
	{
	}

	void init()
	{
        gridVar = Grid(32);
        
        
	}

	void gameLoop()
	{
        glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        glm::mat4 view = renderVar.view;
        glm::mat4 model = renderVar.model;
        glm::mat4 perspective = renderVar.perspective;
        perspective = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        while (!glfwWindowShouldClose(renderVar.getWindow()))
        {
            // input
            // -----
            renderVar.processInput();

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



            // render container
            renderVar.getShader().use();
            glBindVertexArray(renderVar.getVAO());


            view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
            view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));

            /*for (int i = 0; i < 10; i++)
            {
                

                model = glm::translate(model, cubePositions[i]);
                float angle = glm::radians(25.0f) * i;
                model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));

                renderVar.model = model;
                renderVar.view = view;
                renderVar.perspective = perspective;
                renderVar.updateShader();

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }*/
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(renderVar.getWindow());
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
	}

private:

	

	


};

