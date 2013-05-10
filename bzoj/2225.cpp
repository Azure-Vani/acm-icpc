//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <set>
namespace Solve {
	const int MAXN = 100050;

	inline int ScanInt(void) {
		int c, r = 0, d;
		while (d = getchar(), !isdigit(d) && d != '-') {}
		if (d != '-') r = d - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return d == '-' ? -r : r;
	}
	struct pair{
		int x, y;
		inline friend bool operator<(const pair& a, const pair& b) {
			if (a.x == b.x) return a.y < b.y; else return a.x < b.x;
		}
		inline void Scan(void) {x = ScanInt(), y = ScanInt();}
	};
	typedef std::set<pair> II;

	int n; II a[MAXN];

	void solve(void) {
		n = ScanInt();
		int len = 0;
		for (int i = 1; i <= n; i++) {
			pair Now;
			Now.Scan();
			int l = 1, r = len;
			while (l <= r) {
				int mid = (l + r) >> 1;
				II::iterator it = a[mid].lower_bound(Now);
				if (it == a[mid].begin())
					r = mid - 1;
				else {
					it--;
					if (it->x < Now.x && it->y < Now.y)
						l = mid + 1;
					else
						r = mid - 1;
				}
			}
			if (l > len) len++;
			II::iterator it = a[l].lower_bound(Now);
			for(;it != a[l].end(); a[l].erase(it++))
				if (Now.y > it->y)
					break;
			a[l].insert(Now);
		}
		printf("%d\n", len);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
