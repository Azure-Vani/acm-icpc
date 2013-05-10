#include <cctype>
#include <list>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 3000010;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}	

	int n, a[MAXN], k;
	void Input(void) {
		k = ScanInt(); n = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
	}

	struct Node {
		int index, value;
		Node(int i, int v):index(v), value(i){}
	};
	
	inline void Work(void) {
		Input();
		std::list<Node> Max;
		std::list<Node> Min;
		int ret = 0, l = 1;
		for (int i = 1; i <= n; i++) {
			int t = a[i];
			while (!Max.empty() && t > Max.back().value) Max.pop_back();
			while (!Min.empty() && t < Min.back().value) Min.pop_back();
			Max.push_back(Node(t, i));
			Min.push_back(Node(t, i));
			if (Max.front().value - Min.front().value > k) {
				ret = std::max(ret, i - l);
				if (Max.front().index == i) {
					while (!Min.empty() && t - Min.front().value > k) l = Min.front().index + 1, Min.pop_front();
				}else {
					while (!Max.empty() && Max.front().value - t > k) l = Max.front().index + 1, Max.pop_front();
				}
			}
			ret = std::max(ret, i - l + 1);
		}
		printf("%d\n", ret);
	}
}
int main(int argc, char** argv) {
	Solve::Work();
	return 0;
}
