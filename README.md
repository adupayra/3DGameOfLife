# 3DGameOfLife (2 days of development in November 2020)
Basic game of life in 3D using openGL (with GLFW)

# Introduction

Personal project made to learn  C++ and discover graphics computing. It was made in a few days, longest was to learn openGL and basics of computer graphics.

The project is kind of minimal, it doesn't contain features and wasn't aimed to be perfect in term of speed or use of resources. 

Obvious improvements could be to make some thread computation for the rendering part as well as for the state updating part.
It could also be interesting to make more advanced post process effects.

This was a good project to put my hands on C++ as well as on the basics of computer graphics.

I might come back to it when I'll know more about thread management on the CPU side as well as on the GPU side (using CUDA for instance) and more about rendering.

The project files doesn't include glfw/glad/glm, one must download and configure them on its own to run the project.

Here is a screenshot of a state of the game after some generations :

![image](https://user-images.githubusercontent.com/55114282/102686286-d06cb200-41e6-11eb-8d57-3836d196f0b9.png)

Blue : Living cells
Green : About to live cells
Red : Dying cells
