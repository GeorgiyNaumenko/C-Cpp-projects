#pragma once
#include "Point2D.h"

class Segment2D {

public:

	Point2D a, b;

	Segment2D();
	Segment2D(Point2D a1, Point2D b1);

	double length();
	Point2D intersection_s_s(Segment2D* other);

};