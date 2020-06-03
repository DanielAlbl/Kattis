#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
    int val;
    int id;
    bool v;
    bool tail;

    bool operator<(const Point & rhs) const {
        return id < rhs.id;
    }
};

bool compareVal(const Point & a, const Point & b) {
    if (a.val == b.val)
        return a.tail < b.tail;
    return a.val < b.val;
}

Point list[400000];

int main() {
    int size, temp;
    char orr;
    cin >> size;
    size *= 2;
    for (int i = 0; i < size; i+=2) {
        list[i].id = i / 2;
        list[i + 1].id = i / 2;
        list[i].tail = true;
        list[i + 1].tail = false;
        cin >> orr;
        if (orr == 'v') {
            list[i].v = true;
            list[i + 1].v = true;
        } else {
            list[i].v = false;
            list[i + 1].v = false;
        }
        cin >> temp;
        list[i].val = temp;
        list[i + 1].val = temp;
        cin >> temp;
        list[i + 1].val += temp;
        cin >> temp;
        list[i].val -= temp;
        list[i + 1].val -= temp;
    }

    std::sort(list, list + size, compareVal);

    long long count = 0, v = 0, h = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].tail) {
            if (list[i].v) {
                v++;
                count += h;
            } else {
                h++;
                count += v;
            }
        } else {
            if (list[i].v)
                v--;
            else
                h--;
        }
    }

    cout << count << endl;

    return 0;
}