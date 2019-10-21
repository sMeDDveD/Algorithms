#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>


using namespace std;

struct text {
	int position;
	int symbol;
	bool operator<(const text& rs) {
		return symbol < rs.symbol;
	}
	bool operator<(int rs) {
		return symbol < rs;
	}
};

int binary_search(text* arr, size_t n, int key) {
	int start = 0;
	int end = n - 1;
	int mid;
	while (start <= end) {
		mid = (start + end) / 2;
		if (key == arr[mid].symbol) {
			return mid;
		}
		else {
			if (key < arr[mid].symbol) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
	}
	return -1;
}

int main() {
	freopen("..\\input.txt", "r", stdin);
	freopen("..\\output.txt", "w", stdout);

	int n, m, now;
	cin >> n >> m;

	text* A = new text[n];
	for (int i = 0; i < n; i++) {
		cin >> now;
		A[i] = { i, now };
	}
	sort(A, A + n);

	int* inter = new int[m];
	size_t rs = 0;
	for (int i = 0; i < m; i++) {
		cin >> now;
		int place = binary_search(A, n, now);
		if (place != -1) {
			inter[rs++] = A[place].position;
		}
	}

	int* result = new int[rs + 1];
	result[0] = -1;
	fill_n(result + 1, rs, INT_MAX);

	int max = 0;
	for (int i = 0; i < rs; i++) {
		int to_insert = static_cast<int>(upper_bound(result, result + rs + 1, inter[i]) - result);
		result[to_insert] = inter[i];
		if (to_insert > max) max = to_insert;
	}
	cout << max << endl;
	return 0;
}