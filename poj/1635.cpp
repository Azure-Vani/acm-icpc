#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define REP(i,l,r) for(int i = l; i <= r; i++)
using namespace std;

const int MAXN = 3003;
typedef unsigned long long Int64;

int base = 3331; Int64 pow[MAXN];

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[2][MAXN];

int father[MAXN], L, n, sum[2][MAXN];Int64 h[2][MAXN]; char ch[MAXN];

inline bool cmp(int x, int y) {return h[x&1][x >> 1] < h[y&1][y >> 1];}
inline int Dfs(int u, int d) {
	vector<int> tmp;
	Int64 &H = h[d][u]; H = 0; int &ret = sum[d][u]; ret = 1;
	for (Edge *p = a[d][u]; p; p = p->next) {
		ret += Dfs(p->y, d);
		tmp.push_back((p->y << 1) + d);
	}
	sort(tmp.begin(), tmp.end(), cmp);
	for (vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it)
		H = H * pow[sum[d][*it >> 1]] + h[d][*it >> 1];
	H = H * base + ret;
	return ret;
}

int main(void) {
	freopen("in", "r", stdin); 
	pow[0] = 1; REP(i, 1, 3000) pow[i] = pow[i - 1] * base;
	int kase; scanf("%d", &kase);
	while (kase--) {
		memset(a, 0, sizeof a); memset(sum, 0, sizeof sum);
		for (int _ = 0; _ < 2; _++) {
			n = 0, L = 1; int now = 1;
			scanf("%s", ch); n = strlen(ch);
			for (int i = 0; i < n; i++) {
				if (ch[i] == '0') a[_][now] = new Edge(++L, a[_][now]), father[L] = now, now = L;
				else now = father[now];
			}
		}
		Dfs(1, 0); 
		Dfs(1, 1);
		puts(h[0][1] == h[1][1] ? "same" : "different");
	}
	return 0;
}

