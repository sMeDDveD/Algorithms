#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>

using namespace std;

class Team {
private:
	int x, y, z;
public:
	Team() = default;
	Team(int aX, int aY, int aZ) : x(aX), y(aY), z(aZ) {}
	bool operator<(const Team& r) {
		return z < r.z;
	}

	int getY() const {
		return y;
	}

	int getX() const {
		return x;
	}
};

class BindexTree {
private:
	vector<int> tree;

	int f(int i) {
		return i & (i + 1);
	}

	int next(int i) {
		return i | (i + 1);
	}

public:
	BindexTree(int size) {
		tree = vector<int>(size, numeric_limits<int>::max());
	}

	int getMin(int R) {
		int result = numeric_limits<int>::max();
		for (int r = R; r >= 0; r = f(r) - 1) {
			result = min(result, tree[r]);
		}
		return result;
	}

	void updateOnPosition(int position, int value) {
		for (int i = position; i < tree.size(); i = next(i)) {
			tree[i] = min(tree[i], value);
		}
	}
};

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n;
	fin >> n;
	int result = n;
	vector<Team> teams(n);
	int x, y, z;
	for (auto& now : teams) {
		fin >> x >> y >> z;
		now = Team(x, y, z);
	}
	sort(teams.begin(), teams.end());
	BindexTree bindexTree(4 * n);	
	for (int i = 0; i < n; i++) {
		auto t = teams[i];
		bindexTree.updateOnPosition(t.getY(), t.getX());
		if (bindexTree.getMin(t.getY()) < t.getX()) result--;
	}
	fout << result;
	return 0;
}