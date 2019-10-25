#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <functional>
#include <set>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;


class Tree {
private:
	struct Node {
		int value;
		Node* rs = nullptr;
		Node* ls = nullptr;
		Node* parent;
		bool isNice = false;
		int level = 0;
		multiset<int> lWays;
		multiset<int> rWays;
		Node(int v, Node* parent = nullptr) :
			value(v), parent(parent) {}
	};

	Node* root;
	using Visitor = function<void(Node*)>;

	void changeChild(Node* now, Node* toSwap) {
		if (toSwap != nullptr)
			toSwap->parent = now->parent;
		if (now->parent == nullptr) {
			root = toSwap;
		}
		else {
			if (now->parent->ls == now) {
				now->parent->ls = toSwap;
			}
			else {
				now->parent->rs = toSwap;
			}
		}
	}

	Node* leftInRight(Node* start) {
		start = start->rs;
		while (start->ls != nullptr) {
			start = start->ls;
		}
		return start;
	}

	Node* rightInLeft(Node* start) {
		start = start->ls;
		while (start->rs != nullptr) {
			start = start->rs;
		}
		return start;
	}

	void traverse(Node* start, Visitor f) {
		if (start) {
			f(start);
			traverse(start->ls, f);
			traverse(start->rs, f);
		}
	}
public:
	using Nodus = Node;
	Tree() : root(nullptr) {}

	Node * getRoot() {
		return root;
	}

	pair<bool, Node*> find(int v) {
		Node* now = root;
		while (now != nullptr) {
			if (v > now->value)
				now = now->rs;
			else {
				if (v < now->value)
					now = now->ls;
				else
					return { true, now };
			}
		}
		return { false, now };
	}

	void insert(int v) {
		if (root == nullptr) {
			root = new Node(v);
			return;
		}
		Node* parent = nullptr;
		Node* now = root;
		while (now != nullptr) {
			parent = now;
			if (v > now->value)
				now = now->rs;
			else {
				if (v < now->value)
					now = now->ls;
				else
					return;
			}
		}
		Node* n = new Node(v, parent);
		if (parent->value < v) parent->rs = n;
		else parent->ls = n;
	}

	void cut(int v) {
		pair<bool, Node*> result = find(v);
		if (!result.first) {
			return;
		}
		Node* now = result.second;
		Node* toSwap = nullptr;
		if (!now->ls && !now->rs) {
			changeChild(now, nullptr);
		}
		else {
			if (now->ls == nullptr && now->rs != nullptr) {
				changeChild(now, now->rs);
				return;
			}
			if (now->rs == nullptr && now->ls != nullptr) {
				changeChild(now, now->ls);
				return;
			}
			Node* left = rightInLeft(now);
			now->value = left->value;
			changeChild(left, left->ls);
		}

	}

	void postverse(Node* start, int k) {
		if (start) {
			if (start->ls == nullptr && start->rs == nullptr) {
				start->rWays.insert(0);
				start->lWays.insert(0);
			}
			else {
				postverse(start->ls, k);
				postverse(start->rs, k);
				if (start->ls) {
					for (int now : start->ls->lWays)
						start->lWays.insert(now + 1);
					for (int now : start->ls->rWays)
						start->lWays.insert(now + 1);
				}
				if (start->rs) {
					for (int now : start->rs->lWays)
						start->rWays.insert(now + 1);
					for (int now : start->rs->rWays)
						start->rWays.insert(now + 1);
				}
				if (!start->rWays.empty()) {
					for (int now : start->lWays) {
						if (now >= k) continue;
						if (start->rWays.find(k - now) != start->rWays.end()) {
							start->isNice = true;
							break;
						}
					}
				}
			}
		}
	}

	pair<bool, int> bfs() {
		queue<Node*> q;
		vector<Node*> ans;
		q.push(root);
		bool flag = true;
		int ourLevel = -1;
		while (!q.empty()) {
			Node* node = q.front();
			q.pop();
			if (node->parent != nullptr) {
				node->level = node->parent->level + 1;
			}
			if (node->isNice && (flag || ourLevel == node->level)) {
				flag = false;
				ourLevel = node->level;
				ans.push_back(node);
			}
			if (flag || node->level <= ourLevel - 1) {
				if (node->ls != nullptr)
					q.push(node->ls);
				if (node->rs != nullptr)
					q.push(node->rs);
			}
		}
		if (ans.size() % 2 == 0) {
			return { false, 0 };
		}
		else {
			return { true, ans[ans.size() / 2]->value };
		}
	}

	void traverse(Visitor f) {
		traverse(root, f);
	}
};

int main() {
	freopen("out.txt", "w", stdout);
	freopen("in.txt", "r", stdin);
	Tree t;
	int key;
	int k;
	cin >> k;
	while (cin >> key) {
		t.insert(key);
	}
	t.postverse(t.getRoot(), k);
	auto res = t.bfs();
	if (res.first) {
		t.cut(res.second);
	}
	t.traverse([](auto x) { cout << x->value << endl; });
}