#pragma once
#include "Line2D.h"
#include <cmath>
#include "Point2D.h"
#include "Segment2D.h"
#include <iostream>
#include <fstream>
using namespace std;

Line2D::Line2D() {

    a = 0;
    b = 0;
    c = 0;

}

Line2D::Line2D(double a1, double b1, double c1) {
	a = a1;
	b = b1;
	c = c1;
}

Line2D::Line2D(Point2D a1, Point2D b1) {

    a = a1.y - b1.y;
    b = b1.x - a1.x;
    c = a1.x * b1.y - a1.y * b1.x;

}

Point2D Line2D::intersection_l_l(Line2D* other) {

    double k1, k2, b1, b2, x, y;     /* I'm going to represent equations of lines a and b in canonical form */
    int flag;
    Point2D intersection;

    k1 = (-1.0) * this->a / this->b;
    b1 = (-1.0) * this->c / this->b;
    k2 = (-1.0) * other->a / other->b;
    b2 = (-1.0) * other->c / other->b;

    if (k1 == k2) {
        if (b1 == b2) {
            flag = 2;    /* line a coincides with line b */
        }
        else {
            flag = 0;    /* lines are parallel */
        }
    }
    else {
        flag = 1;     /* lines will always have the point of intersection in this case so here we can find it */
        x = (b2 - b1) / (k1 - k2);
        y = k1 * x + b1;
    }

    if (flag == 1) {
        intersection.x = x;
        intersection.y = y;
    }
    else if (flag == 0) {
        intersection.x = HUGE_VAL;
        intersection.y = -HUGE_VAL;
    }
    else {
        intersection.x = HUGE_VAL;
        intersection.y = HUGE_VAL;
    }

    return intersection;

}

Point2D Line2D::intersection_l_s(Segment2D* other) {

    /* with points b.a and b.b from segment all actions are similar to the previous function */
    double x1 = other->a.x, x2 = other->b.x, y1 = other->a.y, y2 = other->b.y;
    double k1, b1, x, y;
    int flag;
    Point2D intersection;

    if (x1 >= x2) {
        x1 = x1 + x2;
        x2 = x1 - x2;
        x1 = x1 - x2;
        y1 = y1 + y2;
        y2 = y1 - y2;
        y1 = y1 - y2;
    }

    if (x1 == x2) {
        k1 = 1.0;
    }
    else if (y1 == y2) {
        k1 = 0.0;
    }
    else {
        k1 = (y2 - y1) / (x2 - x1);
    }

    b1 = y1 - k1 * x1;

    if ((-1.0) * this->a / this->b == k1) {    /* a*x + b*y + c = 0, so y = -a/b*x - c/b */
        if (b1 = (-1.0) * this->c / this->b) {
            flag = 2;       /* we will have that our segment lies on our line */
        }
        else {           /* we will have that our segment is parallel to our line */
            flag = 0;
        }
    }
    else {
        /* y = k1*x + b1 and a*x + b*y + c = 0, so x = -(c + b1*b) / (a + b*k1) */
        x = (-1.0) * (this->c + b1 * this->b) / (this->a + this->b * k1);
        y = k1 * x + b1;
        /* (x, y) may be the point of intersection, but now we must check if it lies on our segment */

        if ((x1 <= x) && (x <= x2)) {
            flag = 1;
        }
        else {
            flag = 0;
        }
    }

    /* depending on the value of flag we can create our point of intersection */
    if (flag == 1) {
        intersection.x = x;
        intersection.y = y;
    }
    else if (flag == 0) {
        intersection.x = HUGE_VAL;
        intersection.y = -HUGE_VAL;
    }
    else {
        intersection.x = HUGE_VAL;
        intersection.y = HUGE_VAL;
    }

    return intersection;

}

void Line2D::console_show_line() {

    if (this->a > 0) {
        cout << this->a << "x ";
    }
    else if (this->a < 0) {
        cout << "-" << this->a << "x ";
    }
    if (this->b > 0) {
        cout << "+ " << this->b << "y ";
    }
    else if (this->b < 0) {
        cout << "- " << (-1.0) * this->b << "y ";
    }
    if (this->c > 0) {
        cout << "+ " << this->c;
    }
    else if (this->c < 0) {
        cout << "- " << (-1.0) * this->c;
    }
    cout << " = 0" << endl;

}

void Line2D::textfile_show_line(const char* filename) {

    ofstream fout;

    fout.open(filename, ofstream::app);

    if (this->a > 0) {
        fout << this->a << "x ";
    }
    else if (this->a < 0) {
        fout << "-" << this->a << "x ";
    }
    if (this->b > 0) {
        fout << "+ " << this->b << "y ";
    }
    else if (this->b < 0) {
        fout << "- " << (-1.0) * this->b << "y ";
    }
    if (this->c > 0) {
        fout << "+ " << this->c;
    }
    else if (this->c < 0) {
        fout << "- " << (-1.0) * this->c;
    }
    fout << " = 0" << "\n";

}