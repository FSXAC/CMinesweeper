#ifndef DRAWING_H
#define DRAWING_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

// Box-drawing characters (https://www.unicode.org/charts/PDF/U2500.pdf)
#define BOXDRAW_HORIZONTAL	0x2500
#define BOXDRAW_VERTICAL	0x2502
#define BOXDRAW_TOP_LEFT	0x250C
#define BOXDRAW_TOP_RIGHT	0x2510
#define BOXDRAW_BOT_LEFT	0x2514
#define BOXDRAW_BOT_RIGHT	0x2518
#define BOXDRAW_VERT_RIGHT	0x251C
#define BOXDRAW_VERT_LEFT	0x2524
#define BOXDRAW_HORIZ_BOT	0x252C
#define BOXDRAW_HORIZ_TOP	0x2534
#define BOXDRAW_CROSS		0x253C


// Tools
#define DRAW(x) wprintf(L"%lc", x)
void setLocale();

// Drawing functions
void drawTopLeftCorner();
void drawTopRightCorner();
void drawBotLeftCorner();
void drawBotRightCorner();

void drawHorizLine(int length);
void drawTopBorder(int length);
void drawBotBorder(int length);

void drawHorizLineTicked(int length, int direction);
void drawTopBorderTicked(int length);

void drawCross();
void drawVertTicked(int direction);

#endif