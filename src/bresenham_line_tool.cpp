//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bresenham_line_tool.h"
#include <algorithm>
#include <math.h>

using namespace std;

// Initialize the tool and store a reference of a canvas_buffer
bresenham_line_tool::bresenham_line_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool draws lines!
	shape = TS_LINE;
}




// Draw a line from (x0, y0) to (x1, y1)
void bresenham_line_tool::draw(int x0, int y0, int x1, int y1)
{
	/************
	Task 3.1.2.    Implement the Bresenham algorithm to raster a line from (x0, y0)
	               to (x1, y1). To set a pixel use "canvas.set_pixel(x, y)" where
				   "x" and "y" is the desired pixel position. This method 
				   handles border violations. Establish the standard case in the
				   first step. If you need to swap the value of two variables you
				   can use the method "std::swap(a, b)".
	Aufgabe 3.1.2. Implementieren Sie den Bresenham-Algorithmus um eine Linie von
	               (x0, y0) nach (x1, y1) zu rastern. Verwenden Sie
				   "canvas.set_pixel(x, y)" um einen Pixel zu setzen, wobei
				   "x" und "y" den gewünschten Pixelpositionen entsprechen.
				   Diese Methode behandelt auch Randverletzungen. Stellen Sie zunaechst
				   den Standardfall her. Falls Sie den Wert zweier Variablen vertauschen
				   muessen koennen Sie dafür die Methode "std::swap(a, b)" verwenden.
   *************/

	bool sign_swap_x = false, sign_swap_y = false, swap_x_y = false;

	int dx = x1 - x0;
	int dy = y1 - y0;

	if (dx < 0) {
		sign_swap_x = true;
		dx *= -1;
	}
	if (dy < 0) {
		sign_swap_y = true;
		dy *= -1;
	}
	if (dx < dy) {
		swap_x_y = true;
		std::swap(dx, dy);
		std::swap(sign_swap_x, sign_swap_y);
	}

	int c = 2 * dy + dx;
	int dist = 0;
	int height = -1; 

	for (int counter = 0; counter <= dx; counter++) {

		int dx_new = counter;

		if (2 * dist >= c) {
			dist -= dy;
		}
		else {
			dist -= dy - dx;
			height++;
		}

		int dy_new = height;

		if (sign_swap_x)
			dx_new *= -1;
		if (sign_swap_y)
			dy_new *= -1;
		if (swap_x_y)
			std::swap(dx_new, dy_new);

		int x_new = x0 + dx_new;
		int y_new = y0 + dy_new;

		if (x_new < canvas.get_width() && x_new >= 0 && y_new < canvas.get_height() && y_new >= 0)
			canvas.set_pixel(x_new, y_new);
	}
	
}




// Put debug output into the stream "stream" to be displayed in the
// main window
void bresenham_line_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Bresenham-Line (click and drag mouse to draw)";
}
