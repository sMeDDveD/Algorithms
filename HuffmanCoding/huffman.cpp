#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;


long long popTwo(multiset<long long>& l) {
	auto start = l.begin();
	long long first = *(start++);
	long long second = *(start++);
	l.erase(l.begin(), start);
	return first + second;
}

int main() {
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);

	long long n;
	cin >> n;
	multiset<long long> leaves;

	long long now;
	for (long long i = 0; i < n; i++) {
		cin >> now;
		leaves.insert(now);
	}
	long long answer = 0;
	if (leaves.size() == 1) {
		answer += *leaves.begin();
	}
	while (leaves.size() != 1) {
		long long newLeave = popTwo(leaves);
		leaves.insert(newLeave);
		answer += newLeave;
	}

	cout << answer;

	return 0;
}