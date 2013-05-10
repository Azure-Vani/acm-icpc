//#define Debug
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 50010;

	int n, Mod, p;

	struct Node {
		int x, y;
		Node(int x, int y):x(x),y(y){}
		inline friend bool operator <(const Node& a, const Node& b) {
			if (a.x != b.x) return a.x < b.x; else return a.y < b.y;
		}
	};
	struct pair {
		int c[3];
		inline Node XX(void) const {return Node(c[1], c[2]);}
		inline friend bool operator <(const pair& a, const pair& b) {
			if (a.c[0] != b.c[0]) return a.c[0] < b.c[0];else
			if (a.c[1] != b.c[1]) return a.c[1] > b.c[1];else
			return a.c[2] > b.c[2];
		}
	}a[MAXN];

	typedef std::set<Node> SII;
	
	inline void Input(void) {
		scanf("%d%d%d", &p, &Mod, &n); int now = p;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 3; j++)
				a[i].c[j] = p, p = (Int64) p * now % Mod;
			std::sort(a[i].c, a[i].c + 3);
		}
		std::sort(a + 1, a + n + 1);
	}
	
	SII T[MAXN];

	inline void Work(void) {
		T[1].insert(a[1].XX());
		int Ans = 1, cnt = 1;
		for (int i = 2; i <= n; i++) {
			int l = 1, r = cnt; Node tmp = a[i].XX();
			while (l <= r) {
				int mid = (l + r) >> 1;
				SII::iterator it = T[mid].lower_bound(tmp);
				if (it == T[mid].begin())
					r = mid - 1;
				else {
					it--;
					if (it->x < tmp.x && it->y < tmp.y)
						l = mid + 1;
					else
						r = mid - 1;
				}
			}
			if (l > cnt) cnt++;
			SII::iterator it = T[l].lower_bound(tmp);
			while (it != T[l].end() && it->y > tmp.y) T[l].erase(it++);
			T[l].insert(tmp);
		}
		printf("%d\n", cnt);
	}

	inline void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
