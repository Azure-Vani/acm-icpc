#include <cstdio>
#include <cctype>
#include <set>
#include <map>
#include <algorithm>

#define foreach(i, T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

#pragma GCC optimize("O2")

using namespace std;

const int MAXN = 500010;

struct Node {
	int m, p, r, d, id;
}a[250010], Ans[250010]; int top = 0;

long long D[250010];

inline int ScanInt(void) {
	int c, r = 0, d;
	while (!isdigit(c = getchar()) && c != '-') ;
	if (c != '-') r = c - 48;
	while ( isdigit(d = getchar())) r = r * 10 + d - 48;
	if (c != '-') return r; else return -r;
}

int n, X, Y, P, R, L, C;
bool used[250010];

inline bool cmp(const Node& x, const Node& y) {
	return x.d < y.d;
}

set<long long> S; map<long long, int> M;
set<int> S1; map<int, int> M1;

set<pair<int, int> > c[MAXN];

inline void Cal(int r, int p) {
	for (;r;r-=r&-r) {
		set<pair<int, int> >::iterator it = c[r].begin();
		while (it != c[r].end() && it->first <= p) {
			if (!used[it->second]) {
				Ans[++top].p = a[it->second].p, Ans[top].r = a[it->second].r;
				used[it->second] = true;
			}
			c[r].erase(it++);
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d%d%d%d", &X, &Y, &P, &R, &n);
	S.insert((long long) R * R); S1.insert(P);
	for (int i = 1, x, y; i <= n; i++) {
		scanf("%d%d%d%d%d", &x, &y, &a[i].m, &a[i].p, &a[i].r); a[i].id = i;
		D[i] = (long long)(x - X) * (x - X) + (long long) (y - Y) * (y - Y);
		S.insert(D[i]); S.insert((long long) a[i].r * a[i].r);
		S1.insert(a[i].m); S1.insert(a[i].p);
	}
	foreach(it, S) M[*it] = ++L;
	foreach(it, S1) M1[*it] = ++C; R = M[(long long) R * R]; P = M1[P];
	for (int i = 1; i <= n; i++) {
		a[i].d = M[D[i]], a[i].r = M[(long long)a[i].r * a[i].r];
		a[i].m = M1[a[i].m]; a[i].p = M1[a[i].p];
	}
	for (int i = 1; i <= n; i++) {
		for (int x = a[i].d; x <= L; x+= x&-x)
			c[x].insert(make_pair(a[i].m, a[i].id));
	}
	Ans[0].p = P, Ans[0].r = R;
	for (int i = 0; top <= n && i <= top; i++) {
		Cal(Ans[i].r, Ans[i].p);
	}
	printf("%d\n", top);
	return 0;
}

