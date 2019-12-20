#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Polynom{
public:
  int mod;                                        /* define the field Zmod[x] */
  vector<int> coefficients;                       /* coefficients of the polynom */
  int deg;                                        /* degree of the polynom */
  Polynom();                                      /* constructor */
  void input();                                   /* input from the keyboard */
  void output();                                  /* output in console */
  void output_in_txt(const char* filename);       /* output in text file */
  float value(float x);                           /* value of polynom in point x */
  Polynom operator + (const Polynom & other);     /* sum of two polynoms */
  Polynom operator - (const Polynom & other);     /* difference of two polynoms */
  Polynom operator * (const Polynom & other);     /* product of two polynoms */
  Polynom operator % (const Polynom & other);     /* remainder of dividing our polynom by another one */
  int resultant(Polynom other);                   /* resultant of polynom */
  int discriminant();                             /* discriminant of polynom */
  bool has_multiple_root();                       /* true if our polynom has multiple root */
  bool has_common_root(Polynom other);            /* true if our polynom has common root with another one */
  Polynom derivative();                           /* derivative of our polynom and another one */
  Polynom indefinite_integral();                  /* indefinite integral of or polynom*/
  float definite_integral(int a, int b);          /* the area under our polynom between a and b - just definite integral from a to b*/
};
