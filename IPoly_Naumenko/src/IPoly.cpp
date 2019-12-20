#pragma once
#include "IPoly.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;



int gcd(int a, int b){
  if (a % b == 0){
    return b;
  }
  else{
    if (a > b){
      return gcd(a % b, b);
    }
    else{
      return gcd(b % a, a);
    }
  }
}

vector< vector<int> > minor(vector< vector<int> > matrix, int n, int i, int j){
  int di, dj;
  vector< vector<int> > matr;

  for(int k = 0; k < n - 1; k++){
    matr.push_back(vector<int>());
    for(int j = 0; j < n - 1; j++){
      matr[k].push_back(0);
    }
  }

  di = 0;
  for (int ki = 0; ki < n - 1; ki++){
    if (ki == i){
      di = 1;
    }
    dj = 0;
    for (int kj = 0; kj < n - 1; kj++){
      if (kj == j){
        dj = 1;
      }
      matr[ki][kj] = matrix[ki + di][kj + dj];
    }
  }

  return matr;
}

int determinant(vector< vector<int> > matrix, int n){
  int j = 0, det = 0, k = 1;
  vector< vector<int> > next;

  // for(int i=0; i < n: i++){
  //   new.push_back(vector<int>());
  // }

  if (n == 1){
    return matrix[0][0];
  }
  if (n == 2){
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][1];
  }
  if (n > 2){
    for(int i=0; i < n; i++){
      next = minor(matrix, n, i, j);
      det = det + matrix[i][0] * determinant(next, n - 1);
    }
  }
  return det;
}



Polynom::Polynom(){

}

void Polynom::input(){
  int temp;
  cout << "Enter the degree:" << endl;
  cin >> deg;
  cout << "Enter the modulo" << endl;
  cin >> mod;
  if (mod == 0){
    for (int i = 0; i < deg + 1; i++){
      cout << "Enter the " << deg - i << " degree coefficient" << endl;
      cin >> temp;
      coefficients.push_back(temp);
    }
  }
  else{
    for (int i = 0; i < deg + 1; i++){
      cout << "Enter the " << deg - i << " degree coefficient" << endl;
      cin >> temp;
      coefficients.push_back(temp % mod);
    }
  }
}

void Polynom::output(){
  cout << "Polynom P(x) from Z" << mod << "[x] field:\t";
  cout << "P(x) = ";
  if (mod == 0){
    for (int i = 0; i < deg + 1; i++){
      if (i == 0){
        if (coefficients[i] != 1){
          cout << coefficients[i] << "x^" << deg - i;
        }
        else{
          cout << "x^" << deg - i;
        }
      }
      else if ( (i > 0) && (i != deg) && (i != deg - 1)){
        if (coefficients[i] != 0){
          if (coefficients[i] != 1){
            cout << " + " << coefficients[i] << "x^" << deg - i;
          }
          else{
            cout << " + " << "x^" << deg - i;
          }
        }
      }
      else if (i == deg - 1){
        if (coefficients[i] != 0){
          if (coefficients[i] != 1){
            cout << " + " << coefficients[i] << "x";
          }
          else{
            cout << " + " << "x";
          }
        }
      }
      else{
        if (coefficients[i] == 0){
          cout << endl;
        }
        else{
          cout << " + " << coefficients[i] << endl;
        }
      }
    }
  }
  else{
    for (int i = 0; i < deg + 1; i++){
      if (i == 0){
        if (coefficients[i] % mod != 1){
          cout << coefficients[i] % mod << "x^" << deg - i;
        }
        else{
          cout << "x^" << deg - i;
        }
      }
      else if ( (i > 0) && (i != deg) && (i != deg - 1)){
        if (coefficients[i] % mod != 0){
          if (coefficients[i] % mod != 1){
            cout << " + " << coefficients[i] % mod << "x^" << deg - i;
          }
          else{
            cout << " + " << "x^" << deg - i;
          }
        }
      }
      else if (i == deg - 1){
        if (coefficients[i] % mod != 0){
          if (coefficients[i] % mod != 1){
            cout << " + " << coefficients[i] % mod << "x";
          }
          else{
            cout << " + " << "x";
          }
        }
      }
      else{
        if (coefficients[i] % mod == 0){
          cout << endl;
        }
        else{
          cout << " + " << coefficients[i] % mod << endl;
        }
      }
    }
  }
}

float Polynom::value(float x){
  int val = 0;
  for (int i = 0; i < deg + 1; i++){
    val = val + ((pow(x, deg-i)*coefficients[i]));
  }
  return val;
}

Polynom Polynom::derivative(){
  Polynom der;
  der.deg = deg - 1;
  der.mod = mod;
  for (int i = 0; i < deg; i++){
    der.coefficients.push_back((coefficients[i]*(deg-i)) % mod);
  }
  return der;
}

Polynom Polynom::indefinite_integral(){
  Polynom indef_integ;
  bool integral_exists = true;
  for (int i = 0; i < deg + 1; i++){
    if (coefficients[deg - i] % gcd(mod, deg - i + 1) != 0){
      integral_exists = false;
      break;
    }
  }
  if (integral_exists){
    indef_integ.deg = deg + 1;
    indef_integ.mod = mod;
    int c;
    for(int i = 0; i < deg + 1; i++){
      c = coefficients[i];
      while(c % (deg - i + 1) != 0){
        c = c + mod;
      }
      indef_integ.coefficients.push_back(c/(deg - i + 1));
    }
    indef_integ.coefficients.push_back(0);
  }
  else{
    indef_integ.deg = 0;
    indef_integ.mod = 0;
    indef_integ.coefficients.push_back(0);
  }
  return indef_integ;
}

float Polynom::definite_integral(int a, int b){
  Polynom integ;
  integ = indefinite_integral();
  return integ.value(b) - integ.value(a);
}

Polynom Polynom::operator + (const Polynom & other){
  vector<int> poly1;
  vector<int> poly2;
  Polynom sum;
  sum.mod = this->mod;
  if (this->deg > other.deg){
    sum.deg = this->deg;
    poly1 = this->coefficients;
    poly2 = other.coefficients;
    for (int i = 0; i < other.deg + 1; i ++){
      poly1[this->deg - i] = poly1[this->deg - i] + poly2[other.deg - i];
    }
  }
  else{
    sum.deg = other.deg;
    poly2 = this->coefficients;
    poly1 = other.coefficients;
    for (int i = 0; i < this->deg + 1; i ++){
      poly1[other.deg - i] = poly1[other.deg - i] + poly2[this->deg - i];
    }
  }
  sum.coefficients = poly1;
  while(sum.coefficients[0] % sum.mod == 0){
    sum.coefficients.erase(sum.coefficients.begin());
    sum.deg--;
  }
  return sum;
}

Polynom Polynom::operator - (const Polynom & other){
  vector<int> poly1;
  vector<int> poly2;
  Polynom dif;
  int temp = 0;
  dif.mod = this->mod;
  if (this->deg > other.deg){
    dif.deg = this->deg;
    poly1 = this->coefficients;
    poly2 = other.coefficients;
    for (int i = 0; i < other.deg + 1; i ++){
      temp = poly1[this->deg - i] - poly2[other.deg - i];
      while (temp < 0){
        temp = temp + this->mod;
      }
      poly1[this->deg - i] = temp;
    }
  }
  else{
    dif.deg = other.deg;
    poly2 = this->coefficients;
    poly1 = other.coefficients;
    for (int i = 0; i < this->deg + 1; i ++){
       temp = poly2[this->deg - i] - poly1[other.deg - i];
       while (temp < 0){
         temp = temp + this->mod;
       }
       poly1[other.deg - i] = temp;
    }
  }
  dif.coefficients = poly1;
  while(dif.coefficients[0] % dif.mod == 0){
    dif.coefficients.erase(dif.coefficients.begin());
    dif.deg--;
  }
  return dif;
}

Polynom Polynom::operator * (const Polynom &other){
  int a;
  Polynom prod;
  a = this->deg + other.deg;
  prod.deg = a;
  prod.mod = this->mod;
  for(int i = 0; i < a + 1; i++){
    prod.coefficients.push_back(0);
  }
  for(int i = 0; i < this->deg + 1; i++){
    for (int j = 0; j < other.deg + 1; j++){
      prod.coefficients[i+j] = prod.coefficients[i+j] + this->coefficients[i] * other.coefficients[j];
    }
  }
  while(prod.coefficients[0] % prod.mod == 0){
    prod.coefficients.erase(prod.coefficients.begin());
    prod.deg--;
  }
  return prod;
}

Polynom Polynom::operator % (const Polynom &other){
  Polynom f = *this;
  Polynom g = other;
  Polynom h, res;
  int c;
  h.mod = f.mod;
  // res.mod = f.mod;
  // res.deg = f.deg - g.deg;
  while(g.deg <= f.deg){
    h.deg = f.deg;
    c = f.coefficients[0] % f.mod;
    while (c % g.coefficients[0] != 0){
      c = c + f.mod;
    }
    c = (c / g.coefficients[0]) % f.mod;
    // res.coefficients.push_back(c);
    h.coefficients.push_back((f.coefficients[0]) % f.mod);
    for (int i = 1; i < g.deg + 1; i++){
      h.coefficients.push_back((g.coefficients[i] * c) % f.mod);
    }
    for (int i = g.deg + 1; i < h.deg + 1; i++){
      h.coefficients.push_back(0);
    }
    f = f - h;
    h.coefficients.clear();
  }
  return f;
}

int Polynom::resultant(Polynom other){
  const int size = this->deg + other.deg;
  vector< vector<int> > matrix;

  for(int i = 0; i < size; i++){
    matrix.push_back(vector<int>());
    for(int j = 0; j < size; j++){
      matrix[i].push_back(0);
    }
  }

  for(int i = 0; i < other.deg; i++){
    for(int j = i; j < this->deg + i + 1; j++){
      matrix[i][j] = this->coefficients[j-i];
    }
  }
  for(int i = other.deg; i < size; i++){
    for(int j = i; j < other.deg + i + 1; j++){
      matrix[i][j-other.deg] = other.coefficients[j-i];
    }
  }

  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  int resul = determinant(matrix, size);
  return resul;
}

int Polynom::discriminant(){
  Polynom f = (*this).derivative();
  return (*this).resultant(f);
}

bool Polynom::has_common_root(Polynom other){
  if((*this).resultant(other) == 0){
    return true;
  }
  else{
    return false;
  }
}

bool Polynom::has_multiple_root(){
  if((*this).discriminant() == 0){
    return true;
  }
  else{
    return false;
  }
}

void Polynom::output_in_txt(const char* filename){

  ofstream fout;

  fout.open(filename, ofstream::app);

  if(!fout.is_open()){
    cout << "Can't open the file " << filename << "!" << endl;
    fout.close();
  }
  else{
    fout << "Polynom P(x) from Z" << mod << "[x] field:\t";
    fout << "P(x) = ";
    if (mod == 0){
      for (int i = 0; i < deg + 1; i++){
        if (i == 0){
          if (coefficients[i] != 1){
            fout << coefficients[i] << "x^" << deg - i;
          }
          else{
            fout << "x^" << deg - i;
          }
        }
        else if ( (i > 0) && (i != deg) && (i != deg - 1)){
          if (coefficients[i] != 0){
            if (coefficients[i] != 1){
              fout << " + " << coefficients[i] << "x^" << deg - i;
            }
            else{
              fout << " + " << "x^" << deg - i;
            }
          }
        }
        else if (i == deg - 1){
          if (coefficients[i] != 0){
            if (coefficients[i] != 1){
              fout << " + " << coefficients[i] << "x";
            }
            else{
              fout << " + " << "x";
            }
          }
        }
        else{
          if (coefficients[i] == 0){
            fout << "\n";
          }
          else{
            fout << " + " << coefficients[i] << "\n";
          }
        }
      }
    }
    else{
      for (int i = 0; i < deg + 1; i++){
        if (i == 0){
          if (coefficients[i] % mod != 1){
            fout << coefficients[i] % mod << "x^" << deg - i;
          }
          else{
            fout << "x^" << deg - i;
          }
        }
        else if ( (i > 0) && (i != deg) && (i != deg - 1)){
          if (coefficients[i] % mod != 0){
            if (coefficients[i] % mod != 1){
              fout << " + " << coefficients[i] % mod << "x^" << deg - i;
            }
            else{
              fout << " + " << "x^" << deg - i;
            }
          }
        }
        else if (i == deg - 1){
          if (coefficients[i] % mod != 0){
            if (coefficients[i] % mod != 1){
              fout << " + " << coefficients[i] % mod << "x";
            }
            else{
              fout << " + " << "x";
            }
          }
        }
        else{
          if (coefficients[i] % mod == 0){
            fout << "\n";
          }
          else{
            fout << " + " << coefficients[i] % mod << "\n";
          }
        }
      }
    }
    fout.close();
  }
}
