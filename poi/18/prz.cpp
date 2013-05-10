#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

namespace Solve {
	const int MAXN = 2012;
	
	pair<int, int> X[4000001], Y[4000001], *Ans = X, *real_Ans = Y;int top1 = 0, top2 = 0;
	int n, a[MAXN], pos[MAXN], begin;

	inline int Getpos(int u) {
		return (begin + pos[u] - 1) % n + 1;
	}
	inline void Move(int t, int u) {
		for (int i = 1; i <= u; i++) {
			if (t >= 3) {
				Ans[++top1] = make_pair(n - (t - 3), 0);
				if (begin > (t - 3)) begin -= (t - 3); else begin += n - (t - 3);
			} else {
				Ans[++top1] = make_pair(3 - t, 0);
				if (begin > (n - (3 - t))) begin -= (n - (3 - t)); else begin += 3 - t;
			}
			Ans[++top1] = make_pair(1, 1);
			if (begin == 1 || begin == 2) begin++; else if (begin == 3) begin = 1;
			t = 1;
		}
	}

	char ch[5];
	inline void Put(int u) {
		register int l = 0;
		while (u) ch[l++] = u % 10 + '0', u /= 10;
		while (--l >= 0) putchar(ch[l]);
	}

	void solve(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {scanf("%d", a + i); if (a[i] == 1) begin = i;}
		if (n == 1) {puts("0");return;}
		if (n == 2) {if (a[1] == 1) puts("0"); else puts("1\n1a");return;}
		for (int i = begin % n + 1, j = 1; i != begin; i = i % n + 1, j++) 
			pos[a[i]] = j;
		for (int i = 2; i <= n - 1; i++) {
			int t = Getpos(i), d = pos[i] - (i - 1);
			if ((d & 1) == 0) {
				Move(t, d / 2);
			} else {
				if (n & 1) {
					if (i == n - 1) {puts("NIE DA SIE");return;}
					else {
						int step = (d + 1) / 2;
						if (pos[i] == n - 1) {
							Move(t, 1); t = 1;
							for (int j = 1; j <= n; j++) {
								if (pos[j] == pos[i] - 1) pos[j]++; else
								if (pos[j] == pos[i] - 2) pos[j]++;
							}
							pos[i] -= 2;
							step--;
						}
						for (int j = 1; j <= n; j++) {
							if (pos[j] == pos[i] + 1) pos[j] -= 2; else
							if (pos[j] == pos[i] - 1) pos[j] += 1;
						}
						pos[i]++;
						Move(t%n+1, 1);
						Move(3, step);
					}
				} else {
					Move(t, n / 2);
					Move(1, d / 2);
				}
			}
			for (int j = 1; j <= n; j++) if (pos[j] >= i - 1 && pos[j] < pos[i]) pos[j]++;
			pos[i] = i - 1;
		}
		if (begin != 1) Ans[++top1] = make_pair(n - begin + 1, 0);

		do {
			if (top2) swap(Ans, real_Ans), top1 = top2;
			top2 = 0;
			for (int it = 1, oth; it <= top1; ((Ans[it].second == 0 && Ans[it].first % n == 0) ? 0 : (real_Ans[++top2] = Ans[it], 0)), it = oth)
				for (int ot = it + 1;;) {
					if (ot > top1) {oth = top1 + 1; break;}
					if (Ans[ot].second == Ans[it].second) {Ans[it].first += Ans[ot].second; ot++;}
					else {oth = ot; break;}
				}
		} while(top1 != top2);

		printf("%d\n", top1);
		for (int i = 1; i < top1; i++) Put(Ans[i].first), putchar(Ans[i].second + 'a'), putchar(' ');
		if (top1) printf("%d%c\n", Ans[top1].first, Ans[top1].second + 'a');
	}
}

int main(void) {
//	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

