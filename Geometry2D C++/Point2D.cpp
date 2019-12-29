#pragma once
#include "Point2D.h"
#include <cmath>

Point2D::Point2D() {

	x = 0.0;
	y = 0.0;
}

Point2D::Point2D(double x1, double y1) {

	x = x1;
	y = y1;
}

Point2D Point2D::add(Point2D* other) {

	return Point2D(this->x + other->x, this->y + other->y);

}

Point2D Point2D::homot(double lambda) {

	return Point2D(this->x * lambda, this->y * lambda);

}

double Point2D::mul(Point2D* other) {

	return this->x * other->y - this->x * other->y;

}

double Point2D::mulS(Point2D* other) {

	return this->x * other->x + this->y * other->y;

}

double Point2D::two_points_length(Point2D* other) {

	return sqrt((other->x - this->x) * (other->x - this->x) + (other->y - this->y) * (other->y - this->y));

}
