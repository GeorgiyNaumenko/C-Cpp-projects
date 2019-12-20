#include "../src/IPoly.h"
#include "../src/IPoly.cpp"        /* else it doesn't want to see realization of my methods */
#include <iostream>
#include <fstream>
using namespace std;

int main(){

  string q;
  cout << "Enter the way of output (text or console) :" << endl;
  cin >> q;

  if ("text" == q){

    /* This output is not finished yet: it doesn't want to write polynoms */

    const char* filename = "IPoly_out.txt";
    ofstream fout;

    fout.open(filename);
    fout << "Hi! Welcome to polynom calculator! \nYou can work either with polynoms from Z[x] or from Zp[x]!";
    fout.close();

    int a, b;

    Polynom pol, deriv, defin_in, rem, sum, prod, pol1;

    pol = Polynom();
    pol.input();
    pol.output_in_txt(filename);

    fout.open(filename, ofstream::app);
    fout << "\nDerivative P'(x):\t";
    fout.close();

    deriv = pol.derivative();
    deriv.output_in_txt(filename);

    fout.open(filename, ofstream::app);
    fout << "\nIntegral P(x)dx:\t";
    fout.close();

    defin_in = pol.indefinite_integral();
    defin_in.output_in_txt(filename);

    fout.open(filename, ofstream::app);
    fout << "\n" << pol.definite_integral(2, 3) << "\n";
    fout.close();

    pol1.input();
    pol1.output_in_txt(filename);

    sum = pol1 + pol;

    fout.open(filename, ofstream::app);
    fout << "\nSum Q(x) + P(x):\t";
    fout.close();

    sum.output_in_txt(filename);

    prod = pol1 * pol;

    fout.open(filename, ofstream::app);
    fout << "\nProd Q(x) * P(x):\t";
    fout.close();

    prod.output_in_txt(filename);

    rem = pol % pol1;

    fout.open(filename, ofstream::app);
    fout << "\nReminder Q(x) % P(x):\t";
    fout.close();

    rem.output_in_txt(filename);

    fout.open(filename, ofstream::app);
    fout << "\nRes(P(x), Q(x)): \n" << "\n";
    fout << pol.resultant(pol1) << "\n";
    fout << "\ndiscriminant of P(x):" << "\n";
    fout << pol.discriminant() << "\n";
    if(pol.has_common_root(pol1)){
      fout << "\nP(x) has common root with Q(x).\n" << "\n";
    }
    else{
      fout << "\nP(x) hasn't common root with Q(x).\n" << "\n";
    }
    if(pol.has_multiple_root()){
      fout << "\nP(x) has multiple root.\n" << "\n";
    }
    else{
      fout << "\nP(x) hasn't multiple root.\n" << "\n";
    }
    fout.close();
  }

  else if ("console" == q){
    Polynom pol;
    Polynom deriv, defin_in, rem;
    pol = Polynom();
    pol.input();
    pol.output();
    cout << "\nDerivative P'(x):\t";
    deriv = pol.derivative();
    deriv.output();
    cout << "\nIntegral P(x)dx:\t";
    defin_in = pol.indefinite_integral();
    defin_in.output();
    cout << "\n" << pol.definite_integral(2, 3) << endl;
    Polynom pol1, sum, prod;
    pol1.input();
    pol1.output();
    sum = pol1 + pol;
    cout << "\nSum Q(x) + P(x):\t";
    sum.output();
    prod = pol1 * pol;
    cout << "\nProd Q(x) * P(x):\t";
    prod.output();
    rem = pol % pol1;
    cout << "\nReminder Q(x) % P(x):\t";
    rem.output();
    cout << "\nRes(P(x), Q(x)): \n" << endl;
    cout << pol.resultant(pol1) << endl;
    cout << "\ndiscriminant of P(x): \n" << endl;
    cout << pol.discriminant() << endl;
    if(pol.has_common_root(pol1)){
      cout << "\nP(x) has common root with Q(x).\n" << endl;
    }
    else{
      cout << "\nP(x) hasn't common root with Q(x).\n" << endl;
    }
    if(pol.has_multiple_root()){
      cout << "\nP(x) has multiple root.\n" << endl;
    }
    else{
      cout << "\nP(x) hasn't multiple root.\n" << endl;
    }
  }

  else{
    cout << "Incorrect way!" << endl;
  }
}
