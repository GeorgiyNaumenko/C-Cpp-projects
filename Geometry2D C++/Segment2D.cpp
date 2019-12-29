#pragma once
#include "Segment2D.h"
#include "Point2D.h"
#include <cmath>

Segment2D::Segment2D() {

    a = Point2D();
    b = Point2D();

}

Segment2D::Segment2D(Point2D a1, Point2D b1) {

	a = a1;
	b = b1;
}

double Segment2D::length() {

	return this->a.two_points_length(&this->b);
}

Point2D Segment2D::intersection_s_s(Segment2D* other) {

    /* it will be more comfortable to work with segments if I create new variables here */
    /* A(x1, y1), B(x2, y2), C(x3, y3), D(x4, y4), my segments: AB and CD */

    double x1 = this->a.x, x2 = this->b.x, x3 = other->a.x, x4 = other->b.x, y1 = this->a.y, y2 = this->b.y, y3 = other->a.y, y4 = other->b.y;
    double k1, k2, b1, b2, x, y;  /* I'm going to find canonical equations of lines passing through my segments */
    int flag = 1;  /* 0 if 0 point, 1 if 1 point, 2 if INF point */
    Point2D intersection;

    if (x1 >= x2) {            /* for correct angular coefficients, we must have: x1 <= x2 and x3 <= x4 */
        x1 = x1 + x2;          /* let's name these two inequalities as (*) */
        x2 = x1 - x2;
        x1 = x1 - x2;
        y1 = y1 + y2;
        y2 = y1 - y2;
        y1 = y1 - y2;
    }

    if (x3 >= x4) {
        x3 = x3 + x4;
        x4 = x3 - x4;
        x3 = x3 - x4;
        y3 = y3 + y4;
        y4 = y3 - y4;
        y3 = y3 - y4;
    }

    /* here we can find angular coefficient k1*/
    if (x1 == x2) {
        k1 = 1.0;
    }
    else if (y1 == y2) {
        k1 = 0.0;
    }
    else {
        k1 = (y2 - y1) / (x2 - x1);
    }

    b1 = y1 - k1 * x1;     /* here we can find a free member*/

    /* and here k2 */
    if (x3 == x4) {
        k2 = 1.0;
    }
    else if (y3 == y4) {
        k2 = 0.0;
    }
    else {
        k2 = (y4 - y3) / (x4 - x3);
    }

    b2 = y3 - k2 * x3;

    /* here we can check what if k1 == k2 */
    if (k1 == k2) {
        if (b1 == b2) {
            if (((x3 < x1) && (x1 < x4)) || ((x3 < x2) && (x2 < x4)) || ((x1 < x3) && (x3 < x2)) || ((x1 < x4) && (x4 < x2))) {
                flag = 2;
            }
            else if ((x1 == x4) || (x2 == x3)) {
                flag = 1;
            }
            else {
                flag = 0;
            }
        }
        else {
            flag = 0;
        }

    }

    /* here we can find our intersection */
    if (flag == 1) {
        x = (b2 - b1) / (k1 - k2);
        y = k1 * x + b1;
        /* and finally we must check, if our intersection point lies on our segments */
        if (((x1 <= x4) && (x4 <= x2)) && ((x1 <= x3) && (x3 <= x2))) {  /* we remember (*) inequalities */
            intersection.x = x;
            intersection.y = y;
        }
        else {
            intersection.x = HUGE_VAL;    /* HUGE_VAL (or -HUGE_VAL) from <math.h> library it's a really huge value */
            intersection.y = -HUGE_VAL;   /*   which can't be represented in double, means plus (or minus) infinity */
        }
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