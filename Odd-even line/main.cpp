#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

int n;
vector<vector<int>> graph;
vector<bool> used(false);

vector<int> currComp;

void dfs(int v) {
	used[v] = true;
	currComp.push_back(v);
	for (auto now : graph[v]) {
		if (!used[now]) {
			dfs(now);
		}
	}
}

vector<vector<int>> findComponents() {
	vector<vector<int>> components;
	for (int i = 0; i < n; ++i)
		if (!used[i]) {
			currComp.clear();
			dfs(i);
			components.push_back(currComp);
		}
	return components;
}

pair<bool, size_t> bipartieTest(const vector<int>& component) {
	vector<char> part(n, -1);
	deque<int> q;
	int start = component.front();
	q.push_back(start);
	part[start] = 0;
	unsigned int leftPart = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop_front();
		for (int now : graph[v]) {
			if (part[now] == -1) {
				part[now] = !part[v];
				q.push_front(now);
				if (!part[now]) {
					leftPart++;
				}
			}
			else {
				if (part[now] == part[v]) {
					return { false, 1 };
				}
			}
		}
	}
	return { true, max(leftPart, component.size() - leftPart) };
}

vector<int> getVertexes(const string& toVertex) {
	stringstream sstring = stringstream(toVertex);
	vector<int> retVector;
	int now;
	while (sstring >> now) {
		if (now) {
			retVector.push_back(now - 1);
		}
	}
	return retVector;
}

void readGraph() {
	cin >> n;
	graph.resize(n);
	used.resize(n);
	cin.ignore();

	string now;
	for (int i = 0; i < n; i++) {
		getline(cin, now);
		graph[i] = getVertexes(now);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	readGraph();

	auto components = findComponents();

	if (components.size() == 1 && !bipartieTest(components.front()).first) {
		cout << "YES";
	}
	else {
		size_t answerPower = 0;
		for (const auto& c : components) {
			answerPower += bipartieTest(c).second;
		}
		cout << "NO" << endl;
		cout << answerPower;
	}
	return 0;
}