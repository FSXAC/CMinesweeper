#ifndef CELL_H
#define CELL_H

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

#endif