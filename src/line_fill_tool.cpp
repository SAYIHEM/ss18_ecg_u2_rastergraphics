//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "line_fill_tool.h"


// Initialize the tool and store a reference of a canvas_buffer
line_fill_tool::line_fill_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool has no shape and is not draggable
	shape = TS_NONE;
	is_draggable = false;
}

// Fill the shape that contains the point (x, y)
void line_fill_tool::draw(int x, int y)
{
	/************
	Additional task: Implement the line fill algorithm. You can declare
	                 helper methods and properties in the header file if needed and
					 implement them here.
    Zusatzaufgabe:   Implementieren Sie den Line-Fill-Algorithmus. Falls benoetigt
	                 koennen Sie sich Helfermethoden in der dazugehoerigen Header-Datei
					 deklarieren und in dieser Datei definieren.
	*************/

	// Go to start position
	while ((x + 1) < canvas.get_width() && !canvas.get_pixel(x + 1, y)) {
		x++;
	}

	pixel p;
	p.x = x;
	p.y = y;

	linestack.push(p);
	
	while (!linestack.empty()) {
		pixel current = linestack.front();
		canvas.set_pixel(current.x, current.y);

		while (current.x - 1 >= 0 && !canvas.get_pixel(current.x - 1, current.y)) {
			canvas.set_pixel(current.x - 1, current.y);
			check_neighbours(current);
			current.x--;
		}

		linestack.pop();
	}
}

// TODO: Fix neighbour detection
void line_fill_tool::check_neighbours(pixel p) {

	pixel n;

	// top-right
	n.x = p.x + 1;
	n.y = p.y + 1;
	if ((n.x + 1) < canvas.get_width() && !canvas.get_pixel(n.x, n.y) && canvas.get_pixel(n.x + 1, n.y)) {
		linestack.push(n);
	}

	// top
	n.x = p.x;
	n.y = p.y + 1;
	if ((n.x + 1) < canvas.get_width() && !canvas.get_pixel(n.x, n.y) && canvas.get_pixel(n.x + 1, n.y)) {
		linestack.push(n);
	}

	// bottom-right
	n.x = p.x - 1;
	n.y = p.y - 1;
	if ((n.x + 1) < canvas.get_width() && !canvas.get_pixel(n.x, n.y) && canvas.get_pixel(n.x + 1, n.y)) {
		linestack.push(n);
	}

	// bottom
	n.x = p.x;
	n.y = p.y - 1;
	if ((n.x + 1) < canvas.get_width() && !canvas.get_pixel(n.x, n.y) && canvas.get_pixel(n.x + 1, n.y)) {
		linestack.push(n);
	}

}




// Put debug output into the stream "stream" to be displayed in the
// main window
void line_fill_tool::set_text(stringstream& stream)
{
	stream<<"Tool: Line Fill (click to fill)";
}


