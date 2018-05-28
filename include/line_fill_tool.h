//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
/*************************************************************************
Line-fill tool.
This class is inherited from "tool_base" to define a tool for filling
shapes using the scan line algorithm on a canvas_buffer. 
Read the information in "tool_base.h" for more information.
*************************************************************************/
#pragma once

// provides the declaration of the super class tool_base
#include "tool_base.h"
// needed for a double ended queue
#include <deque>
#include <queue>

using namespace std;

struct pixel {
	int x, y;
};

class line_fill_tool: public tool_base
{
public:
	// Initialize the tool and store a reference of a canvas_buffer
	line_fill_tool(canvas_buffer &canvas);

	// Fill the shape that contains the point (x, y)
	void draw(int x, int y);

	// Put debug output into the stream "stream" to be displayed in the
	// main window
	void set_text(stringstream& stream);

private:
	void fill_tool_helper(pixel p);
	void check_neighbours(pixel p);

	queue<pixel> linestack;
};