#pragma once
#include "Point2D.h"
#include "Line2D.h"
#include "Circle2D.h"

class Triangle2D{

public:

	Point2D a, b, c;

	Triangle2D();
	Triangle2D(Point2D a1, Point2D b1, Point2D c1);

	double perimeter();
	double area();
	Point2D center();
	Point2D inceter();
	Point2D centroid();
	Point2D orthocenter();
	Circle2D inscribed_circle();
	Circle2D described_circle();
	double inscribed_radius();
	double described_radius();
	double angelA();
	double angelB();
	double angelC();
	Line2D medianA();
	Line2D medianB();
	Line2D medianC();
	Line2D bisectorA();
	Line2D bisectorB();
	Line2D bisectorC();
	Line2D heigthA();
	Line2D heigthB();
	Line2D heigthC();
	Line2D symmedianA();
	Line2D symmedianB();
	Line2D symmedianC();
	Point2D lemuan_point();
	Circle2D unwritten_circle_AB();
	Circle2D unwritten_circle_BC();
	Circle2D unwritten_circle_AC();
	Point2D nikel_point();
	Circle2D euler_circle();

};

