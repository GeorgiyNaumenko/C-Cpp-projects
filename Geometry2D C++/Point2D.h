#pragma once

class Point2D {

public:

	double x, y;

	Point2D();
	Point2D(double x1, double y1);

	Point2D add(Point2D* other);
	Point2D homot(double lambda);
	double mul(Point2D* other);
	double mulS(Point2D* otehr);
	double two_points_length(Point2D* other);
};