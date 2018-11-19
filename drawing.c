#include "drawing.h"

void setLocale()
{
	setlocale(LC_CTYPE, "");
}

void drawTopLeftCorner()
{
	DRAW(BOXDRAW_TOP_LEFT);
}

void drawTopRightCorner()
{
	DRAW(BOXDRAW_TOP_RIGHT);
}

void drawBotLeftCorner()
{
	DRAW(BOXDRAW_BOT_LEFT);
}

void drawBotRightCorner()
{
	DRAW(BOXDRAW_BOT_RIGHT);
}

void drawHorizLine(int length)
{
	for (int i = 0; i < length; i++)
	{
		DRAW(BOXDRAW_HORIZONTAL);
	}
}

void drawTopBorder(int length)
{
	drawTopLeftCorner();
	drawHorizLine(length - 2);
	drawTopRightCorner();
}

void drawBotBorder(int length)
{
	drawBotLeftCorner();
	drawHorizLine(length - 2);
	drawBotRightCorner();
}

void drawHorizLineTicked(int length, int direction)
{
	wchar_t symbol = (direction == 0) ? BOXDRAW_HORIZ_BOT : BOXDRAW_HORIZ_TOP;
	for (int i = 0; i < length; i++)
	{
		DRAW(symbol);
	}
}

void drawTopBorderTicked(int length)
{
	drawTopLeftCorner();
	drawHorizLineTicked(length - 2, 1);
	drawTopRightCorner();
}

void drawCross()
{
	DRAW(BOXDRAW_CROSS);
}

void drawVertTicked(int direction)
{
	wchar_t symbol = (direction == 0) ? BOXDRAW_VERT_LEFT : BOXDRAW_VERT_RIGHT;
	DRAW(symbol);
}
