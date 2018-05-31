//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "rectangle_tool.h"
#include <algorithm>


// Initialize the tool and store a reference of a canvas_buffer
rectangle_tool::rectangle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	shape = TS_BOX;
}



// Draw a box from (x0, y0) to (x1, y1)
void rectangle_tool::draw(int x0, int y0, int x1, int y1)
{
	/************
	Additional task: Implement the rasterization of a rectangle that
	                 ranges from (x0, y0) to (x1, y1).
    Zusatzaufgabe:   Implementieren Sie die Rasterisierung eines
	                 Rechtecks, das von (x0, y0) nach (x1, y1) geht.
	*************/

	if (x1 < x0)
		std::swap(x0, x1);
	if (y1 < y0)
		std::swap(y0, y1);

	// horizontal lines
	if (y0 < canvas.get_height() && y0 >= 0)
		for (int x = x0; x < x1; x++) {
			if (x < canvas.get_width() && x >= 0)
				canvas.set_pixel(x, y0);
		}
	if (y1 < canvas.get_height() && y1 >= 0)
		for (int x = x0; x <= x1; x++) {
			if (x < canvas.get_width() && x >= 0)
				canvas.set_pixel(x, y1);
		}

	// verrical lines
	if (x0 < canvas.get_width() && x0 >= 0)
		for (int y = y0; y < y1; y++) {
			if (y < canvas.get_height() && y >= 0)
				canvas.set_pixel(x0, y);
		}
	if (x1 < canvas.get_width() && x1 >= 0)
		for (int y = y0; y <= y1; y++) {
			if (y < canvas.get_height() && y >= 0)
				canvas.set_pixel(x1, y);
		}
}



// Put debug output into the stream "stream" to be displayed in the
// main window
void rectangle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Rectangle (click and drag mouse to draw)";
}