//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "line_fill_tool.h"
#include <list>
#include <iostream>


// Initialize the tool and store a reference of a canvas_buffer
line_fill_tool::line_fill_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool has no shape and is not draggable
	shape = TS_NONE;
	is_draggable = false;
}

bool pred(pixel a, pixel b) {
	return (a.x == b.x && a.y == b.y);
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

	pixel p = { x , y };

	linestack.push_back(p);

	while (!linestack.empty()) {
		linestack.unique(pred);
		pixel current = linestack.front();
		canvas.set_pixel(current.x, current.y);
		check_neighbours(current);

		while (current.x - 1 >= 0 && !canvas.get_pixel(current.x - 1, current.y)) {
			canvas.set_pixel(current.x - 1, current.y);
			check_neighbours(current);
			current.x--;
		}

		linestack.pop_front();
	}
}

void line_fill_tool::check_neighbours(const pixel p) {

	list<pixel> neighbours;
	pixel n{};

	// Add neighbours to check
	neighbours.push_back({ p.x, p.y + 1 }); // top
	neighbours.push_back({ p.x, p.y - 1 }); // bottom

	for (auto& neighbour : neighbours) {
		if (neighbour.x < 0 || neighbour.x >= canvas.get_width() || 
			neighbour.y < 0 || neighbour.y >= canvas.get_height()) {
			continue;
		}

		if (neighbour.y >= 0 && neighbour.y < canvas.get_height()) {
			if (!canvas.get_pixel(neighbour.x, neighbour.y)) {
				while ((neighbour.x + 1) < canvas.get_width() && !canvas.get_pixel(neighbour.x + 1, neighbour.y)) {
					neighbour.x++;
				}
				linestack.push_back(neighbour);
			}

		}
	}
}




// Put debug output into the stream "stream" to be displayed in the
// main window
void line_fill_tool::set_text(stringstream& stream)
{
	stream<<"Tool: Line Fill (click to fill)";
}


