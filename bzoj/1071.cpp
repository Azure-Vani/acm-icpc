//#define STDIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

#define rep(i,l,r) for(int i = l; i <= r; i++)

namespace Solve {
	const int MAXN = 50010;

	struct pair {
		int x, y, index;
	}a[MAXN], c[MAXN];
	int n, A, B, C;
	
	inline bool cmp(const pair& a, const pair& b) {
		return a.x * A + B * a.y < b.x * A + B * b.y;
	}
	inline bool cmp_y(const pair& a, const pair& b) {
		return a.y < b.y;
	}

	inline int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	int Ans = 0; bool In[MAXN];

#define P(x,y) (A*(x)+B*(y))

	inline void Work(int u) {
		int tmp = 0, low = -1, pos = 1;
		memset(In, 0, sizeof In);
		rep(i,1,n) {
			if (c[i].y == low) {
				tmp -= In[c[i].index];
				In[c[i].index] = false;
				continue;
			}
			low = c[i].y;
			while (pos <= n && P(a[pos].x, a[pos].y) - P(c[u].x, low) <= C) {
				if (a[pos].x < c[u].x || a[pos].y < low) {pos++; continue;}
				tmp += !In[a[pos].index];
				In[a[pos].index] = true;
				pos++;
			}
			Ans = std::max(Ans, tmp);
			tmp -= In[c[i].index];
			In[c[i].index] = false;
		}
	}

	void solve(void) {
		n = ScanInt(), A = ScanInt(), B = ScanInt(), C = ScanInt();
		rep(i,1,n) a[i].x = ScanInt(), a[i].y = ScanInt(), a[i].index = i, c[i] = a[i];
		std::sort(a + 1, a + n + 1, cmp);
		std::sort(c + 1, c + n + 1, cmp_y);
		rep(i,1,std::min(2000,n)) 
			Work(i);
		printf("%d\n", Ans);
	}
}

int main(int argc, char* argv[]) {
	#ifdef STDIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}