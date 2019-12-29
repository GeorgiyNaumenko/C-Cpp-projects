#pragma once
#include "Circle2D.h"
#include <fstream>
#include "Point2D.h"
#include "Line2D.h"
#include <iostream>

using namespace std;

Circle2D::Circle2D() {

}

Circle2D::Circle2D(Point2D center, double radius) {

	o = center;
	r = radius;

}

void Circle2D::console_show_circle() {

    cout << "(x";
    if (this->o.x > 0) {
        cout << " - " << this->o.x << ")^2";
    }
    else if (this->o.x < 0) {
        cout << " + " << (-1.0) * this->o.x << ")^2";
    }
    else {
        cout << ")^2";
    }

    cout << " + ";

    cout << "(y";
    if (this->o.y > 0) {
        cout << " - " << this->o.y << ")^2";
    }
    else if (this->o.y < 0) {
        cout << " + " << (-1.0) * this->o.y << ")^2";
    }
    else {
        cout << ")^2";
    }

    cout << " = ";

    cout << this->r * this->r << endl;

}

void Circle2D::textfile_show_circle(const char* filename) {

    ofstream fout;

    fout.open(filename, ofstream::app);

    fout << "(x";
    if (this->o.x > 0) {
        fout << " - " << this->o.x << ")^2";
    }
    else if (this->o.x < 0) {
        fout << " + " << (-1.0) * this->o.x << ")^2";
    }
    else {
        fout << ")^2";
    }

    fout << " + ";

    fout << "(y";
    if (this->o.y > 0) {
        fout << " - " << this->o.y << ")^2";
    }
    else if (this->o.y < 0) {
        fout << " + " << (-1.0) * this->o.y << ")^2";
    }
    else {
        fout << ")^2";
    }

    fout << " = ";

    fout << this->r * this->r << "\n";

}

Line2D Circle2D::tangent_to_circle(Point2D* t) {

    Line2D tang;
    tang.a = this->o.x - t->x;
    tang.b = this->o.y - t->y;
    tang.c = t->x * t->x - t->x * this->o.x;
    tang.a = t->x - this->o.x;
    tang.b = t->y - this->o.y;
    tang.c = t->x * this->o.x + t->y * this->o.y - t->x * t->x - t->y * t->y;
    return tang;

}

Line2D Circle2D::radical_axis(Circle2D* other) {

    Line2D axis;
    axis.a = 2 * (other->o.x - this->o.x);
    axis.b = 2 * (other->o.y - this->o.y);
    axis.c = this->o.y * this->o.y + this->o.x * this->o.x - this->r * this->r - (other->o.y * other->o.y + other->o.x * other->o.x - other->r * other->r);
    return axis;

}

Point2D Circle2D::radical_center(Circle2D* other1, Circle2D* other2) {

    Line2D axis1, axis2;
    axis1 = other1->radical_axis(this);
    axis2 = other1->radical_axis(other1);
    Point2D rad_c;
    rad_c = axis1.intersection_l_l(&axis2);
    return rad_c;

}