#include "complex.h"

Complex * Complex::getRootsUnity(shlong n)
{
    Complex * roots = new Complex[n];
    longD theta = 0, step = 2 * PI / n;
    for (shlong i = 0; i < n; i++)
    {
        roots[i].a = cosl(theta);
        roots[i].b = sinl(theta);
        theta += step;
    }
    return roots;
}

Complex * Complex::getInverseRoots(shlong n)
{
    Complex * roots = new Complex[n];
    longD theta = 0, step = 2 * PI / n;
    for (shlong i = 0; i < n; i++)
    {
        roots[i].a = cosl(theta);
        roots[i].b = sinl(theta);
        theta -= step;
    }
    return roots;
}

Complex * Complex::squareArray(Complex * arr, shlong size)
{
    for (shlong i = 0; i < size; i++)
        arr[i] = arr[i] * arr[i];
    return arr;
}

long long Complex::cleanUp(Complex * arr, shlong * freq, shlong size)
{
    long long count = 0;
    for (shlong i = 1; i < size/2; i++)
    {
        shlong temp = (shlong)(((arr[i].a + 0.5 - (arr[i].a < 0)) / size)) - 2 * freq[0];
        count += temp * (freq[i]);
        if (i % 2 == 0)
            count -= freq[i / 2] * freq[i];
    }
    delete[] arr;
    return count;
}

Complex * Complex::reverseArray(Complex * arr, shlong size)
{
    Complex temp;
    for (shlong i = 0; i < size / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
    return arr;
}

longD Complex::mag()
{
    return Complex((*this)*Complex(a,-1*b)).a;
}

void Complex::operator+=(Complex y)
{
    a += y.a;
    b += y.b;
}

void Complex::operator*=(Complex y)
{
    longD temp = a;
    a = a * y.a - b * y.b;
    b = temp * y.b + b * y.a;
}

Complex operator+(Complex x, Complex y)
{
    return Complex(x.a + y.a, x.b + y.b);
}

Complex operator*(Complex x, Complex y)
{
    return Complex(x.a*y.a - x.b*y.b, x.a*y.b + x.b*y.a);
}

Complex operator*(shlong a, Complex b)
{
    return Complex(a*b.a,a*b.b);
}

Complex operator/(Complex a, shlong b)
{
    return Complex(a.a/b,a.b/b);
}

ostream & operator<<(ostream & out, Complex c)
{
    out << c.a;
    if (c.b >= 0)
        out << " +";
    out << ' ' << c.b << "i ";
    return out;
}


