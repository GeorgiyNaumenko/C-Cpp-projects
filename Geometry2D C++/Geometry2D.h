#pragma once
#include "Triangle2D.h"
#include "Line2D.h"

class Geometry2D {

public:

	Triangle2D a;
	Line2D l;
	double s1, s2;

	Geometry2D();
	Geometry2D(Triangle2D a1, Line2D l1);

	int inputGeometry2D();
	void outputGeometry2D();
	int inputBinaryFile(const char* filename);
	int outputBinaryFile(const char* filename);
	int inputTextFile(const char* filename);
	int outputTextFile(const char* filename);

	void find_two_areas();
};