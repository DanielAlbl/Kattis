#include <iostream>	
#include <vector>
#include <algorithm>

using namespace std;

int Jack[1000000];
int Jill[1000000];

int main() {
	int N, M, temp, count;
	int* bigger;
	int* smaller;
	while (true) {
		count = 0;
		cin >> N;
		cin >> M;
		if (N == 0 && M == 0)
			break;
		for (int i = 0; i < N; i++)
			cin >> Jack[i];
		for (int i = 0; i < M; i++)
			cin >> Jill[i];
		if (N >= M) {
			bigger = Jack;
			smaller = Jill;
		}
		else {
			bigger = Jill;
			smaller = Jack;
			temp = N;
			N = M;
			M = temp;
		}
		for (int i = 0; i < M; i++) {
			if(binary_search(bigger,bigger+N,smaller[i]))
				count++;
		}
		cout << count << endl;
	}


}