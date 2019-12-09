#ifndef _COMMON_H_
#define _COMMON_H_

/* Declaration of all types */

typedef double Dtype; /* double real type for application */

typedef int Itype; /* integer type for application */

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

#endif /* _COMMON_H_ end */
