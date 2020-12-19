#pragma once
#include "CubeClass.h"
#include <vector>
#include <cstdlib>

const int SIZEOFWORLD = 30;

enum class State {Alive = 1, Dead = 0, GonnaLive = 2, GonnaDie = 3};


class Grid
{
public:
	
	Grid()
	{
		for (int i = 0; i < SIZEOFWORLD; i++)
		{
			for (int j = 0; j < SIZEOFWORLD; j++)
			{
				for (int z = 0; z < SIZEOFWORLD; z++)
				{
					float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					
					grid[i][j][z] = r < 0.01f ? 1 : 0;
					
				}
			}
		}
	}


	

	void processGrid()
	{
		for (int i = 0; i < SIZEOFWORLD; i++)
		{
			int i0 = (i - 1 + SIZEOFWORLD) % SIZEOFWORLD;
			int i2 = (i + 1 + SIZEOFWORLD) % SIZEOFWORLD;
			
			for (int j = 0; j < SIZEOFWORLD; j++)
			{
				int j0 = (j - 1 + SIZEOFWORLD) % SIZEOFWORLD;
				int j2 = (j + 1 + SIZEOFWORLD) % SIZEOFWORLD;
				for (int z = 0; z < SIZEOFWORLD; z++)
				{
					if (grid[i][j][z] == (unsigned int)State::GonnaLive)
					{
						
						tempGrid[i][j][z] = (unsigned int)State::Alive;
					}
					else if (grid[i][j][z] == (unsigned int)State::GonnaDie)
					{
						
						tempGrid[i][j][z] = (unsigned int)State::Dead;
					}
					else
					{
						int z0 = (z - 1 + SIZEOFWORLD) % SIZEOFWORLD;
						int z2 = (z + 1 + SIZEOFWORLD) % SIZEOFWORLD;
						process(i0, i, i2, j0, j, j2, z0, z, z2);
					}

				
				}

			}
		}
		std::swap(grid, tempGrid);
	}

	void process(int i0, int i, int i2, int j0, int j,  int j2, int z0, int z,  int z2)
	{
		unsigned int temp[] = { grid[i0][j0][z0], grid[i][j0][z0], grid[i2][j0][z0], grid[i0][j][z0],  grid[i][j][z0] , grid[i2][j][z0] ,
			grid[i0][j2][z0] , grid[i][j2][z0] , grid[i2][j2][z0] ,
			grid[i0][j0][z] , grid[i][j0][z] , grid[i2][j0][z] , grid[i0][j][z] , grid[i2][j][z] ,
			grid[i0][j2][z] , grid[i][j2][z] , grid[i2][j2][z] ,
			grid[i0][j0][z2] , grid[i][j0][z2] , grid[i2][j0][z2] , grid[i0][j][z2] , grid[i][j][z2] , grid[i2][j][z2] ,
			grid[i0][j2][z2] , grid[i][j2][z2] , grid[i2][j2][z2] };
		int countCells = 0;

		for (int i = 0; i < 26; i++)
		{
			if (temp[i] == (unsigned int)State::Alive)
				countCells++;
		}


		unsigned int cache = grid[i][j][z];
		
		if (countCells == 3 && cache == (unsigned int)State::Dead)
			tempGrid[i][j][z] = (unsigned int)State::GonnaLive;
		else if (countCells == 3 || countCells == 2 && cache == (unsigned int)State::Alive)
			tempGrid[i][j][z] = (unsigned int)State::Alive;
		else if (cache == (unsigned int)State::Alive)
			tempGrid[i][j][z] = (unsigned int)State::GonnaDie;
		else
			tempGrid[i][j][z] = (unsigned int)State::Dead;

		
	}

	bool isCyclic()
	{

	}

	unsigned int grid[SIZEOFWORLD][SIZEOFWORLD][SIZEOFWORLD] = { 0 };
	unsigned int tempGrid[SIZEOFWORLD][SIZEOFWORLD][SIZEOFWORLD] = { 0 };
private:


};

