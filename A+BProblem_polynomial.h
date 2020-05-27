#pragma once
#include "complex.h"

template <class T>
class Polynomial
{
    T * coef;
    shlong size;

    Complex * rootsLookup;
    Complex * X;
    shlong Xsize;

    void fftBackend(shlong numRoots, shlong div = 1, shlong off = 0, shlong Xoff = 0);
public:
    Polynomial(shlong size);
    Polynomial(T * Coef, shlong Size) : coef(Coef), size(Size) {}
    Polynomial(Polynomial * f, bool even);
    Polynomial(ifstream &fin);
    ~Polynomial();

    shlong getSize() { return size; }

    Complex * fft(shlong numRoots);
    Complex * fftInverse(shlong numRoots);

    Complex polynomialize(Complex &x, shlong div = 1, shlong off = 0);

    void operator=(Polynomial<T> * p);
};

template <class T>
Polynomial<T>::Polynomial(shlong size)
{
    coef = new T[size]();
    this->size = size;
}


template <class T>
Polynomial<T>::Polynomial(Polynomial<T> * f, bool even)
{
    size = f->size >> 1;
    coef = new T[size]();
    if (even)
        for (shlong i = 0; i < size; i++)
            coef[i] = f->coef[2 * i];
    else
        for (shlong i = 0; i < size; i++)
            coef[i] = f->coef[2 * i + 1];
}

template <class T>
Polynomial<T>::Polynomial(ifstream & fin)
{
    fin >> size;
    // make size next power of 2
    size = (shlong)pow(2, ((shlong)log2(size - 1) + 1));
    coef = new T[size]();

    T temp;
    for (shlong i = size - 1; i >= 0; i--)
    {
        fin >> temp;
        coef[i] = temp;
    }
}

template <class T>
Polynomial<T>::~Polynomial()
{
    //delete[] coef;
}

template <class T>
void Polynomial<T>::fftBackend(shlong numRoots, shlong div, shlong off, shlong Xoff)
{
    if (numRoots <= 2)
    {
        for (shlong i = 0; i < numRoots; i++)
            X[Xoff + i] = polynomialize(rootsLookup[div*i], div, off);
        return;
    }

    // NumRoots is cut in half
    numRoots >>= 1;

    fftBackend(numRoots,div<<1,off,Xoff);
    fftBackend(numRoots,div<<1,off+div,Xoff+numRoots);

    for (shlong i = 0; i < numRoots; i++)
    {
        Complex temp = X[Xoff + i];
        X[Xoff + i] = X[Xoff + i] + rootsLookup[i*div] * X[Xoff + numRoots + i];
        X[Xoff + numRoots + i] = temp + rootsLookup[i*div+(Xsize>>1)] * X[Xoff + numRoots + i];
    }
}

template<class T>
Complex * Polynomial<T>::fftInverse(shlong numRoots)
{
    Xsize = numRoots;
    X = new Complex[Xsize];
    rootsLookup = Complex::getInverseRoots(Xsize);
    fftBackend(numRoots);
    delete[] rootsLookup;
    return X;
}

template<class T>
Complex * Polynomial<T>::fft(shlong numRoots)
{
    Xsize = numRoots;
    X = new Complex[numRoots];
    rootsLookup = Complex::getRootsUnity(numRoots);

    fftBackend(numRoots);

    delete[] rootsLookup;
    return X;
}

template <class T>
Complex Polynomial<T>::polynomialize(Complex &x, shlong div, shlong off)
{
    Complex f(0, 0);
    Complex xn(1, 0);
    for (shlong i = off; i < size; i += div)
    {
        f += coef[i] * xn;
        xn *= x;
    }
    return f;
}

template <class T>
void Polynomial<T>::operator=(Polynomial<T> * p)
{
    delete[] coef;
    coef = p->coef;
    size = p->size;
}

