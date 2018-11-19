#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <stdio.h>
#include "cell.h"
#include "useful.h"
#include "drawing.h"

#define g_MAX_WIDTH 80
#define g_MAX_HEIGHT 60

// Grid - that holds the cells
typedef struct
{
	Cell **cells;

	unsigned int width;
	unsigned int height;
} Grid;

// Grid display mapping
// Display mappings
enum displayMapping
{
	displayMapping_blank = ' ',
	displayMapping_mine = 0x2738,
	displayMapping_flag = 'F',
	displayMapping_hidden = '-'
};

// Grid lifetime managerment functions
Grid *createGrid(unsigned int width, unsigned int height);
void freeGrid(Grid *grid);

// Grid state manipulation functions
bool clearGrid(Grid *grid);
bool flipGrid(Grid *grid);
bool sweepGrid(Grid *grid, unsigned int startX, unsigned int startY);

// Grid generation
void generateRandomGrid(Grid *grid, int numMines, int x, int y);
void placeMines(Grid *grid, int numMines, int x, int y);
void placeValues(Grid *grid);

// Grid helpers
unsigned int countSurroundingMines(Grid *grid, int x, int y);

// Grid display functions
void displayTopLegend(int cells);
void displayTopTickedBorder(int cells);
void displayGridRow(int cells);
void displayBottomBorder(int cells);
void displayGrid(Grid *grid);

#endif