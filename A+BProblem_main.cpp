#include "polynomial.h"
#include <limits>
#include <vector>

shlong freq[262145] = { 0 };
shlong * zero = &freq[131073];

shlong AB(Complex * X, shlong * sums, shlong size, shlong off);

vector<shlong> v;
void test();

int main()
{
    shlong size, temp, off = 0;
    shlong min = numeric_limits<shlong>::max(), max = numeric_limits<shlong>::min();
    shlong count, zeros = 0;

    cin >> size;
    for (shlong i = 0; i < size; i++)
    {
        cin >> temp;
        if (temp == 0)
            zeros++;
        else
        {
            zero[temp]++;
            if (temp < min)
                min = temp;
            if (temp > max)
                max = temp;
        }
        v.push_back(temp);
    }

    if (min < 0)
    {
        size = max - min;
        off = -min;
    }
    else
        size = max;
    if (size == 0)
        size = 2;
    else
        size = (shlong)pow(2, ((shlong)log2(size) + 1));
    
    Polynomial<shlong> p(&zero[-off], size);
    size *= 2;
    Complex * temps = p.fft(size);
    Complex::squareArray(temps, size);
    Polynomial<Complex> i(temps, size);
    Complex * X = i.fftInverse(size);
    count = AB(&X[off], &zero[-off], size, off);

    if(size != 0 && 2 * off < size)
        count += (shlong)(X[2 * off].getA() + 0.5) / size * zeros;
        
    count += zeros * (zeros * (zeros - 3) + 2);

    for (shlong i = min; i <= max; i++)
        count += 2 * zeros * zero[i] * (zero[i] - 1);

    cout << count << endl;

    delete[] temps;
    delete[] X;
    return 0;
}

shlong AB(Complex * X, shlong * sums, shlong size, shlong off)
{
    shlong count = 0;
    shlong sSize = size / 2;
    shlong xSize = size - off;
    for (shlong i = 0; i < sSize && i < xSize; i++) 
    {
        count += (shlong)(X[i].getA() + 0.5) / size * sums[i];
        if (abs(i - off) % 2 == 0)
            count -= sums[i] * (zero[(i - off) / 2]);
    }
    return count;
}

void test()
{
    shlong count = 0;

    for (int i = 0; i < v.size(); i++)
        for (int j = 0; j < v.size(); j++)
            for (int k = 0; k < v.size(); k++)
                if (i != j && i != k && j != k && v[i] + v[j] == v[k])
                    count++;

    cout << count << endl;
}
