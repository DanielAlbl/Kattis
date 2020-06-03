#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MOD 1000000007
typedef long long shlong;

shlong pascal[50001];

// size is q+1
void updatePascal(int q) {
    for (int i = 1; i < (q + 2) / 2; i++)
        pascal[i] = (pascal[q + 1 - i] + pascal[q - i]) % MOD;
    if (q % 2 == 1)
        pascal[(q + 1) / 2] = (2 * pascal[(q + 1) / 2]) % MOD;
    for (int i = 0; i < (q+2)/2; i++)
        pascal[q+1-i] = pascal[i];
}

shlong calculateConstTerm(int q) {
    shlong sum = 0;
    for (int i = 1; i < q+1; i++)
        sum = (sum + i * pascal[i]) % MOD;
    return sum;
}

int main(int argc, char ** argv) {
    char curr;
    shlong last_zero = 0;
    shlong sum = 0;
    shlong i = 0;
    shlong q = 0;
    shlong qthPow = 1;
    shlong lastPow = 1;

    while (cin >> curr) {
        if (curr == '0') {
            sum += ((qthPow * (i - last_zero)) % MOD) - (q*lastPow) % MOD;
            last_zero++;
        }
        if (curr == '?') {
            sum = (2 * sum) % MOD;
            sum += ((qthPow * (i - last_zero)) % MOD) - (q*lastPow) % MOD;
            lastPow = qthPow;
            qthPow = (2 * qthPow) % MOD;
            q++;
        }
        sum = (sum + MOD) % MOD;
        i++;
    }
    cout << sum << endl;
    return 0;
}
