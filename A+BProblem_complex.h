#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <tgmath.h>

using namespace std;

typedef long long shlong;
typedef long double longD;
#define PI 3.141592653589793238462643383279502884

class Complex {
    longD a;
    longD b;
  public:
    Complex() : a(0), b(0) {}
    Complex(longD A, longD B) : a(A), b(B) {}
    ~Complex() {}

    static Complex * getRootsUnity(shlong n);
    static Complex * getInverseRoots(shlong n); // creates new arr
    static Complex * squareArray(Complex * arr, shlong size); // creates new arr
    static long long cleanUp(Complex * arr, shlong * freq, shlong size); // deletes old array
    static Complex * reverseArray(Complex * arr, shlong size);
    longD mag();

    longD getA() {
        return a;
    }
    longD getB() {
        return b;
    }

    friend Complex operator+(Complex x, Complex y);
    friend Complex operator*(Complex x, Complex y);
    friend Complex operator*(shlong a, Complex b);
    friend Complex operator/(Complex a, shlong b);
    friend ostream & operator<<(ostream & out, Complex c);
    void operator+=(Complex y);
    void operator*=(Complex y);

};
