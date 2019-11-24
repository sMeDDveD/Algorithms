#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

using ll = long long;

struct edges {
	int to;
	ll w;
};

int main() {
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);
	int n, m;
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	vector<vector<edges>> lists(n);
	vector<ll> dest(n, numeric_limits<ll>::max());
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> p;
	vector<bool> used(n, false);

	int u, v, w;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		lists[u - 1].push_back({ v - 1, w });
		lists[v - 1].push_back({ u - 1, w });
	}

	int start = 0;
	int end = n - 1;
	dest[start] = 0;
	p.push({ dest[start], start });


	while (!p.empty()) {
		int vertex = p.top().second;
		ll d = p.top().first;
		p.pop();
		used[vertex] = true;
		if (d > dest[vertex])  continue;

		for (const auto& now : lists[vertex]) {
			if (dest[now.to] > dest[vertex] + now.w) {
				dest[now.to] = dest[vertex] + now.w;
				p.push({ dest[now.to], now.to });
			}
		}
		if (used[end]) break;
	}
	cout << dest[end];
	return 0;
}