#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include <math.h>
#include <stdio.h>
#include "common.h"

/* Declaration all types, structures and functions */

/* Point2D type as vector in R^2 or as 2 reals */
typedef struct Point2D_{
  union{
    struct{
      Dtype x;        /* first real coordinate of point */
      Dtype y;        /* second real coordinate of point */
    };
    Dtype vector[2];  /* vector with 2 coordinates */
  };
} Point2D;

/* Segment2D type as 2 points */
typedef struct Segment2D_{
  Point2D a;
  Point2D b;
} Segment2D;

/* Triangle2D type as 3 points */
typedef struct Triangle2D_{
  Point2D a;
  Point2D b;
  Point2D c;
} Triangle2D;

/* Line2D type as 3 reals, which are characterise linear equation ax^2 + by + c = 0 */
typedef struct Line2D_{
  Dtype a;
  Dtype b;
  Dtype c;
} Line2D;

/* I have to calculate the areas of ​​2 figures onto which the triangle cuts off given line,
so what I want to do is the "main type" Geometry2D and members of this type will be Triangle2D and Line2D type objects */
typedef struct Geometry2D_{
  Triangle2D a;
  Line2D l;
  Dtype s1, s2;    /* two areas we want to find */
} Geometry2D;

/* input from keyboard */
extern int inputGeometry2D(Geometry2D* x);

/* output in the console */
extern void outputGeometry2D(Geometry2D x, int percision);

/* input from binary file */
extern int inputBinaryFile(char* filename, Geometry2D* x);

/* output in binary file */
extern int outputBinaryFile(char* filename, Geometry2D x);

/* input from text file */
extern int inputTextFile(char* filename, Geometry2D* x);

/* output in text file */
extern int outputTextFile(char* filename, Geometry2D x, int percision);

/* function "find_two_areas(x)" returns Geometry2D type object and calculate 2 areas we need */
extern Geometry2D find_two_areas(Geometry2D* x);

/* function "add(a, b)" which is adding 2 vectors and returns new Point2D type object as vector*/
extern Point2D add(Point2D* a, Point2D* b);

/* function "mulS(a, b)" returns scalar product of 2 vectors a and b*/
extern Dtype mulS(Point2D* a, Point2D* b);

/* function "mul(a, b)" returns vector product of 2 vectors a and b as a real number wich shows Oz coordinate.
We allways get vector (0, 0, z) and this function returns z. */
extern Dtype mul(Point2D* a, Point2D* b);

/* my gcc compiler can't compile reloading any function, so I created 3 different functions
for intersection*/

/* function "intersection_s_s(a, b)" returns point of intersection of 2 Segment2D type objects if this point exists */
extern Point2D intersection_s_s(Segment2D* a, Segment2D* b);

/* function intersection_l_s(a, b) returns point of intersection of Line2D type object and
Segment2D type object if this point exists */
extern Point2D intersection_l_s(Line2D* a, Segment2D* b);

/* function intersection_s_s(a, b) returns point of intersection of 2 Line2D type objects if this point exists */
extern Point2D intersection_l_l(Line2D* a, Line2D* b);

/* function "two_points_length(a, b)" returns the distance between Point2D type objects a and b */
extern Dtype two_points_length(Point2D* a, Point2D* b);

/* function "segment_length(a)" returns Dtype type length of segment a */
extern Dtype segment_length(Segment2D* a);

/* function "line_through_two_points" returns Line2D object as a line which is passing through points a and b */
extern Line2D line_through_two_points(Point2D* a, Point2D* b);

/* function "perimeter(a)" returns Dtype type perimeter of triangle a */
extern Dtype perimeter(Triangle2D* a);

/* function "area(a)" returns Dtype type area of triangle a */
extern Dtype area(Triangle2D* a);

/* function "incenter(a)" returns Point2D type object - center of inscribed in triangle a circle */
extern Point2D incenter(Triangle2D* a);

/* function "center(a)" returns Point2D type object - center of described around triangle a circle */
extern Point2D center(Triangle2D* a);

/* function "inscribed_radius(a)" returns Dtype type length of inscribed in triangle a circle */
extern Dtype inscribed_radius(Triangle2D* a);

/* function "described_radius(a)" returns Dtype type length of described around triangle a circle */
extern Dtype described_radius(Triangle2D* a);

/* function "angelA(a)" returns Dtype type angle A in radians of triangle a */
extern Dtype angelA(Triangle2D* a);

/* function "angelB(a)" returns Dtype type angle B in radians of triangle a */
extern Dtype angelB(Triangle2D* a);

/* function "angelC(a)" returns Dtype type angle C in radians of triangle a */
extern Dtype angleC(Triangle2D* a);

/* function "medianA(a)" returns Line2D type object - median from A of triangle a */
extern Line2D medianA(Triangle2D* a);

/* function "medianB(a)" returns Line2D type object - median from B of triangle a */
extern Line2D medianB(Triangle2D* a);

/* function "medianC(a)" returns Line2D type object - median from C of triangle a */
extern Line2D medianC(Triangle2D* a);

/* function "bisectorA(a)" returns Line2D type object - INTERNAL bisector from A of triangle a */
extern Line2D bisectorA(Triangle2D* a);

/* function "bisectorB(a)" returns Line2D type object - INTERNAL bisector from B of triangle a */
extern Line2D bisectorB(Triangle2D* a);

/* function "bisectorC(a)" returns Line2D type object - INTERNAL bisector from C of triangle a */
extern Line2D bisectorC(Triangle2D* a);

/* function "heigthA(a)" returns Line2D type object - heigth from A of triangle a */
extern Line2D heigthA(Triangle2D* a);

/* function "heigthB(a)" returns Line2D type object - heigth from B of triangle a */
extern Line2D heigthB(Triangle2D* a);

/* function "heigthC(a)" returns Line2D type object - heigth from C of triangle a */
extern Line2D heigthC(Triangle2D* a);

/* function "centroid(a)" returns Point2D type object - the point of medians' intersection in triangle a */
extern Point2D centroid(Triangle2D* a);

#endif /* GEOMETRY2D_H end */
