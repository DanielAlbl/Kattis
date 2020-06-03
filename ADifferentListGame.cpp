#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

typedef long long shlong;
typedef pair<shlong, shlong> pare;
typedef set<shlong>::iterator it;

set<shlong> factors;
unordered_set<shlong> primes;

map<pare, int> mx;

inline void getSome(shlong &N) {
    shlong n = N;

    for (shlong i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            primes.insert(i);
            n /= i;
        }
        while (n % i == 0)
            n /= i;
    }
    if(n != 1)
        primes.insert(n);

    for (auto i : primes)
        N /= i;

    shlong sqrt = shlong(sqrtl((long double)N));

    for (shlong i = 1; i < sqrt; i++) {
        if (N % i == 0) {
            shlong div = N / i;
            if (primes.find(i) == primes.end() && primes.find(div) == primes.end()) {
                factors.insert(i);
                factors.insert(N / i);
            }
        }
    }
}

int DP(it d, shlong x) {
    auto pair = make_pair((*d), x);
    // use solution if already found
    if (mx.find(pair) != mx.end())
        return mx[pair];
    if (x == 1)
        return 0;
    if (d == factors.begin())
        return -1;
    if (factors.find(x) == factors.end())
        return -1;

    // factors larger than x are irrelevent
    if (*d > x)
        return DP(factors.find(x), x);

    it p = prev(d);

    int ans = max(DP(p, x), 1 + DP(p, x / (*d)));
    // if both calls returned -1, return -1
    if (ans == 0)
        ans = -1;
    // store solution
    mx[make_pair(*d, x)] = ans;
    return ans;
}

int main() {
    shlong N;
    shlong count;
    shlong dp = 0;

    cin >> N;

    getSome(N);

    count = primes.size();

    if (factors.empty()) {
        if (N != 1 && primes.find(N) == primes.end())
            count++;
    } else {
        dp = DP(prev(factors.end()), N);
        if (dp == -1)
            dp = 0;
    }

    cout << count + dp << endl;

    return 0;
}
