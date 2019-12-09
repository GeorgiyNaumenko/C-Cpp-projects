#ifndef _GEOMETRY2D_C_
#define _GEOMETRY2D_C_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../headers/Geometry2D.h"
#include "../headers/common.h"


Point2D add(Point2D* a, Point2D* b){
  Point2D new;
  new.vector[0] = a->vector[0] + b->vector[0];
  new.vector[1] = a->vector[1] + b->vector[1];
  return new;
}

Dtype mulS(Point2D* a, Point2D* b){
  return a->vector[0] * b->vector[0] + a->vector[1] * b->vector[1];
}

Dtype mul(Point2D* a, Point2D* b){
  return a->vector[0] * b->vector[1] - a->vector[1] * b->vector[0];
}

Point2D homot(Point2D* a, Dtype lambda){
  Point2D new;
  new.vector[0] = a->vector[0]*lambda;
  new.vector[1] = a->vector[1]*lambda;
  return new;
}

Point2D intersection_s_s(Segment2D* a, Segment2D* b){
  /* it will be more comfortable to work with segments if I create new variables here */
  /* A(x1, y1), B(x2, y2), C(x3, y3), D(x4, y4), my segments: AB and CD */
  Dtype x1=a->a.x, x2=a->b.x, x3=b->a.x, x4=b->b.x, y1=a->a.y, y2=a->b.y, y3=b->a.y, y4=b->b.y;
  Dtype k1, k2, b1, b2, x, y;  /* I'm going to find canonical equations of lines passing through my segments */
  Itype flag = 1;  /* 0 if 0 point, 1 if 1 point, 2 if INF point */
  Point2D intersection;

  if(x1 >= x2){            /* for correct angular coefficients, we must have: x1 <= x2 and x3 <= x4 */
    x1 = x1 + x2;          /* let's name these two inequalities as (*) */
    x2 = x1 - x2;
    x1 = x1 - x2;
    y1 = y1 + y2;
    y2 = y1 - y2;
    y1 = y1 - y2;
  }

  if(x3 >= x4){
    x3 = x3 + x4;
    x4 = x3 - x4;
    x3 = x3 - x4;
    y3 = y3 + y4;
    y4 = y3 - y4;
    y3 = y3 - y4;
  }

  /* here we can find angular coefficient k1*/
  if(x1 == x2){
    k1 = 1.0;
  }
  else if(y1 == y2){
    k1 = 0.0;
  }
  else{
    k1 = (y2 - y1) / (x2 - x1);
  }

  b1 = y1 - k1*x1;     /* here we can find a free member*/

  /* and here k2 */
  if(x3 == x4){
    k2 = 1.0;
  }
  else if(y3 == y4){
    k2 = 0.0;
  }
  else{
    k2 = (y4 - y3) / (x4 - x3);
  }

  b2 = y3 - k2*x3;

  /* here we can check what if k1 == k2 */
  if(k1 == k2){
    if(b1 == b2){
      if(((x3 < x1) && (x1 < x4)) || ((x3 < x2) && (x2 < x4)) || ((x1 < x3) && (x3 < x2)) || ((x1 < x4) && (x4 < x2))){
        flag = 2;
      }
      else if((x1 == x4) || (x2 == x3)){
        flag = 1;
      }
      else{
        flag = 0;
      }
    }
    else{
      flag = 0;
    }
  }

  /* here we can find our intersection */
  if (flag == 1){
    x = (b2 - b1) / (k1 - k2);
    y = k1*x + b1;
    /* and finally we must check, if our intersection point lies on our segments */
    if( ((x1 <= x4) && (x4 <= x2)) && ((x1 <= x3) && (x3 <= x2))){  /* we remember (*) inequalities */
      intersection.x = x;
      intersection.y = y;
    }
    else{
      intersection.x = HUGE_VAL;    /* HUGE_VAL (or -HUGE_VAL) from <math.h> library it's a really huge value */
      intersection.y = -HUGE_VAL;   /*   which can't be represented in double, means plus (or minus) infinity */
    }
  }
  else if (flag == 0){
    intersection.x = HUGE_VAL;
    intersection.y = -HUGE_VAL;
  }
  else{
    intersection.x = HUGE_VAL;
    intersection.y = HUGE_VAL;
  }

  return intersection;
}

Point2D intersection_l_s(Line2D* a, Segment2D* b){
  /* with points b.a and b.b from segment all actions are similar to the previous function */
  Dtype x1 = b->a.x, x2 = b->b.x, y1 = b->a.y, y2 = b->b.y;
  Dtype k1, b1, x, y;
  Itype flag;
  Point2D intersection;

  if(x1 >= x2){
    x1 = x1 + x2;
    x2 = x1 - x2;
    x1 = x1 - x2;
    y1 = y1 + y2;
    y2 = y1 - y2;
    y1 = y1 - y2;
  }

  if(x1 == x2){
    k1 = 1.0;
  }
  else if(y1 == y2){
    k1 = 0.0;
  }
  else{
    k1 = (y2 - y1) / (x2 - x1);
  }

  b1 = y1 - k1*x1;

  if((-1.0)*a->a/a->b == k1){    /* a*x + b*y + c = 0, so y = -a/b*x - c/b */
    if (b1 = (-1.0)*a->c/a->b){
      flag = 2;       /* we will have that our segment lies on our line */
    }
    else{           /* we will have that our segment is parallel to our line */
      flag = 0;
    }
  }
  else{
    /* y = k1*x + b1 and a*x + b*y + c = 0, so x = -(c + b1*b) / (a + b*k1) */
    x = (-1.0)*(a->c + b1*a->b) / (a->a + a->b*k1);
    y = k1*x + b1;
    /* (x, y) may be the point of intersection, but now we must check if it lies on our segment */

    if((x1 <= x) && (x <= x2)){
      flag = 1;
    }
    else{
      flag = 0;
    }
  }

  /* depending on the value of flag we can create our point of intersection */
  if(flag == 1){
    intersection.x = x;
    intersection.y = y;
  }
  else if (flag == 0){
    intersection.x = HUGE_VAL;
    intersection.y = -HUGE_VAL;
  }
  else{
    intersection.x = HUGE_VAL;
    intersection.y = HUGE_VAL;
  }

  return intersection;
}

Point2D intersection_l_l(Line2D* a, Line2D* b){
  Dtype k1, k2, b1, b2, x, y;     /* I'm going to represent equations of lines a and b in canonical form */
  Itype flag;
  Point2D intersection;

  k1 = (-1.0)*a->a/a->b;
  b1 = (-1.0)*a->c/a->b;
  k2 = (-1.0)*b->a/b->b;
  b2 = (-1.0)*b->c/b->b;

  if (k1 == k2){
    if (b1 == b2){
      flag = 2;    /* line a coincides with line b */
    }
    else{
      flag = 0;    /* lines are parallel */
    }
  }
  else{
    flag = 1;     /* lines will always have the point of intersection in this case so here we can find it */
    x = (b2 - b1) / (k1 - k2);
    y = k1*x + b1;
  }

  if(flag == 1){
    intersection.x = x;
    intersection.y = y;
  }
  else if (flag == 0){
    intersection.x = HUGE_VAL;
    intersection.y = -HUGE_VAL;
  }
  else{
    intersection.x = HUGE_VAL;
    intersection.y = HUGE_VAL;
  }

  return intersection;
}

Dtype two_points_length(Point2D* a, Point2D* b){
  return sqrt((b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y));
}

Dtype segment_length(Segment2D* a){
  return two_points_length(&a->a, &a->b);
}

Line2D line_through_two_points(Point2D* a, Point2D* b){
  Line2D new;
  new.a = a->y - b->y;
  new.b = b->x - a->x;
  new.c = a->x * b->y - a->y * b->x;
  return new;
}


Dtype perimeter(Triangle2D* a){
  return two_points_length(&a->a, &a->b) + two_points_length(&a->c, &a->b) + two_points_length(&a->a, &a->c);
}

Dtype area(Triangle2D* a){
  Dtype p = perimeter(a)/2.0, ab = two_points_length(&a->a, &a->b), bc = two_points_length(&a->c, &a->b), ac = two_points_length(&a->a, &a->c);
  return sqrt(p*(p-ab)*(p-bc)*(p-ac));
}

Point2D center(Triangle2D* a){
  Line2D mid_per_AC, mid_per_AB;
  Point2D M_ac, M_ab, center;
  Dtype k1, k2, k3, k4, b1, b2;
  M_ac.x = (a->a.x + a->c.x) / 2.0;  /* midpoints of AC and AB */
  M_ab.x = (a->a.x + a->b.x) / 2.0;
  M_ac.y = (a->a.y + a->c.y) / 2.0;
  M_ab.y = (a->a.y + a->b.y) / 2.0;
  k1 = (a->b.y - a->a.y) / (a->b.x- a->a.x);  /* angular coefficients of AB and AC*/
  k2 = (a->c.y - a->a.y) / (a->c.x- a->a.x);
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
  center = intersection_l_l(&mid_per_AB, &mid_per_AC);
  return center;
}

Dtype described_radius(Triangle2D* a){
  Point2D cent = center(a);
  return two_points_length(&a->a, &cent);
}

Line2D medianA(Triangle2D* a){
  Point2D M_bc;                    /* midpoint of BC */
  Point2D *pointer = &M_bc;
  M_bc.x = (a->b.x + a->c.x) / 2.0;
  M_bc.y = (a->b.y + a->c.y) / 2.0;
  return line_through_two_points(&a->a, pointer);
}

Line2D medianB(Triangle2D* a){
  Point2D M_ac;                    /* midpoint of AC */
  Point2D *pointer = &M_ac;
  M_ac.x = (a->a.x + a->c.x) / 2.0;
  M_ac.y = (a->a.y + a->c.y) / 2.0;
  return line_through_two_points(&a->b, pointer);
}

Line2D medianC(Triangle2D* a){
  Point2D M_ab;                    /* midpoint of AB */
  Point2D *pointer = &M_ab;
  M_ab.x = (a->b.x + a->a.x) / 2.0;
  M_ab.y = (a->b.y + a->a.y) / 2.0;
  return line_through_two_points(&a->c, pointer);
}

Point2D centroid(Triangle2D* a){
  Line2D med_a = medianA(a), med_b = medianB(a);
  Line2D *p1 = &med_a, *p2 = &med_b;
  return intersection_l_l(p1, p2);
}

Point2D incenter(Triangle2D* a){
  Point2D Ta, Tb, Tc, cent;         /* Ta, Tb and Tc - tangent points of inscrible in triangle circle with segments BC, AC and AB respectively */
  Triangle2D t;
  Triangle2D *p_t = &t;
  Dtype ab, ac, bc, p, lambda_ab, lambda_ac, lambda_bc;
  Dtype x1 = a->a.x, x2 = a->b.x, x3 = a->c.x, y1 = a->a.y, y2 = a->b.y, y3 = a->c.y;
  p = perimeter(a) / 2.0;
  ab = two_points_length(&a->a, &a->b);
  bc = two_points_length(&a->b, &a->c);
  ac = two_points_length(&a->a, &a->c);
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
  cent = center(p_t);                       /* The main idea is that inscribed in ABC sircle is described around TaTbTc circle */
  return cent;
}

Dtype inscribed_radius(Triangle2D* a){
  return 2.0 * area(a) / perimeter(a);       /* r = S/p because S = pr */
}

Line2D bisectorA(Triangle2D* a){
  Point2D inc = incenter(a);
  Point2D *p_inc = &inc;
  return line_through_two_points(p_inc, &a->a);     /* every bisector is passing through the vertex of triangle and the incenter */
}

Line2D bisectorB(Triangle2D* a){
  Point2D inc = incenter(a);
  Point2D *p_inc = &inc;
  return line_through_two_points(p_inc, &a->b);
}

Line2D bisectorC(Triangle2D* a){
  Point2D inc = incenter(a);
  Point2D *p_inc = &inc;
  return line_through_two_points(p_inc, &a->c);
}

Dtype angelA(Triangle2D* a){
  Point2D vect_a, vect_b, vect_c;       /* cosine we can find from the scalar product and the length of the vector */
  vect_a.vector[0] = a->a.x;
  vect_a.vector[1] = a->a.y;
  vect_b.vector[0] = a->b.x;
  vect_b.vector[1] = a->b.y;
  vect_c.vector[0] = a->c.x;
  vect_c.vector[1] = a->c.y;
  Point2D ab_v, ac_v;
  Point2D min_a = homot(&vect_a, -1.0);
  Point2D *aa = &min_a;
  ab_v = add(&vect_b, aa);
  ac_v = add(&vect_c, aa);
  Dtype cosine = mulS(&ab_v, &ac_v) / (two_points_length(&a->a, &a->c) * two_points_length(&a->a, &a->b));
  return acos(cosine);
}

Dtype angelB(Triangle2D* a){
  Point2D vect_a, vect_b, vect_c;
  vect_a.vector[0] = a->a.x;
  vect_a.vector[1] = a->a.y;
  vect_b.vector[0] = a->b.x;
  vect_b.vector[1] = a->b.y;
  vect_c.vector[0] = a->c.x;
  vect_c.vector[1] = a->c.y;
  Point2D ba_v, bc_v;
  Point2D min_b = homot(&vect_b, -1.0);
  Point2D *bb = &min_b;
  ba_v = add(&vect_a, bb);
  bc_v = add(&vect_c, bb);
  Dtype cosine = mulS(&ba_v, &bc_v) / (two_points_length(&a->a, &a->b) * two_points_length(&a->c, &a->b));
  return acos(cosine);
}

Dtype angelC(Triangle2D* a){
  Point2D vect_a, vect_b, vect_c;
  vect_a.vector[0] = a->a.x;
  vect_a.vector[1] = a->a.y;
  vect_b.vector[0] = a->b.x;
  vect_b.vector[1] = a->b.y;
  vect_c.vector[0] = a->c.x;
  vect_c.vector[1] = a->c.y;
  Point2D ca_v, cb_v;
  Point2D min_c = homot(&vect_c, -1.0);
  Point2D *cc = &min_c;
  ca_v = add(&vect_a, cc);
  cb_v = add(&vect_b, cc);
  Dtype cosine = mulS(&ca_v, &cb_v) / (two_points_length(&a->a, &a->c) * two_points_length(&a->c, &a->b));
  return acos(cosine);
}

Line2D heigthA(Triangle2D* a){                              /* if we have line Ax + By + C = 0, all lines -Bx + Ay + C1 = 0 will be            */
  Line2D bc = line_through_two_points(&a->b, &a->c), h_a;   /* perpendicular to this line, and in order to find C1, we can put our vertex      */
  Dtype c1 = bc.b * a->a.x - bc.a * a->a.y;                 /* A(x0, y0) in the equation: C1 = Bx0 - Ay0                                       */
  h_a.a = (-1.0) * bc.b;
  h_a.b = bc.a;
  h_a.c = c1;
  return h_a;
}

Line2D heigthB(Triangle2D* a){
  Line2D ac = line_through_two_points(&a->a, &a->c), h_b;
  Dtype c1 = ac.b * a->b.x - ac.a * a->b.y;
  h_b.a = (-1.0) * ac.b;
  h_b.b = ac.a;
  h_b.c = c1;
  return h_b;
}

Line2D heigthC(Triangle2D* a){
  Line2D ab = line_through_two_points(&a->a, &a->b), h_c;
  Dtype c1 = ab.b * a->c.x - ab.a * a->c.y;
  h_c.a = (-1.0) * ab.b;
  h_c.b = ab.a;
  h_c.c = c1;
  return h_c;
}

Geometry2D find_two_areas(Geometry2D* x){
  Segment2D ab, ac, bc;
  Segment2D *p_ab = &ab, *p_ac = &ac, *p_bc = &bc;
  ab.a = x->a.a;
  ab.b = x->a.b;
  ac.a = x->a.a;
  ac.b = x->a.c;
  bc.a = x->a.c;
  bc.b = x->a.b;

  /* One of the segments AC, AB or BC lies on the line L */
  if(((intersection_l_s(&x->l, p_ab).x == HUGE_VAL) && (intersection_l_s(&x->l, p_ab).y == HUGE_VAL)) || ((intersection_l_s(&x->l, p_ac).x == HUGE_VAL) && (intersection_l_s(&x->l, p_ac).y == HUGE_VAL)) || ((intersection_l_s(&x->l, p_bc).x == HUGE_VAL) && (intersection_l_s(&x->l, p_bc).y == HUGE_VAL))){
    x->s2 = 0.0;
    x->s1 = area(&x->a);
  }

  /* line L is passing through the vertex but is not passing through the opposite segment; 3 cases for each vertex */
  else if((x->l.a * x->a.a.x + x->l.b * x->a.a.y + x->l.c == 0) && ((intersection_l_s(&x->l, p_bc).x == HUGE_VAL) && (intersection_l_s(&x->l, p_bc).y == -HUGE_VAL))){
    x->s2 = 0.0;
    x->s1 = area(&x->a);
  }
  else if((x->l.a * x->a.b.x + x->l.b * x->a.b.y + x->l.c == 0) && ((intersection_l_s(&x->l, p_ac).x == HUGE_VAL) && (intersection_l_s(&x->l, p_ac).y == -HUGE_VAL))){
    x->s2 = 0.0;
    x->s1 = area(&x->a);
  }
  else if((x->l.a * x->a.c.x + x->l.b * x->a.c.y + x->l.c == 0) && ((intersection_l_s(&x->l, p_ab).x == HUGE_VAL) && (intersection_l_s(&x->l, p_ab).y == -HUGE_VAL))){
    x->s2 = 0.0;
    x->s1 = area(&x->a);
  }

  /* the case when our line L even don't touch our triangle*/
  else if(((intersection_l_s(&x->l, p_bc).x == HUGE_VAL) && (intersection_l_s(&x->l, p_bc).y == -HUGE_VAL)) && ((intersection_l_s(&x->l, p_ac).x == HUGE_VAL) && (intersection_l_s(&x->l, p_ac).y == -HUGE_VAL)) && ((intersection_l_s(&x->l, p_ab).x == HUGE_VAL) && (intersection_l_s(&x->l, p_ab).y == -HUGE_VAL))){
    x->s2 = 0.0;
    x->s1 = area(&x->a);
  }

  /* all cases when one of areas will be zero have been shown yet, so now at least 2 sides of triangle will have a real intersection point with line L */
  /* no metter how many segments line L will intersect because all that we will do it's look for a triangle */
  /* that's because one of our figures MUST be triangle and we can calculate it's area: we have a function for that! */
  /* the area of second figure we can find easily: we just need to substract area of first figure from area of ABC */
  /* so now let's do it */

  /* the case when our line L intersects BC and AC. In this case we chould find those intersection points P and Q and calculate area of triangle PQC */
  else if((intersection_l_s(&x->l, p_bc).x != HUGE_VAL) && (intersection_l_s(&x->l, p_ac).x != HUGE_VAL)){
    Point2D p, q;
    Triangle2D cpq;
    Triangle2D *p_cpq  = &cpq;
    p = intersection_l_s(&x->l, p_bc);
    q = intersection_l_s(&x->l, p_ac);
    p_cpq->a = x->a.c;
    p_cpq->b = p;
    p_cpq->c = q;
    x->s1 = area(p_cpq);
    x->s2 = area(&x->a) - x->s1;
  }

  /* the case when our line L intersects BC and AB. In this case we chould find those intersection points P and Q and calculate area of triangle PQB */
  else if((intersection_l_s(&x->l, p_bc).x != HUGE_VAL) && (intersection_l_s(&x->l, p_ab).x != HUGE_VAL)){
    Point2D p, q;
    Triangle2D bpq;
    Triangle2D *p_bpq  = &bpq;
    p = intersection_l_s(&x->l, p_bc);
    q = intersection_l_s(&x->l, p_ab);
    p_bpq->a = x->a.b;
    p_bpq->b = p;
    p_bpq->c = q;
    x->s1 = area(p_bpq);
    x->s2 = area(&x->a) - x->s1;
  }

  /* the case when our line L intersects AC and AB. In this case we chould find those intersection points P and Q and calculate area of triangle PQA */
  else if((intersection_l_s(&x->l, p_ac).x != HUGE_VAL) && (intersection_l_s(&x->l, p_ab).x != HUGE_VAL)){
    Point2D p, q;
    Triangle2D apq;
    Triangle2D *p_apq  = &apq;
    p = intersection_l_s(&x->l, p_ac);
    q = intersection_l_s(&x->l, p_ab);
    p_apq->a = x->a.a;
    p_apq->b = p;
    p_apq->c = q;
    x->s1 = area(p_apq);
    x->s2 = area(&x->a) - x->s1;
  }

  return *x;
}

void console_show_line(Line2D* line){
  if(line->a > 0){
    printf("%fx ", line->a);
  }
  else if(line->a < 0){
    printf("-%fx ", (-1.0)*line->a);
  }
  if(line->b > 0){
    printf("+ %fy ", line->b);
  }
  else if(line->b < 0){
    printf("- %fy ", (-1.0)*line->b);
  }
  if(line->c > 0){
    printf("+ %f", line->c);
  }
  else if(line->c < 0){
    printf("- %f", (-1.0)*line->c);
  }
  printf(" = 0\n");
}

void textfile_show_line(Line2D* line, FILE *f) {
  if(line->a > 0){
    fprintf(f, "%fx ", line->a);
  }
  else if(line->a < 0){
    fprintf(f, "-%fx ", (-1.0)*line->a);
  }
  if(line->b > 0){
    fprintf(f, "+ %fy ", line->b);
  }
  else if(line->b < 0){
    fprintf(f, "- %fy ", (-1.0)*line->b);
  }
  if(line->c > 0){
    fprintf(f, "+ %f", line->c);
  }
  else if(line->c < 0){
    fprintf(f, "- %f", (-1.0)*line->c);
  }
  fprintf(f, " = 0\n");
}

Itype inputGeometry2D(Geometry2D* x){
  printf("Input the Dtype (double) type coordinate 'x' of vertex A and press 'Enter':\n");
  scanf("%lf", &x->a.a.x);
  printf("Input the Dtype (double) type coordinate 'y' of vertex A and press 'Enter':\n");
  scanf("%lf", &x->a.a.y);
  printf("Input the Dtype (double) type coordinate 'x' of vertex B and press 'Enter':\n");
  scanf("%lf", &x->a.b.x);
  printf("Input the Dtype (double) type coordinate 'y' of vertex B and press 'Enter':\n");
  scanf("%lf", &x->a.b.y);
  printf("Input the Dtype (double) type coordinate 'x' of vertex C and press 'Enter':\n");
  scanf("%lf", &x->a.c.x);
  printf("Input the Dtype (double) type coordinate 'y' of vertex C and press 'Enter':\n");
  scanf("%lf", &x->a.c.y);
  printf("Input the Dtype (double) type coefficient 'a' of line L and press 'Enter':\n");
  scanf("%lf", &x->l.a);
  printf("Input the Dtype (double) type coefficient 'b' of line L and press 'Enter':\n");
  scanf("%lf", &x->l.b);
  printf("Input the Dtype (double) type coefficient 'c' of line L and press 'Enter':\n");
  scanf("%lf", &x->l.c);
  return 0;
}

void outputGeometry2D(Geometry2D x){
  Geometry2D calculated = find_two_areas(&x);
  Point2D vector_A, vector_B, vector_C;
  vector_A.vector[0] = x.a.a.x;
  vector_B.vector[0] = x.a.b.x;
  vector_C.vector[0] = x.a.c.x;
  vector_A.vector[1] = x.a.a.y;
  vector_B.vector[1] = x.a.b.y;
  vector_C.vector[1] = x.a.c.y;
  printf("Let OA->, OB->, OC-> be a radius-vectors of points A, B, C.\n");
  printf("Scalar products:\n");
  printf("(OA->, OB->) = %f, (OA->, OC->) = %f, (OB->, OC->) = %f\n", mulS(&vector_A, &vector_B), mulS(&vector_A, &vector_C), mulS(&vector_B, &vector_C));
  printf("Vector products:\n");
  printf("[OA-> x OB->] = (0, 0, %f), [OB-> x OA->] = (0, 0, %f)\n", mul(&vector_A, &vector_B), mul(&vector_B, &vector_A));
  printf("[OA-> x OC->] = (0, 0, %f), [OC-> x OA->] = (0, 0, %f)\n", mul(&vector_A, &vector_C), mul(&vector_C, &vector_A));
  printf("[OB-> x OC->] = (0, 0, %f), [OC-> x OB->] = (0, 0, %f)\n", mul(&vector_B, &vector_C), mul(&vector_C, &vector_B));
  printf("Sums of radius-vectors:\n");
  printf("OA-> + OB-> = (%f, %f)\n", add(&vector_A, &vector_B).x, add(&vector_A, &vector_B).y);
  printf("OA-> + OC-> = (%f, %f)\n", add(&vector_A, &vector_C).x, add(&vector_A, &vector_C).y);
  printf("OC-> + OB-> = (%f, %f)\n", add(&vector_C, &vector_B).x, add(&vector_C, &vector_B).y);
  printf("Lengthes of ABC sides:\n");
  printf("AB = %f\n", two_points_length(&x.a.a, &x.a.b));
  printf("AC = %f\n", two_points_length(&x.a.a, &x.a.c));
  printf("CB = %f\n", two_points_length(&x.a.c, &x.a.b));
  printf("Some special points and values in ABC:\n");
  printf("Perimeter of ABC: %f\n", perimeter(&x.a));
  printf("Area of ABC: %f\n", area(&x.a));
  printf("Incenter: (%f, %f)\n", incenter(&x.a).x, incenter(&x.a).y);
  printf("Radius of inscribed circle = %f\n", inscribed_radius(&x.a));
  printf("Center: (%f, %f)\n", center(&x.a).x, center(&x.a).y);
  printf("Radius of described circle = %f\n", described_radius(&x.a));
  printf("Centroid: (%f, %f)\n", centroid(&x.a).x, centroid(&x.a).y);
  printf("Angles in radians:\n");
  printf("<A = %f radians\n", angelA(&x.a));
  printf("<B = %f radians\n", angelB(&x.a));
  printf("<C = %f radians\n", angelC(&x.a));
  printf("And as summ you get:\n");
  printf("pi = %f\n", angelA(&x.a) + angelB(&x.a) + angelC(&x.a));
  printf("Equalities of some special lines in ABC:\n");
  printf("Median from vertex A: ");
  Line2D meda = medianA(&x.a);
  console_show_line(&meda);
  printf("Median from vertex B: ");
  Line2D medb = medianB(&x.a);
  console_show_line(&medb);
  printf("Median from vertex C: ");
  Line2D medc = medianC(&x.a);
  console_show_line(&medc);
  printf("Heigth from vertex A: ");
  Line2D ha = heigthA(&x.a);
  console_show_line(&ha);
  printf("Heigth from vertex B: ");
  Line2D hb = heigthB(&x.a);
  console_show_line(&hb);
  printf("Heigth from vertex C: ");
  Line2D hc = heigthC(&x.a);
  console_show_line(&hc);
  printf("Bisector from vertex A: ");
  Line2D bisa = bisectorA(&x.a);
  console_show_line(&bisa);
  printf("Bisector from vertex B: ");
  Line2D bisb = bisectorB(&x.a);
  console_show_line(&bisb);
  printf("Bisector from vertex C: ");
  Line2D bisc = bisectorC(&x.a);
  console_show_line(&bisc);
  printf("And the answer to the main qastion:\n");
  if (calculated.s2 == 0.0){
    printf("\nTriangle ABC wasn't divided by line L into 2 figures.\n");
  }
  else{
    printf("\nTriangle ABC was divided by line L into two figures with areas %f and %f\n", calculated.s1, calculated.s2);
  }
}

Itype inputBinaryFile(char* filename, Geometry2D* x){
  FILE *f;
  f = fopen(filename, "rb");
  fread(&x->a.a.x, sizeof(Dtype), 1, f);
  fread(&x->a.a.y, sizeof(Dtype), 1, f);
  fread(&x->a.b.x, sizeof(Dtype), 1, f);
  fread(&x->a.b.y, sizeof(Dtype), 1, f);
  fread(&x->a.c.x, sizeof(Dtype), 1, f);
  fread(&x->a.c.y, sizeof(Dtype), 1, f);
  fread(&x->l.a, sizeof(Dtype), 1, f);
  fread(&x->l.b, sizeof(Dtype), 1, f);
  fread(&x->l.c, sizeof(Dtype), 1, f);
  fclose(f);
  return 0;
}

Itype outputBinaryFile(char* filename, Geometry2D x){

  Point2D vector_A, vector_B, vector_C;
  vector_A.vector[0] = x.a.a.x;
  vector_B.vector[0] = x.a.b.x;
  vector_C.vector[0] = x.a.c.x;
  vector_A.vector[1] = x.a.a.y;
  vector_B.vector[1] = x.a.b.y;
  vector_C.vector[1] = x.a.c.y;

  FILE *f;
  f = fopen(filename, "wb");

  Dtype mulSAB = mulS(&vector_A, &vector_B), mulSAC = mulS(&vector_A, &vector_C), mulSBC = mulS(&vector_B, &vector_C);
  fwrite(&mulSAB, sizeof(Dtype), 1, f);
  fwrite(&mulSAC, sizeof(Dtype), 1, f);
  fwrite(&mulSBC, sizeof(Dtype), 1, f);

  Dtype mAB = mul(&vector_A, &vector_B), mBA = mul(&vector_B, &vector_A);
  Dtype mAC = mul(&vector_A, &vector_C), mCA = mul(&vector_B, &vector_A);
  Dtype mBC = mul(&vector_B, &vector_C), mCB = mul(&vector_C, &vector_B);
  fwrite(&mAB, sizeof(Dtype), 1, f);
  fwrite(&mBA, sizeof(Dtype), 1, f);
  fwrite(&mAC, sizeof(Dtype), 1, f);
  fwrite(&mCA, sizeof(Dtype), 1, f);
  fwrite(&mBC, sizeof(Dtype), 1, f);
  fwrite(&mCB, sizeof(Dtype), 1, f);

  Point2D sumAB = add(&vector_A, &vector_B), sumAC = add(&vector_A, &vector_C), sumBC = add(&vector_C, &vector_B);
  fwrite(&sumAB, sizeof(Point2D), 1, f);
  fwrite(&sumAC, sizeof(Point2D), 1, f);
  fwrite(&sumBC, sizeof(Point2D), 1, f);

  Dtype lAB = two_points_length(&x.a.a, &x.a.b), lAC = two_points_length(&x.a.a, &x.a.c), lCB = two_points_length(&x.a.c, &x.a.b);
  fwrite(&lAB, sizeof(Dtype), 1, f);
  fwrite(&lAC, sizeof(Dtype), 1, f);
  fwrite(&lCB, sizeof(Dtype), 1, f);

  Dtype per = perimeter(&x.a), ar = area(&x.a), i_r = inscribed_radius(&x.a), d_r = described_radius(&x.a);
  Point2D inc = incenter(&x.a), cen = center(&x.a), ceid = centroid(&x.a);
  fwrite(&per, sizeof(Dtype), 1, f);
  fwrite(&ar, sizeof(Dtype), 1, f);
  fwrite(&inc, sizeof(Point2D), 1, f);
  fwrite(&i_r, sizeof(Dtype), 1, f);
  fwrite(&cen, sizeof(Point2D), 1, f);
  fwrite(&d_r, sizeof(Dtype), 1, f);
  fwrite(&ceid, sizeof(Point2D), 1, f);

  Dtype a_an = angelA(&x.a), b_an = angelB(&x.a), c_an = angelC(&x.a);
  fwrite(&a_an, sizeof(Dtype), 1, f);
  fwrite(&b_an, sizeof(Dtype), 1, f);
  fwrite(&c_an, sizeof(Dtype), 1, f);

  Line2D meda = medianA(&x.a);
  Line2D medb = medianB(&x.a);
  Line2D medc = medianC(&x.a);
  Line2D ha = heigthA(&x.a);
  Line2D hb = heigthB(&x.a);
  Line2D hc = heigthC(&x.a);
  Line2D bisa = bisectorA(&x.a);
  Line2D bisb = bisectorB(&x.a);
  Line2D bisc = bisectorC(&x.a);
  fwrite(&meda, sizeof(Line2D), 1, f);
  fwrite(&medb, sizeof(Line2D), 1, f);
  fwrite(&medc, sizeof(Line2D), 1, f);
  fwrite(&ha, sizeof(Line2D), 1, f);
  fwrite(&hb, sizeof(Line2D), 1, f);
  fwrite(&hc, sizeof(Line2D), 1, f);
  fwrite(&bisa, sizeof(Line2D), 1, f);
  fwrite(&bisb, sizeof(Line2D), 1, f);
  fwrite(&bisc, sizeof(Line2D), 1, f);

  Geometry2D calculated = find_two_areas(&x);
  fwrite(&calculated.s1, sizeof(Dtype), 1, f);
  fwrite(&calculated.s2, sizeof(Dtype), 1, f);

  fclose(f);
  return 0;
}

Itype inputTextFile(char* filename, Geometry2D* x){
  FILE *f;
  f = fopen(filename, "r");
  fscanf(f, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &x->a.a.x, &x->a.a.y, &x->a.b.x, &x->a.b.y, &x->a.c.x, &x->a.c.y, &x->l.a, &x->l.b, &x->l.c);
  fclose(f);
  return 0;
}

Itype outputTextFile(char* filename, Geometry2D x){
  FILE *f;
  Geometry2D calculated = find_two_areas(&x);
  f = fopen(filename, "w");
  Point2D vector_A, vector_B, vector_C;
  vector_A.vector[0] = x.a.a.x;
  vector_B.vector[0] = x.a.b.x;
  vector_C.vector[0] = x.a.c.x;
  vector_A.vector[1] = x.a.a.y;
  vector_B.vector[1] = x.a.b.y;
  vector_C.vector[1] = x.a.c.y;
  fprintf(f, "Let OA->, OB->, OC-> be a radius-vectors of points A, B, C.\n");
  fprintf(f, "Scalar products:\n\n");
  fprintf(f, "(OA->, OB->) = %f, (OA->, OC->) = %f, (OB->, OC->) = %f\n\n", mulS(&vector_A, &vector_B), mulS(&vector_A, &vector_C), mulS(&vector_B, &vector_C));
  fprintf(f, "Vector products:\n\n");
  fprintf(f, "[OA-> x OB->] = (0, 0, %f), [OB-> x OA->] = (0, 0, %f)\n", mul(&vector_A, &vector_B), mul(&vector_B, &vector_A));
  fprintf(f, "[OA-> x OC->] = (0, 0, %f), [OC-> x OA->] = (0, 0, %f)\n", mul(&vector_A, &vector_C), mul(&vector_C, &vector_A));
  fprintf(f, "[OB-> x OC->] = (0, 0, %f), [OC-> x OB->] = (0, 0, %f)\n\n", mul(&vector_B, &vector_C), mul(&vector_C, &vector_B));
  fprintf(f, "Sums of radius-vectors\n\n");
  fprintf(f, "OA-> + OB-> = (%f, %f)\n", add(&vector_A, &vector_B).x, add(&vector_A, &vector_B).y);
  fprintf(f, "OA-> + OC-> = (%f, %f)\n", add(&vector_A, &vector_C).x, add(&vector_A, &vector_C).y);
  fprintf(f, "OC-> + OB-> = (%f, %f)\n\n", add(&vector_C, &vector_B).x, add(&vector_C, &vector_B).y);
  fprintf(f, "Lengthes of ABC sides:\n\n");
  fprintf(f, "AB = %f\n", two_points_length(&x.a.a, &x.a.b));
  fprintf(f, "AC = %f\n", two_points_length(&x.a.a, &x.a.c));
  fprintf(f, "CB = %f\n\n", two_points_length(&x.a.c, &x.a.b));
  fprintf(f, "Some special points and values in ABC:\n\n");
  fprintf(f, "Perimeter of ABC: %f\n", perimeter(&x.a));
  fprintf(f, "Area of ABC: %f\n", area(&x.a));
  fprintf(f, "Incenter: (%f, %f)\n", incenter(&x.a).x, incenter(&x.a).y);
  fprintf(f, "Radius of inscribed circle = %f\n", inscribed_radius(&x.a));
  fprintf(f, "Center: (%f, %f)\n", center(&x.a).x, center(&x.a).y);
  fprintf(f, "Radius of described circle = %f\n", described_radius(&x.a));
  fprintf(f, "Centroid: (%f, %f)\n\n", centroid(&x.a).x, centroid(&x.a).y);
  fprintf(f, "Angles in radians:\n\n");
  fprintf(f, "<A = %f radians\n", angelA(&x.a));
  fprintf(f, "<B = %f radians\n", angelB(&x.a));
  fprintf(f, "<C = %f radians\n", angelC(&x.a));
  fprintf(f, "And as summ you get:\n");
  fprintf(f, "pi = %f\n\n", angelA(&x.a) + angelB(&x.a) + angelC(&x.a));
  fprintf(f, "Equalities of some special lines in ABC:\n\n");
  fprintf(f, "Median from vertex A: ");
  Line2D meda = medianA(&x.a);
  textfile_show_line(&meda, f);
  fprintf(f, "Median from vertex B: ");
  Line2D medb = medianB(&x.a);
  textfile_show_line(&medb, f);
  fprintf(f, "Median from vertex C: ");
  Line2D medc = medianC(&x.a);
  textfile_show_line(&medc, f);
  fprintf(f, "\nHeigth from vertex A: ");
  Line2D ha = heigthA(&x.a);
  textfile_show_line(&ha, f);
  fprintf(f, "Heigth from vertex B: ");
  Line2D hb = heigthB(&x.a);
  textfile_show_line(&hb, f);
  fprintf(f, "Heigth from vertex C: ");
  Line2D hc = heigthC(&x.a);
  textfile_show_line(&hc, f);
  fprintf(f, "\nBisector from vertex A: ");
  Line2D bisa = bisectorA(&x.a);
  textfile_show_line(&bisa, f);
  fprintf(f, "Bisector from vertex B: ");
  Line2D bisb = bisectorB(&x.a);
  textfile_show_line(&bisb, f);
  fprintf(f, "Bisector from vertex C: ");
  Line2D bisc = bisectorC(&x.a);
  textfile_show_line(&bisc, f);
  fprintf(f, "\nAnd the answer to the main qastion:\n");
  if (calculated.s2 == 0.0){
    fprintf(f, "\nTriangle ABC wasn't divided by line L into 2 figures.\n");
  }
  else{
    fprintf(f, "\nTriangle ABC was divided by line L into two figures with areas %f and %f\n", calculated.s1, calculated.s2);
  }
  fclose(f);
  return 0;
}

#endif /* end of _GEOMETRY2D_C_ */
