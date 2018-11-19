#include "minesweeper.h"


// Main function (entry point)
int main(void)
{

	bool keepPlaying = false;
	do
	{
		keepPlaying = playMinesweeper();
	} while (keepPlaying);

	return 0;
}

bool playMinesweeper()
{
	// Create a grid of cells
	Grid* grid = createGrid(10, 10);
	clearGrid(grid);
	displayGrid(grid);

	// FIXME: temp
	return false;
}

// This function creates a new instance of the grid
Grid* createGrid(unsigned int width, unsigned int height)
{
	// limit the size of the grid to some arbitrary value
	width = width > 80 ? 80 : width;
	height = height > 60 ? 60 : height;

	// allocate memory for grid struct that holds the pointer to grid array
	Grid* newGrid = malloc(sizeof(Grid));
	if (!newGrid)
		return NULL;

	// allocate memory for rows of cells
	newGrid->cells = (Cell **)malloc(height * sizeof(Cell *));
	if (!newGrid->cells)
	{
		free(newGrid);
		return NULL;
	}

	// Allocate memory for each cell in each row
	for (int i = 0; i < height; i++)
	{
		newGrid->cells[i] = (Cell *) malloc(width * sizeof(Cell));
	}
	if (!newGrid->cells[0])
	{
		free(newGrid->cells);
		free(newGrid);
		return NULL;
	}

	// If all allocation is valid, proceed to assign size to grid struct
	newGrid->width = width;
	newGrid->height = height;

	return newGrid;
}

// This function, given a grid pointer, will clear all state of the grid
bool clearGrid(Grid* grid)
{
	// Check nullptr
	if (!grid)
		return false;

	for (unsigned int i = 0; i < grid->width; i++)
	{
		for (unsigned int j = 0; j < grid->height; j++)
		{
			grid->cells[j][i].role = cellRole_Empty;
			grid->cells[j][i].state = cellState_Hidden;
		}
	}
	
	return true;
}

// Flip grid will change all cell states to being shown
bool flipGrid(Grid* grid)
{
	// check null
	if (!grid)
		return false;

	for (unsigned int i = 0; i < grid->width; i++)
	{
		for (unsigned int j = 0; j < grid->height; j++)
		{
			grid->cells[j][i].state = cellState_Visible;
		}
	}

	return true;
}

// bool sweepGrid(Grid* grid, unsigned int startX, unsigned int startY)
// {
// 	// null and error checking
// 	if (!grid)
// 		return false;

// 	if (startX < 0 || startX >= grid->width)
// 		return false;

// 	if (startY < 0 || startY >= grid->height)
// 		return false;

// 	// Recursively check grid
// 	// check x, y-1
// 	if (startY - 1 > 0)
// 		sweepGrid(grid, startX, startY - 1);

// 	// check x-1, y
// 	// check x+1, y
// 	// check x, y+1
// }

void displayGrid(Grid* grid)
{
	if (!grid)
		return;

	// Display
	for (int i = 0; i < grid->height; i++)
	{
		if (i == 0)
		{
			printf("====\n");
		}
		// else
		// {
		// 	printf("----");
		// }

		for (int j = 0; j < grid->width; j++)
		{
			enum cellRole role = grid->cells[i][j].role;
			enum cellState state = grid->cells[i][j].state;
			unsigned int value = grid->cells[i][j].value;

			switch (state)
			{
				case cellState_Visible:
				{
					// Safe fields
					if (role == cellRole_Empty)
					{
						if (value == 0)
						{
							printf("%c", displayMapping_blank);
						}
						else
						{
							printf("%d", value);
						}
					}
					else if (role == cellRole_Mine)
					{
						printf("%c", displayMapping_mine);
					}
				}
				break;

				case cellState_Flagged:
				{
					printf("%c", displayMapping_flag);
				}
				break;

				case cellState_Hidden:
				{
					printf("%c", displayMapping_hidden);
				}
				break;
			}
		}

		// next line
		printf("\n");
	}

	// finish
	printf("======");
}