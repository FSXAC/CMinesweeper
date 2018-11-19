#ifndef MINESWEEPER_H
#define MINESWEEPER_H

/* Minesweeper game */

// Includes
#include <stdio.h>
#include <stdlib.h>

// Useful stuff
typedef char bool;
#define false 0
#define true 1

////// GRID STUFF

// Cell states
enum cellState
{
	cellState_Hidden,
	cellState_Visible,
	cellState_Flagged
};

// Cell role
enum cellRole
{
	cellRole_Empty,
	cellRole_Mine
};

// Cell
typedef struct
{
	enum cellState state;
	enum cellRole role;
	unsigned int value;
} Cell;

// Grid - that holds the cells
typedef struct
{
	Cell **cells;

	unsigned int width;
	unsigned int height;
} Grid;

// Display mappings
enum displayMapping
{
	displayMapping_blank = ' ',
	displayMapping_mine = 'X',
	displayMapping_flag = 'F',
	displayMapping_hidden = '-'
};

// Functions
bool playMinesweeper();
void freeGrid(Grid *grid);
Grid *createGrid(unsigned int width, unsigned int height);
bool clearGrid(Grid *grid);

void freeGrid(Grid *grid);
void generateRandomGrid(Grid* grid, int numMines, int x, int y);
void placeMines(Grid *grid, int numMines, int x, int y);
void placeValues(Grid *grid);
unsigned int countSurroundingMines(Grid *grid, int x, int y);
bool flipGrid(Grid* grid);
bool sweepGrid(Grid* grid, unsigned int startX, unsigned int startY);

void displayGrid(Grid *grid);

#endif /* MINESWEEPER_H */