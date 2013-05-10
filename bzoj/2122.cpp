//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <cassert>
namespace Solve {
	const int inf = 1050000000;
	const int MAXN = 50010;
	const int MAXQ = 225;

	inline int ScanInt(void) {
		int c, d, r = 0;
		while (c = getchar(), !isdigit(c) && c != '-') {}
		if (c != '-') r = c - '0';
		while (d = getchar(),  isdigit(d)) r = r * 10 + d - '0';
		return c == '-' ? -r : r;
	}

	int n, m, D[MAXN], L[MAXN];
	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) 
			D[i] = D[i - 1] + ScanInt();
		for (int i = 1; i <= n; i++) L[i] = ScanInt();
	}

	int belong[MAXN];
	struct Node {
		int g, s;
		inline friend bool operator <(const Node& a, const Node& b) {
			if (a.g == b.g) return a.s > b.s; else return a.g > b.g;
		}
	}tmp[MAXN], c[MAXQ + 3][MAXN], LL[MAXQ + 3][MAXQ + 3], RR[MAXQ + 3][MAXQ + 3], tmpL[MAXN], tmpR[MAXN], All[MAXN];
	int f[MAXN], cnt[MAXQ + 3], cntL[MAXQ + 3], cntR[MAXQ + 3];

	void Prepare(void) {
		for (int L = 1, R, now = 1; L <= n; L = R + 1, now++) {
			memset(f, 0, sizeof f);
			R = std::min(L + MAXQ - 1, n);
			int l = 0;
			for (int j = L; j <= R; j++) belong[j] = now;
			for (int i = L; i <= R; i++) {
				tmp[++l].g = f[i] = Solve::L[i];
				tmp[l].s = D[i] - D[i - 1];
				for (int j = i + 1; j <= R; j++) {
					f[j] = std::min(f[j - 1] + D[j] - D[j - 1], Solve::L[j]);
					tmp[++l].g = f[j];
					tmp[l].s = D[j] - D[i - 1];
				}
				if (i == L) {
					for (int j = L; j <= R; j++) {
						tmpL[j - L + 1].g = f[j];
						tmpL[j - L + 1].s = D[j] - D[i - 1];
					}
					All[now].s = D[R] - D[L - 1];
					All[now].g = f[R];
				}
				tmpR[R - i + 1].g = f[R];
				tmpR[R - i + 1].s = D[R] - D[i - 1];
			}
			std::sort(tmp + 1, tmp + 1 + l);
			std::sort(tmpL + 1, tmpL + (R - L + 1) + 1);
			std::sort(tmpR + 1, tmpR + (R - L + 1) + 1);
			cntL[now] = cntR[now] = cnt[now] = 0;
			for (int i = 1, max = -inf; i <= l; i++)
				if (tmp[i].s > max) {
					c[now][++cnt[now]] = tmp[i];
					max = tmp[i].s;
				}
			for (int i = 1, max = -inf; i <= R - L + 1; i++)
				if (tmpL[i].s > max) {
					LL[now][++cntL[now]] = tmpL[i];
					max = tmpL[i].s;
				}
			for (int i = 1, max = -inf; i <= R - L + 1; i++)
				if (tmpR[i].s > max) {
					RR[now][++cntR[now]] = tmpR[i];
					max = tmpR[i].s;
				}
		}
	}

	inline int Binary(Node a[], int x, int n) {
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (a[mid].g >= a[mid].s + x)
				l = mid + 1;
			else
				r = mid - 1;
		}
		return std::max(x, std::max(std::min(a[l].g, a[l].s + x), std::min(a[r].g, a[r].s + x)));
	}

	inline int Gao(int A, int B, int X) {
		int Y = X, ret = X;
		if (belong[A] == belong[A - 1]) {
			int i = A, tmp = X;
			for (; belong[i] == belong[A] && i <= B ; i++) {
				tmp = std::min(tmp + D[i] - D[i - 1], L[i]);
				ret = std::max(ret, tmp);
				tmp = std::max(tmp, X);
			}
			Y = tmp;
			if (i > B) return ret;
			A = i;
		}
		for (int k = belong[A]; k * MAXQ <= B; k++) {
			int t_mid = Binary(c[k], X, cnt[k]);
			int t_L = Binary(LL[k], Y, cntL[k]);
			int t_R = Binary(RR[k], X, cntR[k]);
			ret = std::max(ret, std::max(t_mid, t_L));
			Y = std::max(t_R, std::max(X, std::min(All[k].g, All[k].s + Y)));
		}
		if (belong[B] == belong[B + 1] || B == n) {
			for (int i = (belong[B]  - 1) * MAXQ + 1, tmp = Y; i <= B; i++) {
				tmp = std::min(tmp + D[i] - D[i - 1], L[i]);
				ret = std::max(ret, tmp);
				tmp = std::max(tmp, X);
			}
		}
		return ret;
	}

	void solve(void) {
		Input();
		Prepare();
		for (int i = 1; i <= m; i++) {
			int A = ScanInt(), B = ScanInt(), X = ScanInt();
			int t = Gao(A, B, X);
			printf("%d\n", t);
		}
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
