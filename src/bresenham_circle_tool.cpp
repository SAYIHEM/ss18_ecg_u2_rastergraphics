//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bresenham_circle_tool.h"
#include <algorithm>
#include <math.h>

// Initialize the tool and store a reference of a canvas_buffer
bresenham_circle_tool::bresenham_circle_tool(canvas_buffer& canvas): tool_base(canvas)
{
	// This tool draws circles!
	shape = TS_CIRCLE;
}


struct cycle_drawer {
	int xm, ym; // midpoints

	void draw_cycle_point(int x, int y, canvas_buffer &canvas) {
		if (x + xm < canvas.get_width() && x + xm >= 0 && y + ym < canvas.get_height() && y + ym >= 0)
			canvas.set_pixel(x + xm, y + ym);
	}
};


// Draw a circle with center (x0, y0) and (x1, y1) on the circle
void bresenham_circle_tool::draw(int x0, int y0, int x1, int y1)
{
	// Calculate the radius
	int r = static_cast<int>(sqrt(static_cast<double>((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1))));

	/************
	Additional task: Implement circle rasterization using the bresenham algorithm.
	                 The circle shall have its center at (x0, y0) with a
					 radius of "r".
    Zusatzaufgabe:   Implementieren Sie die Rasterisierung eines Kreises mit dem
	                 Bresenham-Algorithmus. Der Kreis soll seinen Mittelpunkt bei
					 (x0, y0) und einen Radius von "r" haben.
	*************/

	int d = -r;
	int dy = 0, dx = r;

	cycle_drawer cd;
	cd.xm = x0;
	cd.ym = y0;

	while (dx >= dy) {

		cd.draw_cycle_point(dx, dy, canvas);
		cd.draw_cycle_point(-dx, dy, canvas);
		cd.draw_cycle_point(dx, -dy, canvas);
		cd.draw_cycle_point(-dx, -dy, canvas);
		cd.draw_cycle_point(dy, dx, canvas);
		cd.draw_cycle_point(-dy, dx, canvas);
		cd.draw_cycle_point(dy, -dx, canvas);
		cd.draw_cycle_point(-dy, -dx, canvas);

		d += 2 * dy + 1;
		dy++;

		if (d > 0) {
			d += -2 * dx + 2;
			dx--;
		}
	}

}



// Put debug output into the stream "stream" to be displayed in the
// main window
void bresenham_circle_tool::set_text(std::stringstream& stream)
{
	stream<<"Tool: Bresenham-Circle (click and drag mouse to draw)";
}