//#define Debug
#include <cctype>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 202;
	const int MAXM = 20004;

	int l1, l2;

	struct Edge {
		int x, y, a, b;
		inline friend bool operator <(const Edge& a, const Edge& b) {
			return l1 * a.a + l2 * a.b < l1 * b.a + l2 * b.b;
		}
	}E[MAXM];
	
	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar()));
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	int n, m;
	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= m; i++) {
			E[i].x = ScanInt(), E[i].y = ScanInt(), E[i].a = ScanInt(), E[i].b = ScanInt();
		}
	}

	struct Node {
		int x, y;
		inline int XX(void) const {return x * y;}
		inline bool operator <(Node oth) const {
			if (XX() != oth.XX()) return XX() < oth.XX();
			else return x < oth.x;
		}
	}Ans;

	int f[MAXN];
	int Find(int x) {return (x == f[x]) ? x : (f[x] = Find(f[x]));}

	inline Node MST(void) {
		std::sort(E + 1, E + m + 1);
		for (int i = 0; i <= n; i++) f[i] = i;
		int cnt = 0; Node ret; ret.x = ret.y = 0;
		for (int i = 1; i <= m; i++) {
			int t1 = Find(E[i].x), t2 = Find(E[i].y);
			if (t1 == t2) continue;
			cnt++;
			ret.x += E[i].a, ret.y += E[i].b; f[t1] = t2;
			if (cnt == n) return ret;
		}
		return ret;
	}

	void Work(const Node& L, const Node& R) {
		if (L.x == R.x && L.y == R.y) return;
		l1 = R.y - L.y, l2 = L.x - R.x;
		Node tmp = MST();
		Ans = std::min(Ans, tmp);
		if ((tmp.x == L.x && tmp.y == L.y) || (tmp.x == R.x && tmp.y == R.y)) return;
		if ((tmp.x - R.x) * (L.y - R.y) == (tmp.y - R.y) * (L.x - R.x)) return;
		Work(L, tmp);
		Work(tmp, R);
	}

	void solve(void) {
		Input();
		l1 = 0, l2 = 1;
		Node L = MST();
		l1 = 1, l2 = 0;
		Node R = MST();
		Ans = std::min(L, R);
		Work(L, R);
		printf("%d %d\n", Ans.x, Ans.y);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
