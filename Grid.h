#pragma once
#include "CubeClass.h"
#include <vector>

const int SIZEOFWORLD = 9;



class Grid
{
public:
	
	Grid()
	{
		grid[0][0][0] = 1;
		grid[0][1][0] = 1;
		grid[0][2][0] = 1;
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
					int z0 = (z - 1 + SIZEOFWORLD) % SIZEOFWORLD;
					int z2 = (z + 1 + SIZEOFWORLD) % SIZEOFWORLD;
					process(i0,  i, i2, j0, j, j2, z0,z, z2);
				}

			}
		}
		std::swap(grid, tempGrid);
	}

	void process(int i0, int i, int i2, int j0, int j,  int j2, int z0, int z,  int z2)
	{
		int countCells = grid[i0][j0][z0] + grid[i][j0][z0] + grid[i2][j0][z0] + grid[i0][j][z0] + grid[i][j][z0] + grid[i2][j][z0] +
			grid[i0][j2][z0] + grid[i][j2][z0] + grid[i2][j2][z0] +
			grid[i0][j0][z] + grid[i][j0][z] + grid[i2][j0][z] + grid[i0][j][z] + grid[i2][j][z] +
			grid[i0][j2][z] + grid[i][j2][z] + grid[i2][j2][z] +
			grid[i0][j0][z2] + grid[i][j0][z2] + grid[i2][j0][z2] + grid[i0][j][z2] + grid[i][j][z2] + grid[i2][j][z2] +
			grid[i0][j2][z2] + grid[i][j2][z2] + grid[i2][j2][z2];

		
		tempGrid[i][j][z] = countCells == 3 || (countCells == 2 && grid[i][j][z] == 1) ? 1 : 0;
	}

	bool isCyclic()
	{

	}

	unsigned int grid[SIZEOFWORLD][SIZEOFWORLD][SIZEOFWORLD] = { 0 };
	unsigned int tempGrid[SIZEOFWORLD][SIZEOFWORLD][SIZEOFWORLD] = { 0 };
private:


};

