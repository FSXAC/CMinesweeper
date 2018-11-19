#include "minesweeper.h"

// Main function (entry point)
int main(void)
{
	// Set locale for drawing
	setlocale(LC_CTYPE, "");

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
	Grid* grid = createGrid(20, 20); // get instance of the grid
	clearGrid(grid);
	generateRandomGrid(grid, 20, 0, 0);

	flipGrid(grid);
	displayGrid(grid);

	freeGrid(grid);
	return false;
}