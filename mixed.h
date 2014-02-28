// Name: Nathaniel Wingfield
// Section: 3
// File: mixed.h
// Asg:  #7
// Date: 11/24/02
//
// Purpose:  Declaration of the mixed number class 'Mixed'

#include <iostream.h>

class Mixed {
    friend ostream& operator << (ostream& s, const Mixed& m);
    friend istream& operator >> (istream& s, Mixed& m);
    friend bool operator < (Mixed m1, Mixed m2);
    friend bool operator > (Mixed m1, Mixed m2);
    friend bool operator <= (Mixed m1, Mixed m2);
    friend bool operator >= (Mixed m1, Mixed m2);
    friend bool operator == (Mixed m1, Mixed m2);
    friend bool operator != (Mixed m1, Mixed m2);
    friend Mixed operator + (Mixed m1, Mixed m2);
    friend Mixed operator - (Mixed m1, Mixed m2);
    friend Mixed operator * (Mixed m1, Mixed m2);
    friend Mixed operator / (Mixed m1, Mixed m2);
public:
    Mixed();
    Mixed(int w);
    Mixed(int w, int n, int d);
    double Evaluate(); // return the decimal equivalent
    void ToFraction(); // convert the mixed number into fraction form, possibly improper fraction
    void Simplify(); // simplify to lowest terms
private:
    int sign;
    int whole;
    int numerator;
    int denominator;
};
