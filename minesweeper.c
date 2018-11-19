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
	Grid* grid = createGrid(80, 30); // get instance of the grid
	clearGrid(grid);
	generateRandomGrid(grid, 20, 2, 2);


	flipGrid(grid);
	displayGrid(grid);

	// FIXME: temp
	freeGrid(grid);
	return false;
}