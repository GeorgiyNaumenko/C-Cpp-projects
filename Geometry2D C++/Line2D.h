#pragma once
#include "Point2D.h"
#include "Segment2D.h"

class Line2D{

public:

	double a, b, c;

	Line2D();
	Line2D(double a1, double b1, double c1);
	Line2D(Point2D a1, Point2D b1);

	Point2D intersection_l_s(Segment2D* other);
	Point2D intersection_l_l(Line2D* other);
	void console_show_line();
	void textfile_show_line(const char* filename);

};