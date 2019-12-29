#include "Point2D.h"
#include "Segment2D.h"
#include "Line2D.h"
#include "Circle2D.h"
#include "Triangle2D.h"
#include "Geometry2D.h"
#include <iostream>
#include <string>
using namespace std;

int main() {

    string choose;
    Geometry2D my_geometry = Geometry2D();

    cout << "Welcome to Geometry2D calculator! Here yo can find a lot of values of different planimetry objects." << endl;
    cout << "Firstly, you should create your triangle and line." << endl;
    cout << "You have triangle ABC with vertexes A(x1, y1), B(x2, y2) and C(x3, y3)." << endl;
    cout << "Also, you have a line L: ax + by + c = 0." << endl;
    cout << "You work in space R^2." << endl;

    cout << "Input 'console' to work with console" << endl << "Input 'binary' to work with binary file" << endl << "Input 'text' to work with text file" << endl << endl << endl;
    cin >> choose;

    if (choose == "console") {

        cout << endl << endl << "You are working with console!" << endl << endl << endl;

        my_geometry.inputGeometry2D();
        my_geometry.outputGeometry2D();
    }
    else if (choose == "binary") {

        cout << endl << endl << "You are working with binary file!" << endl << endl << endl;

        if (my_geometry.inputBinaryFile("Geometry2D_in.dat") == 0) {
            cout << endl << "Sucsessfully got data from binary file!" << endl;
        }
        else {
            printf("ERROR WHILE GETTING DATA FROM BINARY FILE 'Geometry2D_in.dat'!!!\n");
            cout << endl << "ERROR WHILE GETTING DATA FROM BINARY FILE 'Geometry2D_in.dat'!!!" << endl;
        }

        if (my_geometry.outputBinaryFile("Geometry2D_out.dat") == 0) {
            cout << endl << "Sucsessfully created binary file with all values!" << endl;
        }
        else {
            cout << endl << "ERROR WHILE CREATING BINARY FILE 'Geometry2D_out.dat'!!!" << endl;
        }
    }
    else if (choose == "text") {

        cout << endl << endl << "You are working with text file!" << endl << endl << endl;

        if (my_geometry.inputTextFile("Geometry2D_in.txt") == 0) {
            cout << endl << "Sucsessfully got data from text file 'Geometry2D_in.txt'!" << endl;
        }
        else {
            cout << endl << "ERROR WHILE GETTING DATA FROM TEXT FILE 'Geometry2D_in.txt'!!!" << endl;
        }

        if (my_geometry.outputTextFile("Geometry2D_out.txt") == 0) {
            cout << endl << "Sucsessfully created text file 'Geometry2D_out.txt' with all values!" << endl;
        }
        else {
            cout << endl << "ERROR WHILE CREATING TEXT FILE 'Geometry2D_out.txt'!!!" << endl;
        }
    }
    else {
        cout << "Incorrect desision!" << endl;
    }

}