#include <stdio.h>
#include <math.h>
#include "../headers/Geometry2D.h"  /* it connects to this file if only it in the current folder*/
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

  // printf("k1 = %f, k2 = %f\n", k1, k2);

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
  new.c = a->x * b->y - a->y + b->x;
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
  return line_through_two_points(p_inc, &a->a);     /* every bisector is passing through the verticle of triangle and the incenter */
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
  Point2D vect_b, vect_c;       /* cosine we can find from the scalar product and the length of the vector */
  vect_b.vector[0] = a->b.x;
  vect_b.vector[0] = a->b.y;
  vect_c.vector[0] = a->c.x;
  vect_c.vector[0] = a->c.y;
  Point2D *p_b = &vect_b, *p_c = &vect_c;
  Dtype cosine = mulS(p_b, p_c) / two_points_length(&a->b, &a->c);
  return acos(cosine);
}

Dtype angelB(Triangle2D* a){
  Point2D vect_a, vect_c;
  vect_a.vector[0] = a->a.x;
  vect_a.vector[0] = a->a.y;
  vect_c.vector[0] = a->c.x;
  vect_c.vector[0] = a->c.y;
  Point2D *p_a = &vect_a, *p_c = &vect_c;
  Dtype cosine = mulS(p_a, p_c) / two_points_length(&a->a, &a->c);
  return acos(cosine);
}

Dtype angelC(Triangle2D* a){
  Point2D vect_b, vect_a;
  vect_a.vector[0] = a->a.x;
  vect_a.vector[0] = a->a.y;
  vect_b.vector[0] = a->b.x;
  vect_b.vector[0] = a->b.y;
  Point2D *p_a = &vect_a, *p_b = &vect_b;
  Dtype cosine = mulS(p_b, p_a) / two_points_length(&a->a, &a->b);
  return acos(cosine);
}

Line2D heigthA(Triangle2D* a){                              /* if we have line Ax + By + C = 0, all lines -Bx + Ay + C1 = 0 will be            */
  Line2D bc = line_through_two_points(&a->b, &a->c), h_a;   /* perpendicular to this line, and in order to find C1, we can put our verticle    */
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
  // Triangle2D my_triangle = x->a;
  // Line2D my_line = x->l;
  Segment2D ab, ac, bc;
  // Line2D line_ab = line_through_two_points(&x->a.a, &x->a.b), line_bc = line_through_two_points(&x->a.c, &x->a.b), line_ac = line_through_two_points(&x->a.a, &x->a.c);
  // Line2D *p_line_ab = &line_ab, *p_line_ac = &line_ac, *p_line_bc = &line_bc;
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

  /* line L is passing through the verticle but is not passing through the opposite segment; 3 cases for each verticle */
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
    printf("BC and AC: xp = %f, yp = %f, xq = %f, yq = %f\n", p.x, p.y, q.x, q.y);
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
    printf("BC and AB: xp = %f, yp = %f, xq = %f, yq = %f\n", p.x, p.y, q.x, q.y);
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
    printf("AC and AB: xp = %f, yp = %f, xq = %f, yq = %f\n", p.x, p.y, q.x, q.y);
  }

  return *x;
}

int main(){
  
}
