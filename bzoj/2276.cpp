//#define Debug
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <list>
namespace Solve {
	inline int ScanInt(void) {
		int c, r = 0, d;
		while (c = getchar(), c != '-' && !isdigit(c)) {}
		if (c != '-') r = c - '0';
		while (d = getchar(),  isdigit(d)) r = r * 10 + d - '0';
		return c == '-' ? -r : r;
	}

	struct Node {
		int low, pos;
		Node(int low, int pos):low(low), pos(pos){}
	};

	int n;
	std::list<Node> T;

	void solve(void) {
		n = ScanInt();
		T.push_back(Node(ScanInt(), 1)); ScanInt();
		int Ans = 0;
		for (int i = 2; i <= n; i++) {
			int l = ScanInt(), r = ScanInt();
			while (!T.empty() && T.front().low > r) T.pop_front();
			if (!T.empty()) {
				int Now = i - T.front().pos + 1;
				Ans = std::max(Ans, Now);
			}
			int pos = i;
			while (!T.empty() && T.back().low < l) pos = T.back().pos, T.pop_back();
			T.push_back(Node(l, pos));
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
