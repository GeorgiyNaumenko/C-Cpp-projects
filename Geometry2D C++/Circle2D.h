#pragma once
#include "Point2D.h"
#include "Line2D.h"

class Circle2D{

public:

	double r;
	Point2D o;

	Circle2D();
	Circle2D(Point2D center, double radius);

	void console_show_circle();
	void textfile_show_circle(const char* filename);
	Line2D tangent_to_circle(Point2D* t);
	Line2D radical_axis(Circle2D* other);
	Point2D radical_center(Circle2D* other1, Circle2D* other2);

};

