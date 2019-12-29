#pragma once
#include "Triangle2D.h"
#include "Circle2D.h"
#include "Point2D.h"
#include "Segment2D.h"
#include "Line2D.h"
#include <cmath>
#include <iostream>

Triangle2D::Triangle2D() {

}

Triangle2D::Triangle2D(Point2D a1, Point2D b1, Point2D c1) {

	a = a1;
	b = b1;
	c = c1;

}

double Triangle2D::perimeter() {

	return this->a.two_points_length(&this->b) + this->b.two_points_length(&this->c) + this->c.two_points_length(&this->a);

}

double Triangle2D::area() {

    double p = this->perimeter() / 2, ab = a.two_points_length(&this->b), bc = this->b.two_points_length(&this->c), ac = this->c.two_points_length(&this->a);
    return sqrt(p * (p - ab) * (p - bc) * (p - ac));

}

Point2D Triangle2D::center() {

    Line2D mid_per_AC, mid_per_AB;
    Point2D M_ac, M_ab, center;
    double k1, k2, k3, k4, b1, b2;
    M_ac.x = (this->a.x + this->c.x) / 2.0;  /* midpoints of AC and AB */
    M_ab.x = (this->a.x + this->b.x) / 2.0;
    M_ac.y = (this->a.y + this->c.y) / 2.0;
    M_ab.y = (this->a.y + this->b.y) / 2.0;
    k1 = (this->b.y - this->a.y) / (this->b.x - this->a.x);  /* angular coefficients of AB and AC*/
    k2 = (this->c.y - this->a.y) / (this->c.x - this->a.x);
    k3 = (-1.0) / k1;                  /* angular coefficients of middle perpendiculars to AB and AC */
    k4 = (-1.0) / k2;
    b1 = M_ab.y - k3 * M_ab.x;
    b2 = M_ac.y - k4 * M_ac.x;
    mid_per_AB.b = 1.0;
    mid_per_AB.a = (-1.0) * k3;
    mid_per_AB.c = (-1.0) * b1;
    mid_per_AC.b = 1.0;
    mid_per_AC.a = (-1.0) * k4;
    mid_per_AC.c = (-1.0) * b2;
    center = mid_per_AB.intersection_l_l(&mid_per_AC);

    return center;

}

Point2D Triangle2D::inceter() {

    Point2D Ta, Tb, Tc, cent;         /* Ta, Tb and Tc - tangent points of inscrible in triangle circle with segments BC, AC and AB respectively */
    Triangle2D t;
    Triangle2D* p_t = &t;
    double ab, ac, bc, p, lambda_ab, lambda_ac, lambda_bc;
    double x1 = this->a.x, x2 = this->b.x, x3 = this->c.x, y1 = this->a.y, y2 = this->b.y, y3 = this->c.y;
    p = this->perimeter() / 2.0;
    ab = this->a.two_points_length(&this->b);
    bc = this->b.two_points_length(&this->c);
    ac = this->a.two_points_length(&this->c);
    lambda_ab = (p - bc) / (p - ac);                       /* ratio of segments, for example lambda_ab = ATc / TcB */
    lambda_bc = (p - ac) / (p - ab);
    lambda_ac = (p - ab) / (p - bc);
    Tc.x = (x1 + lambda_ab * x2) / (1.0 + lambda_ab);      /* here we can find coordinates of points Ta, Tb and Tc */
    Tc.y = (y1 + lambda_ab * y2) / (1.0 + lambda_ab);
    Ta.x = (x2 + lambda_bc * x3) / (1.0 + lambda_bc);
    Ta.y = (y2 + lambda_bc * y3) / (1.0 + lambda_bc);
    Tb.x = (x3 + lambda_ac * x1) / (1.0 + lambda_ac);
    Tb.y = (y3 + lambda_ac * y1) / (1.0 + lambda_ac);
    t.a = Ta;
    t.b = Tb;
    t.c = Tc;
    cent = p_t->center();                       /* The main idea is that inscribed in ABC sircle is described around TaTbTc circle */

    return cent;

}

Point2D Triangle2D::centroid() {

    return this->medianA().intersection_l_l(&this->medianB());

}

Point2D Triangle2D::orthocenter() {

    return this->heigthA().intersection_l_l(&this->heigthB());

}

Circle2D Triangle2D::inscribed_circle() {

    return Circle2D(this->inceter(), this->inscribed_radius());

}

Circle2D Triangle2D::described_circle() {

    return Circle2D(this->center(), this->described_radius());

}

double Triangle2D::described_radius() {

    return this->center().two_points_length(&this->a);

}

double Triangle2D::inscribed_radius() {

    return 2.0 * this->area() / this->perimeter();

}

double Triangle2D::angelA() {

    Point2D ab_v, ac_v, min_a;

    min_a = a.homot(-1.0);
    ab_v = min_a.add(&this->b);
    ac_v = min_a.add(&this->c);

    return acos(ab_v.mulS(&ac_v) / (this->a.two_points_length(&this->b) * this->a.two_points_length(&this->c)));

}

double Triangle2D::angelB() {

    Point2D ba_v, bc_v, min_b;

    min_b = b.homot(-1.0);
    ba_v = min_b.add(&this->a);
    bc_v = min_b.add(&this->c);

    return acos(ba_v.mulS(&bc_v) / (this->b.two_points_length(&this->a) * this->b.two_points_length(&this->c)));

}

double Triangle2D::angelC() {

    Point2D ca_v, cb_v, min_c;

    min_c = c.homot(-1.0);
    ca_v = min_c.add(&this->a);
    cb_v = min_c.add(&this->b);

    return acos(ca_v.mulS(&cb_v) / (this->c.two_points_length(&this->b) * this->a.two_points_length(&this->c)));

}

Line2D Triangle2D::medianA() {

    Point2D m = Point2D((this->b.x + this->c.x) / 2.0, (this->b.y + this->c.y) / 2.0);

    return Line2D(this->a, m);

}

Line2D Triangle2D::medianB() {

    Point2D m = Point2D((this->a.x + this->c.x) / 2.0, (this->a.y + this->c.y) / 2.0);

    return Line2D(this->b, m);

}

Line2D Triangle2D::medianC() {

    Point2D m = Point2D((this->a.x + this->b.x) / 2.0, (this->a.y + this->b.y) / 2.0);

    return Line2D(this->c, m);

}

Line2D Triangle2D::bisectorA() {

    return Line2D(this->a, this->inceter());

}

Line2D Triangle2D::bisectorB() {

    return Line2D(this->b, this->inceter());

}

Line2D Triangle2D::bisectorC() {

    return Line2D(this->c, this->inceter());

}

Line2D Triangle2D::heigthA() {

    Line2D bc = Line2D(this->c, this->b);

    return Line2D((-1.0) * bc.b, bc.a, bc.b * this->a.x - bc.a * this->a.y);

}

Line2D Triangle2D::heigthB() {

    Line2D ac = Line2D(this->a, this->c);

    return Line2D((-1.0) * ac.b, ac.a, ac.b * this->b.x - ac.a * this->b.y);

}

Line2D Triangle2D::heigthC() {

    Line2D ab = Line2D(this->a, this->b);

    return Line2D((-1.0) * ab.b, ab.a, ab.b * this->c.x - ab.a * this->c.y);

}

Line2D Triangle2D::symmedianA() {

    Point2D t = this->described_circle().tangent_to_circle(&this->c).intersection_l_l(&this->described_circle().tangent_to_circle(&this->b));

    return Line2D(t, this->a);

}

Line2D Triangle2D::symmedianB() {

    Point2D t = this->described_circle().tangent_to_circle(&this->c).intersection_l_l(&this->described_circle().tangent_to_circle(&this->a));

    return Line2D(t, this->b);

}

Line2D Triangle2D::symmedianC() {

    Point2D t = this->described_circle().tangent_to_circle(&this->a).intersection_l_l(&this->described_circle().tangent_to_circle(&this->b));

    return Line2D(t, this->c);

}

Point2D Triangle2D::lemuan_point() {

    return this->symmedianA().intersection_l_l(&this->symmedianB());

}

Circle2D Triangle2D::unwritten_circle_AB() {

    double p = this->perimeter() / 2.0, lambda;
    Point2D t, j;
    Line2D a_b = Line2D(this->a, this->b), perp;
    Segment2D ac = Segment2D(this->a, this->c), bc = Segment2D(this->b, this->c);
    lambda = (p - ac.length()) * (p - bc.length());
    t = Point2D((this->a.x + lambda * this->b.x) / (1.0 + lambda), (this->a.y + lambda * this->b.y) / (1.0 + lambda));
    perp = Line2D((-1.0) * a_b.b, a_b.a, a_b.b * t.x - a_b.a * t.y);
    j = perp.intersection_l_l(&this->bisectorC());
    Segment2D rad = Segment2D(j, t);

    return Circle2D(j, rad.length());

}

Circle2D Triangle2D::unwritten_circle_BC() {

    double p = this->perimeter() / 2.0, lambda;
    Point2D t, j;
    Line2D b_c = Line2D(this->c, this->b), perp;
    Segment2D ac = Segment2D(this->a, this->c), ab = Segment2D(this->b, this->a);
    lambda = (p - ab.length()) * (p - ac.length());
    t = Point2D((this->b.x + lambda * this->c.x) / (1.0 + lambda), (this->b.y + lambda * this->c.y) / (1.0 + lambda));
    perp = Line2D((-1.0) * b_c.b, b_c.a, b_c.b * t.x - b_c.a * t.y);
    j = perp.intersection_l_l(&this->bisectorA());
    Segment2D rad = Segment2D(j, t);

    return Circle2D(j, rad.length());

}

Circle2D Triangle2D::unwritten_circle_AC() {

    double p = this->perimeter() / 2.0, lambda;
    Point2D t, j;
    Line2D a_c = Line2D(this->a, this->c), perp;
    Segment2D ab = Segment2D(this->a, this->b), bc = Segment2D(this->b, this->c);
    lambda = (p - bc.length()) * (p - ab.length());
    t = Point2D((this->c.x + lambda * this->a.x) / (1.0 + lambda), (this->c.y + lambda * this->a.y) / (1.0 + lambda));
    perp = Line2D((-1.0) * a_c.b, a_c.a, a_c.b * t.x - a_c.a * t.y);
    j = perp.intersection_l_l(&this->bisectorB());
    Segment2D rad = Segment2D(j, t);

    return Circle2D(j, rad.length());

}

Point2D Triangle2D::nikel_point() {

    double x1 = this->a.x, x2 = this->b.x, x3 = this->c.x;
    double y1 = this->a.y, y2 = this->b.y, y3 = this->c.y;

    Segment2D ab = Segment2D(this->a, this->b);
    Segment2D bc = Segment2D(this->b, this->c);
    Segment2D ac = Segment2D(this->a, this->c);

    double p = this->perimeter() / 2.0;

    double lambda_ab = (p - ac.length()) / (p - bc.length());
    double lambda_bc = (p - ab.length()) / (p - ac.length());
    double lambda_ac = (p - bc.length()) / (p - ab.length());

    Point2D Tc = Point2D((x1 + lambda_ab * x2) / (1.0 + lambda_ab), (y1 + lambda_ab * y2) / (1.0 + lambda_ab));
    Point2D Ta = Point2D((x2 + lambda_ab * x3) / (1.0 + lambda_ab), (y2 + lambda_ab * y3) / (1.0 + lambda_ab));
    Point2D Tb = Point2D((x3 + lambda_ab * x1) / (1.0 + lambda_ab), (y3 + lambda_ab * y1) / (1.0 + lambda_ab));

    Line2D tca = Line2D(Tc, Ta);
    Line2D tcb = Line2D(Tc, Tb);
    Line2D tab = Line2D(Tb, Ta);

    return tca.intersection_l_l(&tab);

}

Circle2D Triangle2D::euler_circle() {

    Point2D ma = Point2D((this->b.x + this->c.x) / 2.0, (this->b.y + this->c.y) / 2.0);
    Point2D mb = Point2D((this->a.x + this->c.x) / 2.0, (this->a.y + this->c.y) / 2.0);
    Point2D mc = Point2D((this->b.x + this->a.x) / 2.0, (this->b.y + this->a.y) / 2.0);

    Triangle2D mid = Triangle2D(ma, mb, mc);

    return mid.described_circle();

}
