#include "grid.h"

// This function creates a new instance of the grid
Grid *createGrid(unsigned int width, unsigned int height)
{
	// limit the size of the grid to some arbitrary value
	width = width > g_MAX_WIDTH ? g_MAX_WIDTH : width;
	height = height > g_MAX_HEIGHT ? g_MAX_HEIGHT : height;

	// allocate memory for grid struct that holds the pointer to grid array
	Grid *newGrid = malloc(sizeof(Grid));
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
		newGrid->cells[i] = (Cell *)malloc(width * sizeof(Cell));
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

void freeGrid(Grid *grid)
{
	for (int i = 0; i < grid->height; i++)
	{
		free(grid->cells[i]);
	}

	free(grid->cells);
	free(grid);
}

// This function, given a grid pointer, will clear all state of the grid
bool clearGrid(Grid *grid)
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
bool flipGrid(Grid *grid)
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

// Sweep grid function takes in a coordinate and attempts to
// "sweep" surrounding tiles by making them visible if they're not a mine
bool sweepGrid(Grid *grid, unsigned int startX, unsigned int startY)
{
	// null and error checking
	if (!grid)
		return false;

	if (startX < 0 || startX >= grid->width)
		return false;

	if (startY < 0 || startY >= grid->height)
		return false;

	// Check the surroundings
	for (int dy = startY - 1; dy <= startY + 1; dy++)
	{
		for (int dx = startX - 1; dx <= startX + 1; dx++)
		{
			// Skip checking if these conditions are true
			if (dx < 0 || dx >= grid->width)
				continue;
			if (dy < 0 || dy >= grid->height)
				continue;
			if (dx == startX && dy == startY)
				continue;

			// Skip sweeping if current cell is already visible
			Cell *currentCell = &(grid->cells[dy][dx]);
			if (currentCell->state != cellState_Hidden)
				continue;

			if (currentCell->role == cellRole_Empty)
			{
				// show visible
				currentCell->state = cellState_Visible;

				// Auto reveal surroundings if cell is blank and has 0 mines surrounding it
				if (currentCell->value == 0)
				{
					sweepGrid(grid, dx, dy);
				}
			}
		}
	}

	return true;
}

// Generate random grid states
void generateRandomGrid(Grid *grid, int numMines, int x, int y)
{
	if (!grid)
		return;

	// place mines
	placeMines(grid, numMines, x, y);

	// generate numbers based on placed mines
	placeValues(grid);
}

// Places mines on the grid field, make sure that (x, y) must be empty
void placeMines(Grid *grid, int numMines, int x, int y)
{

	int placedCount = 0;
	while (placedCount < numMines)
	{
		int randomX = rand() % grid->width;
		int randomY = rand() % grid->height;

		// Check range to (x, y) and re-roll if too close
		if (abs(randomX - x) <= 1 || abs(randomY - y) <= 1)
		{
			continue;
		}

		// Else, place mine
		grid->cells[randomY][randomX].role = cellRole_Mine;
		placedCount++;
	}
}

// Suppose there are mines on the field, generate numbers based on surrounding mines
void placeValues(Grid *grid)
{
	for (int i = 0; i < grid->height; i++)
	{
		for (int j = 0; j < grid->width; j++)
		{
			Cell *cell = &(grid->cells[i][j]);
			if (cell->role != cellRole_Mine && cell->value == 0)
			{
				cell->value = countSurroundingMines(grid, j, i);
			}
		}
	}
}

// Returns the number of mines surrounding a particular coord
unsigned int countSurroundingMines(Grid *grid, int x, int y)
{
	unsigned int count = 0;
	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)
		{
			// Boundary checking
			if (i < 0 || j >= grid->width)
				continue;
			if (j < 0 || i >= grid->height)
				continue;

			// Check if it's a mine
			if (grid->cells[i][j].role == cellRole_Mine)
			{
				count++;
			}
		}
	}

	return count;
}

void displayTopLenged(int cells)
{
	// Leave 3 spaces for formatting
	//      XX-
	printf("   ");

	for (int i = 0; i < cells; i++)
	{
		if (i < 10)
		{
			printf("%2d  ", i);
		}
		else
		{
			printf("%3d ", i);
		}
	}

	printf("\n");
}

void displayTopTickedBorder(int cells)
{
	printf("  ");
	DRAW(BOXDRAW_TOP_LEFT);
	for (int i = 0; i < cells; i++)
	{
		DRAW(BOXDRAW_HORIZONTAL);
		DRAW(BOXDRAW_HORIZ_TOP);
		DRAW(BOXDRAW_HORIZONTAL);

		if (i != cells - 1)
			DRAW(BOXDRAW_HORIZ_BOT);
	}
	DRAW(BOXDRAW_TOP_RIGHT);
	printf("\n");
}

void displayGridRow(int cells)
{
	printf("  ");
	DRAW(BOXDRAW_VERT_RIGHT);

	for (int i = 0; i < cells; i++)
	{
		DRAW(BOXDRAW_HORIZONTAL);
		DRAW(BOXDRAW_HORIZONTAL);
		DRAW(BOXDRAW_HORIZONTAL);

		if (i != cells - 1)
			DRAW(BOXDRAW_CROSS);
	}

	DRAW(BOXDRAW_VERT_LEFT);

	printf("\n");
}

void displayBottomBorder(int cells)
{
	printf("  ");
	DRAW(BOXDRAW_BOT_LEFT);
	for (int i = 0; i < cells; i++)
	{
		DRAW(BOXDRAW_HORIZONTAL);
		DRAW(BOXDRAW_HORIZONTAL);
		DRAW(BOXDRAW_HORIZONTAL);

		if (i != cells - 1)
			DRAW(BOXDRAW_HORIZ_TOP);
	}
	DRAW(BOXDRAW_BOT_RIGHT);
	printf("\n");
}

void displayGrid(Grid *grid)
{
	if (!grid)
		return;

	const unsigned int width = grid->width;
	const unsigned int height = grid->height;

	// Display
	for (int i = 0; i < height; i++)
	{
		if (i == 0)
		{
			displayTopLenged(width);
			displayTopTickedBorder(width);
		}

		// For each row
		// Print left legend
		printf("%2d", i);
		DRAW(BOXDRAW_VERT_LEFT);

		// Left padding
		printf(" ");

		// Display each cell formatted
		for (int j = 0; j < width; j++)
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
					wprintf(L"%lc", displayMapping_mine);
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

			// Right border for each cell
			printf(" ");
			DRAW(BOXDRAW_VERTICAL);
			printf(" ");
		}

		// next line
		printf("\n");

		// separate each line with horizontal border
		if (i != height - 1)
			displayGridRow(width);
	}

	// finish and bottom border
	displayBottomBorder(width);
	printf("\n");
}