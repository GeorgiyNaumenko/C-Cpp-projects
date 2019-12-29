#pragma once
#include "Geometry2D.h"
#include "Circle2D.h"
#include "Point2D.h"
#include "Segment2D.h"
#include "Line2D.h"
#include "Triangle2D.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

Geometry2D::Geometry2D() {

}

Geometry2D::Geometry2D(Triangle2D a1, Line2D l1) {

	a = a1;
	l = l1;
}

int Geometry2D::inputGeometry2D() {

    cout << "Input the double type coordinate 'x' of vertex A and press 'Enter':" << endl;
    cin >> this->a.a.x;
    cout << "Input the double type coordinate 'y' of vertex A and press 'Enter':" << endl;
    cin >> this->a.a.y;
    cout << "Input the double type coordinate 'x' of vertex B and press 'Enter':" << endl;
    cin >> this->a.b.x;
    cout << "Input the double type coordinate 'y' of vertex B and press 'Enter':" << endl;
    cin >> this->a.b.y;
    cout << "Input the double type coordinate 'x' of vertex C and press 'Enter':" << endl;
    cin >> this->a.c.x;
    cout << "Input the double type coordinate 'y' of vertex C and press 'Enter':" << endl;
    cin >> this->a.c.y;
    cout << "Input the double type coefficient 'a' of line L and press 'Enter':" << endl;
    cin >> this->l.a;
    cout << "Input the double type coefficient 'b' of line L and press 'Enter':" << endl;
    cin >> this->l.b;
    cout << "Input the double type coefficient 'c' of line L and press 'Enter':" << endl;
    cin >> this->l.c;

    return 0;

}

void Geometry2D::outputGeometry2D() {

    this->find_two_areas();

    Point2D vector_A, vector_B, vector_C;

    vector_A.x = this->a.a.x;
    vector_B.x = this->a.b.x;
    vector_C.x = this->a.c.x;
    vector_A.y = this->a.a.y;
    vector_B.y = this->a.b.y;
    vector_C.y = this->a.c.y;

    cout << "Let OA->, OB->, OC-> be a radius-vectors of points A, B, C." << endl;

    cout << "Scalar products:" << endl;
    cout << "(OA->, OB->) = " << vector_A.mulS(&vector_B);
    cout << "(OA->, OC->) = " << vector_A.mulS(&vector_C);
    cout << "(OB->, OC->) = " << vector_B.mulS(&vector_C) << endl;

    cout << "Vector products:" << endl;
    cout << "[OA-> x OB->] = (0, 0, " << vector_A.mul(&vector_B) << "), ";
    cout << "[OB-> x OA->] = (0, 0, " << vector_B.mul(&vector_A) << endl;
    cout << "[OA-> x OC->] = (0, 0, " << vector_A.mul(&vector_C) << "), ";
    cout << "[OC-> x OA->] = (0, 0, " << vector_C.mul(&vector_A) << endl;
    cout << "[OB-> x OC->] = (0, 0, " << vector_B.mul(&vector_C) << "), ";
    cout << "[OC-> x OB->] = (0, 0, " << vector_C.mul(&vector_B) << endl;

    cout << "Sums of radius - vectors:" << endl;
    cout << "OA-> + OB-> = (" << vector_A.add(&vector_B).x << ", " << vector_A.add(&vector_B).y << ")" << endl;
    cout << "OA-> + OC-> = (" << vector_A.add(&vector_C).x << ", " << vector_A.add(&vector_C).y << ")" << endl;
    cout << "OC-> + OB-> = (" << vector_C.add(&vector_B).x << ", " << vector_C.add(&vector_B).y << ")" << endl;

    cout << "Lengthes of ABC sides:" << endl;
    cout << "AB = " << this->a.a.two_points_length(&this->a.b) << endl;
    cout << "AC = " << this->a.a.two_points_length(&this->a.c) << endl;
    cout << "BC = " << this->a.c.two_points_length(&this->a.b) << endl;

    cout << "Some special points and values in ABC:" << endl;
    cout << "Perimeter of ABC: " << this->a.perimeter() << endl;
    cout << "Area of ABC: " << this->a.area() << endl;
    cout << "Incenter: (" << this->a.inceter().x << ", " << this->a.inceter().y << ")" << endl;
    cout << "Radius of inscribed circle = " << this->a.inscribed_radius() << endl;
    cout << "Center: (" << this->a.center().x << ", " << this->a.center().y << ")" << endl;
    cout << "Radius of described circle = " << this->a.described_radius() << endl;
    cout << "Centroid: (" << this->a.centroid().x << ", " << this->a.centroid().y << ")" << endl;

    cout << "Angles in radians:" << endl;
    cout << "<A = " << this->a.angelA() << " radians" << endl;
    cout << "<B = " << this->a.angelB() << " radians" << endl;
    cout << "<C = " << this->a.angelC() << " radians" << endl;
    cout << "And as sum you get: ";
    cout << "pi = " << a.angelA() + a.angelB() + a.angelC() << endl;

    cout << "Equalities of some special lines in ABC:" << endl;

    cout << "Median from vertex A:\t";
    this->a.medianA().console_show_line();
    cout << "Median from vertex B:\t";
    this->a.medianB().console_show_line();
    cout << "Median from vertex C:\t";
    this->a.medianC().console_show_line();

    cout << "Heigth from vertex A:\t";
    this->a.heigthA().console_show_line();
    cout << "Heigth from vertex B:\t";
    this->a.heigthB().console_show_line();
    cout << "Heigth from vertex C:\t";
    this->a.heigthC().console_show_line();

    cout << "Bisector from vertex A:\t";
    this->a.bisectorA().console_show_line();
    cout << "Bisector from vertex B:\t";
    this->a.bisectorB().console_show_line();
    cout << "Bisector from vertex C:\t";
    this->a.bisectorC().console_show_line();
    
    cout << "And the answer to the main qastion:" << endl;
    cout << endl;
    if (this->s2 == 0.0) {
        cout << "Triangle ABC wasn't divided by line L into 2 figures." << endl;
    }
    else {
        cout << "Triangle ABC was divided by line L into two figures with areas " << this->s1 << " and " << this->s2 << "." << endl;
    }
   
    cout << endl;
    cout << endl;
    cout << "And now, let's look at some really interesting geometry things!" << endl;
    cout << "This programm is capable of building some really interesting geometry objects in triangle." << endl;

    cout << "Tangent to described circle of ABC in point A:\t";
    this->a.described_circle().tangent_to_circle(&this->a.a).console_show_line();
    cout << "Tangent to described circle of ABC in point B:\t";
    this->a.described_circle().tangent_to_circle(&this->a.b).console_show_line();
    cout << "Tangent to described circle of ABC in point C:\t";
    this->a.described_circle().tangent_to_circle(&this->a.c).console_show_line();

    cout << "Symmedian of ABC from vertex A:\t";
    this->a.symmedianA().console_show_line();
    cout << "Symmedian of ABC from vertex B:\t";
    this->a.symmedianB().console_show_line();
    cout << "Symmedian of ABC from vertex C:\t";
    this->a.symmedianC().console_show_line();

    cout << "Lemuan point of ABC:\t (" << this->a.lemuan_point().x << ", " << this->a.lemuan_point().y << ")" << endl;

    cout << "Unwriten circle of ABC which is tangent to AB:\t";
    this->a.unwritten_circle_AB().console_show_circle();
    cout << "Unwriten circle of ABC which is tangent to BC:\t";
    this->a.unwritten_circle_BC().console_show_circle();
    cout << "Unwriten circle of ABC which is tangent to AC:\t";
    this->a.unwritten_circle_AC().console_show_circle();

    cout << "Radical axis of unwritten circles which are tangent to AC and AB:\t";
    this->a.unwritten_circle_AC().radical_axis(&this->a.unwritten_circle_AB()).console_show_line();
    cout << "Radical axis of unwritten circles which are tangent to AC and AB:\t";
    this->a.unwritten_circle_AB().radical_axis(&this->a.unwritten_circle_BC()).console_show_line();
    cout << "Radical axis of unwritten circles which are tangent to AC and AB:\t";
    this->a.unwritten_circle_AC().radical_axis(&this->a.unwritten_circle_BC()).console_show_line();
    cout << "Radical center of three unwritten circles of ABC:\t (" << this->a.unwritten_circle_AB().radical_center(&this->a.unwritten_circle_AC(), &this->a.unwritten_circle_BC()).x;
    cout << ", " << this->a.unwritten_circle_AB().radical_center(&this->a.unwritten_circle_AC(), &this->a.unwritten_circle_BC()).y << ")" << endl;

    cout << "Nikel point of ABC:\t (" << this->a.nikel_point().x << ", " << this->a.nikel_point().y << ")" << endl;

    cout << "Euler circle (circle of nine points) of ABC:\t";
    this->a.euler_circle().console_show_circle();

    cout << endl << endl << "T H A N K   Y O U !   W A I T   F O R   U P D A T E S   S O O N !" << endl;

}

int Geometry2D::inputTextFile(const char* filename) {

    ifstream fin;
    string taken;

    fin.open(filename);

    if (fin.is_open()) {

        cout << endl << "File '" << filename << "' successfully opened!" << endl;

        fin >> taken;
        this->a.a.x = stoi(taken);
        fin >> taken;
        this->a.a.y = stoi(taken);
        fin >> taken;
        this->a.b.x = stoi(taken);
        fin >> taken;
        this->a.b.y = stoi(taken);
        fin >> taken;
        this->a.c.x = stoi(taken);
        fin >> taken;
        this->a.c.y = stoi(taken);
        fin >> taken;
        this->l.a = stoi(taken);
        fin >> taken;
        this->l.b = stoi(taken);
        fin >> taken;
        this->l.c = stoi(taken);

        fin.close();

        return 0;

    }
    else {

        cout << endl << "Error while opening file '" << filename << "'!" << endl;

        return 1;
    }

}

int Geometry2D::outputTextFile(const char* filename) {

    this->find_two_areas();

    ofstream fout;

    fout.open(filename, ofstream::app);

    if (fout.is_open()) {

        cout << endl << "File '" << filename << "' successfully opened!" << endl;

        Point2D vector_A, vector_B, vector_C;

        vector_A.x = this->a.a.x;
        vector_B.x = this->a.b.x;
        vector_C.x = this->a.c.x;
        vector_A.y = this->a.a.y;
        vector_B.y = this->a.b.y;
        vector_C.y = this->a.c.y;

        fout << "Let OA->, OB->, OC-> be a radius-vectors of points A, B, C." << "\n";

        fout << "Scalar products:" << "\n";
        fout << "(OA->, OB->) = " << vector_A.mulS(&vector_B);
        fout << "(OA->, OC->) = " << vector_A.mulS(&vector_C);
        fout << "(OB->, OC->) = " << vector_B.mulS(&vector_C) << "\n";

        fout << "Vector products:" << "\n";
        fout << "[OA-> x OB->] = (0, 0, " << vector_A.mul(&vector_B) << "), ";
        fout << "[OB-> x OA->] = (0, 0, " << vector_B.mul(&vector_A) << "\n";
        fout << "[OA-> x OC->] = (0, 0, " << vector_A.mul(&vector_C) << "), ";
        fout << "[OC-> x OA->] = (0, 0, " << vector_C.mul(&vector_A) << "\n";
        fout << "[OB-> x OC->] = (0, 0, " << vector_B.mul(&vector_C) << "), ";
        fout << "[OC-> x OB->] = (0, 0, " << vector_C.mul(&vector_B) << "\n";

        fout << "Sums of radius - vectors:" << "\n";
        fout << "OA-> + OB-> = (" << vector_A.add(&vector_B).x << ", " << vector_A.add(&vector_B).y << ")" << "\n";
        fout << "OA-> + OC-> = (" << vector_A.add(&vector_C).x << ", " << vector_A.add(&vector_C).y << ")" << "\n";
        fout << "OC-> + OB-> = (" << vector_C.add(&vector_B).x << ", " << vector_C.add(&vector_B).y << ")" << "\n";

        fout << "Lengthes of ABC sides:" << "\n";
        fout << "AB = " << this->a.a.two_points_length(&this->a.b) << "\n";
        fout << "AC = " << this->a.a.two_points_length(&this->a.c) << "\n";
        fout << "BC = " << this->a.c.two_points_length(&this->a.b) << "\n";

        fout << "Some special points and values in ABC:" << "\n";
        fout << "Perimeter of ABC: " << this->a.perimeter() << "\n";
        fout << "Area of ABC: " << this->a.area() << "\n";
        fout << "Incenter: (" << this->a.inceter().x << ", " << this->a.inceter().y << ")" << "\n";
        fout << "Radius of inscribed circle = " << this->a.inscribed_radius() << "\n";
        fout << "Center: (" << this->a.center().x << ", " << this->a.center().y << ")" << "\n";
        fout << "Radius of described circle = " << this->a.described_radius() << "\n";
        fout << "Centroid: (" << this->a.centroid().x << ", " << this->a.centroid().y << ")" << "\n";

        fout << "Angles in radians:" << "\n";
        fout << "<A = " << this->a.angelA() << " radians" << "\n";
        fout << "<B = " << this->a.angelB() << " radians" << "\n";
        fout << "<C = " << this->a.angelC() << " radians" << "\n";
        fout << "And as sum you get: ";
        fout << "pi = " << a.angelA() + a.angelB() + a.angelC() << "\n";

        fout << "Equalities of some special lines in ABC:" << "\n";

        fout << "Median from vertex A:\t";
        this->a.medianA().textfile_show_line(filename);
        fout << "Median from vertex B:\t";
        this->a.medianB().textfile_show_line(filename);
        fout << "Median from vertex C:\t";
        this->a.medianC().textfile_show_line(filename);

        fout << "Heigth from vertex A:\t";
        this->a.heigthA().textfile_show_line(filename);
        fout << "Heigth from vertex B:\t";
        this->a.heigthB().textfile_show_line(filename);
        fout << "Heigth from vertex C:\t";
        this->a.heigthC().textfile_show_line(filename);

        fout << "Bisector from vertex A:\t";
        this->a.bisectorA().textfile_show_line(filename);
        fout << "Bisector from vertex B:\t";
        this->a.bisectorB().textfile_show_line(filename);
        fout << "Bisector from vertex C:\t";
        this->a.bisectorC().textfile_show_line(filename);

        fout << "And the answer to the main qastion:" << "\n";
        fout << endl;
        if (this->s2 == 0.0) {
            fout << "Triangle ABC wasn't divided by line L into 2 figures." << "\n";
        }
        else {
            fout << "Triangle ABC was divided by line L into two figures with areas " << this->s1 << " and " << this->s2 << "." << "\n";
        }

        fout << "\n";
        fout << "\n";
        fout << "And now, let's look at some really interesting geometry things!" << "\n";
        fout << "This programm is capable of building some really interesting geometry objects in triangle." << "\n";

        fout << "Tangent to described circle of ABC in point A:\t";
        this->a.described_circle().tangent_to_circle(&this->a.a).console_show_line();
        fout << "Tangent to described circle of ABC in point B:\t";
        this->a.described_circle().tangent_to_circle(&this->a.b).console_show_line();
        fout << "Tangent to described circle of ABC in point C:\t";
        this->a.described_circle().tangent_to_circle(&this->a.c).console_show_line();

        fout << "Symmedian of ABC from vertex A:\t";
        this->a.symmedianA().textfile_show_line(filename);
        fout << "Symmedian of ABC from vertex B:\t";
        this->a.symmedianB().textfile_show_line(filename);
        fout << "Symmedian of ABC from vertex C:\t";
        this->a.symmedianC().textfile_show_line(filename);

        fout << "Lemuan point of ABC:\t (" << this->a.lemuan_point().x << ", " << this->a.lemuan_point().y << ")" << endl;

        fout << "Unwriten circle of ABC which is tangent to AB:\t";
        this->a.unwritten_circle_AB().textfile_show_circle(filename);
        fout << "Unwriten circle of ABC which is tangent to BC:\t";
        this->a.unwritten_circle_BC().textfile_show_circle(filename);
        fout << "Unwriten circle of ABC which is tangent to AC:\t";
        this->a.unwritten_circle_AC().textfile_show_circle(filename);

        fout << "Radical axis of unwritten circles which are tangent to AC and AB:\t";
        this->a.unwritten_circle_AC().radical_axis(&this->a.unwritten_circle_AB()).textfile_show_line(filename);
        fout << "Radical axis of unwritten circles which are tangent to AC and AB:\t";
        this->a.unwritten_circle_AB().radical_axis(&this->a.unwritten_circle_BC()).textfile_show_line(filename);
        fout << "Radical axis of unwritten circles which are tangent to AC and AB:\t";
        this->a.unwritten_circle_AC().radical_axis(&this->a.unwritten_circle_BC()).textfile_show_line(filename);
        fout << "Radical center of three unwritten circles of ABC:\t (" << this->a.unwritten_circle_AB().radical_center(&this->a.unwritten_circle_AC(), &this->a.unwritten_circle_BC()).x;
        fout << ", " << this->a.unwritten_circle_AB().radical_center(&this->a.unwritten_circle_AC(), &this->a.unwritten_circle_BC()).y << ")" << "\n";

        fout << "Nikel point of ABC:\t (" << this->a.nikel_point().x << ", " << this->a.nikel_point().y << ")" << "\n";

        fout << "Euler circle (circle of nine points) of ABC:\t";
        this->a.euler_circle().textfile_show_circle(filename);

        fout << "\n" << "\n" << "T H A N K   Y O U !   W A I T   F O R   U P D A T E S   S O O N !" << "\n";

    }
    
    else {

        cout << endl << "Error while opening file '" << filename << "'!" << endl;

        return 1;

    }
}

int Geometry2D::inputBinaryFile(const char* filename) {

    return 0;

}

int Geometry2D::outputBinaryFile(const char* filename){
    
    return 0;

}

void Geometry2D::find_two_areas() {

    Segment2D ab, ac, bc;

    ab.a = this->a.a;
    ab.b = this->a.b;
    ac.a = this->a.a;
    ac.b = this->a.c;
    bc.a = this->a.c;
    bc.b = this->a.b;

    /* One of the segments AC, AB or BC lies on the line L */
    if (((this->l.intersection_l_s(&ab).x == HUGE_VAL) && (this->l.intersection_l_s(&ab).y == HUGE_VAL)) || ((this->l.intersection_l_s(&ac).x == HUGE_VAL) && (this->l.intersection_l_s(&ac).y == HUGE_VAL)) || ((this->l.intersection_l_s(&bc).x == HUGE_VAL) && (this->l.intersection_l_s(&bc).y == HUGE_VAL))) {
        this->s2 = 0.0;
        this->s1 = this->a.area();
    }

    /* line L is passing through the vertex but is not passing through the opposite segment; 3 cases for each vertex */
    else if ((this->l.a * this->a.a.x + this->l.b * this->a.a.y + this->l.c == 0) && ((this->l.intersection_l_s(&bc).x == HUGE_VAL) && (this->l.intersection_l_s(&bc).y == -HUGE_VAL))) {
        this->s2 = 0.0;
        this->s1 = this->a.area();
    }
    else if ((this->l.a * this->a.b.x + this->l.b * this->a.b.y + this->l.c == 0) && ((this->l.intersection_l_s(&ac).x == HUGE_VAL) && (this->l.intersection_l_s(&ac).y == -HUGE_VAL))) {
        this->s2 = 0.0;
        this->s1 = this->a.area();
    }
    else if ((this->l.a * this->a.c.x + this->l.b * this->a.c.y + this->l.c == 0) && ((this->l.intersection_l_s(&ab).x == HUGE_VAL) && (this->l.intersection_l_s(&ab).y == -HUGE_VAL))) {
        this->s2 = 0.0;
        this->s1 = this->a.area();
    }

    /* the case when our line L even don't touch our triangle*/
    else if (((this->l.intersection_l_s(&bc).x == HUGE_VAL) && (this->l.intersection_l_s(&bc).y == -HUGE_VAL)) && ((this->l.intersection_l_s(&ac).x == HUGE_VAL) && (this->l.intersection_l_s(&ac).y == -HUGE_VAL)) && ((this->l.intersection_l_s(&ab).x == HUGE_VAL) && (this->l.intersection_l_s(&ab).y == -HUGE_VAL))) {
        this->s2 = 0.0;
        this->s1 = this->a.area();
    }

    /* all cases when one of areas will be zero have been shown yet, so now at least 2 sides of triangle will have a real intersection point with line L */
    /* no metter how many segments line L will intersect because all that we will do it's look for a triangle */
    /* that's because one of our figures MUST be triangle and we can calculate it's area: we have a function for that! */
    /* the area of second figure we can find easily: we just need to substract area of first figure from area of ABC */
    /* so now let's do it */

    /* the case when our line L intersects BC and AC. In this case we chould find those intersection points P and Q and calculate area of triangle PQC */
    else if ((this->l.intersection_l_s(&bc).x != HUGE_VAL) && (this->l.intersection_l_s(&ac).x != HUGE_VAL)) {
        Point2D p, q;
        Triangle2D cpq;
        p = this->l.intersection_l_s(&bc);
        q = this->l.intersection_l_s(&ac);
        cpq.a = this->a.c;
        cpq.b = p;
        cpq.c = q;
        this->s1 = cpq.area();
        this->s2 = this->a.area() - this->s1;
    }

    /* the case when our line L intersects BC and AB. In this case we chould find those intersection points P and Q and calculate area of triangle PQB */
    else if ((this->l.intersection_l_s(&bc).x != HUGE_VAL) && (this->l.intersection_l_s(&ab).x != HUGE_VAL)) {
        Point2D p, q;
        Triangle2D bpq;
        p = this->l.intersection_l_s(&bc);
        q = this->l.intersection_l_s(&ab);
        bpq.a = this->a.b;
        bpq.b = p;
        bpq.c = q;
        this->s1 = bpq.area();
        this->s2 = this->a.area() - this->s1;
    }

    /* the case when our line L intersects AC and AB. In this case we chould find those intersection points P and Q and calculate area of triangle PQA */
    else if ((this->l.intersection_l_s(&ac).x != HUGE_VAL) && (this->l.intersection_l_s(&ab).x != HUGE_VAL)) {
        Point2D p, q;
        Triangle2D apq;
        p = this->l.intersection_l_s(&ac);
        q = this->l.intersection_l_s(&ab);
        apq.a = this->a.a;
        apq.b = p;
        apq.c = q;
        this->s1 = apq.area();
        this->s2 = this->a.area() - this->s1;
    }

}
