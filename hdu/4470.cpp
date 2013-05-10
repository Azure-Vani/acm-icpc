#include <cstdio>
#include <algorithm>
#include <cctype>
#define REP(i, l, r) for(int i = l; i <= r; i++)
#define mp make_pair
#define Jump(l, r) {\
	ret += f[l][r].win;\
	if (f[l][r].left) {\
		tmp = Cal(it = (r) - f[l][r].left + 1); ret += tmp.first, it = tmp.second;\
	} else it = succ(r);\
}

using namespace std;
typedef pair<int, int> PII;

const int MAXN = 2012; int n, k, I = -1, J = -1, a[MAXN];
inline int getC(void) {
	int c; while (!isalnum(c = getchar())); 
	return isdigit(c) ? c - 48 : (c == 'A' ? 1 : 10);
}

struct Node {
	int win, left;
	Node():win(0), left(0){}
}f[MAXN][MAXN];

inline int succ(int now) {
	if (now == I - 1) return J + 1;
	else if (now == J) return 1;
	else return now + 1;
}

inline PII Cal(int now, int end = MAXN) {
	int c[2] = {}, num[2] = {};
	REP(i, 0, 3) if (now != end) c[i&1] += a[now], num[i&1]++, now = succ(now);
	REP(i, 0, 1) {
		while (c[i] < 16 && now != end) {
			c[i] += a[now], num[i]++, now = succ(now);
			if (c[i] > 21) return mp(i, now);
			if (num[i] == 5) return mp(i^1, now);
		}
	}
	return c[0] >= 16 && c[1] >= 16 ? mp((int)(c[0] > c[1]), now) : mp(0, end + 2);
}

inline void Process(int l) {
	int i = l;
	while (i <= n) {
		PII tmp = Cal(i, n + 1);
		REP(j, i, tmp.second - 2) f[l][j].win = f[l][i - 1].win, f[l][j].left = j - i + 1;
		f[l][tmp.second - 1].win = f[l][i - 1].win + tmp.first;
		f[l][tmp.second - 1].left = 0;
		i = tmp.second;
	}
}

inline int Make(int l, int r) {
	int ret = 0, it = l, cut = n - k + 2; PII tmp;
	if (cut > r) {
		Jump(l, r);
		if (it < l) Jump(it, l - 1);
		if (it < cut) Jump(it, cut - 1);
	} else if (l - (r - cut + 1) >= 1) {
		cut = l - (r - cut + 1);
		Jump(l, r);
		if (it < cut) Jump(it, cut - 1);
	} else {
		cut = r - (n - cut + 1 - (n - (r - l + 1))) + 1;
		Jump(l, cut - 1);
	}
	return ret;
}

int main(void) {
	int kase = 0;
	while (scanf("%d%d", &n, &k) == 2) {
		I = -1, J = -1;
		REP(i, 1, n) a[i] = getC();
		REP(i, 1, n) Process(i);
		int Ans = 0;
		REP(i, 2, n - 1) REP(j, i, n - 1) { 
			I = i, J = j; int tmp = Make(i, j);
			Ans = max(tmp, Ans);
		}
		printf("Case %d: %d\n", ++kase, Ans);
	}
	return 0;
}

