#pragma once


#include "RenderClass.h"
#include "Grid.h"
#include <iostream>
#include <thread>
#include <chrono>


class GameManager
{
public:

    RenderClass renderVar;
    Grid gridVar;

	GameManager()
	{
	}

	void init()
	{
        renderVar.init();
        
        
	}

	void gameLoop()
	{
        float cubeSize = renderVar.getCubeSize();

        float offsetxy = ((float)SIZEOFWORLD * cubeSize)/2 - cubeSize / 2;
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::vec3 gonnaLiveColor = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 gonnaDieColor = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 aliveColor = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 colors[] = { aliveColor, gonnaLiveColor, gonnaDieColor };
        //renderVar.getShader().setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        while (!glfwWindowShouldClose(renderVar.getWindow()))
        {
            // input
            // -----
            renderVar.processInput();

            std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
            
            


            // render
            // ------
            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            
            //View adjustement
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(-offsetxy, -offsetxy, -5.0f));
            view = glm::rotate(view, glm::radians(45.0f), glm::vec3(1.0f, 1.0, 0));
            renderVar.getShader().setMatrix("view", view);
            
            //Render the cells
            glm::mat4 model = glm::mat4(1.0f);
            for (int i = 0; i < SIZEOFWORLD; i++)
            {
                for (int j = 0; j < SIZEOFWORLD; j++)
                {
                    
                    for (int z = 0; z < SIZEOFWORLD; z++)
                    {
                        unsigned int cache = gridVar.grid[i][j][z];
                        if (cache != (unsigned int)State::Dead)
                        {
                            model = glm::mat4(1.0f);
                            model = glm::translate(model, renderVar.renderGrid[i][j][z]);
                            renderVar.getShader().setMatrix("model", model);
                            renderVar.getShader().setVec3("color", colors[cache - 1]);
                            glDrawArrays(GL_TRIANGLES, 0, 36);
                        }


                        
                    }
                }
            }

            //Update the grid
            gridVar.processGrid();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(renderVar.getWindow());
            glfwPollEvents();
            
        }
        
        // Deletion of the gl variables
        renderVar.deleteBuffers();
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
	}

private:

    const int timeStep = 500;

	


};

