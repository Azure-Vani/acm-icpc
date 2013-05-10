#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
namespace Solve {
	typedef long long Int65;
	typedef std::set<int> SII;
	typedef std::vector<int> VII;
	const int MAXN = 100010;

	int factory[MAXN], cnt = 0;

	inline void Divid(int n) {
		for (int i = 2; i * i <= n; i++) if (n % i == 0) {
			factory[++cnt] = i;
			while (n % i == 0) n /= i;
		}
		if (n != 1) factory[++cnt] = n;
	}

	inline int Pow(int a, int n, int c) {
		int r = 1;
		while (n) {if (n&1) r = (Int65) r * a % c; n >>= 1, a = (Int65) a * a % c;}
		return r;
	}

	inline bool Is(int n, int p) {
		for (int i = 1; i <= cnt; i++) {
			if (Pow(n, (p - 1) / factory[i], p) == 1)
				return false;
		}
		return true;
	}

	inline int GetRoot(int p) {
		for (int i = 1;;i++)
			if (Is(i, p))
				return i;
	}

	const int MOD = 1200007;
	struct Edge {
		int value, index; Edge *next;
		Edge(int index, int value, Edge* next):next(next), value(value), index(index){}
	}*e[MOD];

	inline void insert(int index, int value) {
		int t = index % MOD;
		e[t] = new Edge(index, value, e[t]);
	}

	inline VII BabyStep(int a, int b, int c) {
		VII ret;
		int m = (int)sqrt(c) + 1, tmp = 1; a %= c; if (a == 0) return ret;
		insert(1, 0);
		for (int i = 1; i <= m; i++)
			tmp = (Int65) tmp * a % c, insert(tmp, i);
		int gss = b, opp = Pow(tmp, c - 2, c);
		for (int i = 0, d; i <= m; i++) {
			int index = gss % MOD;
			for (Edge *p = e[index]; p; p = p->next) if (p->index == gss)
				ret.push_back(i * m + p->value);
			gss = (Int65) gss * opp % c;
		}
		return ret;
	}

	int p, k, a;

	inline void solve(void) {
		scanf("%d%d%d", &p, &a, &k);
		Divid(p - 1);
		if (p == 2) {
			if (k == 0) printf("%d\n%d\n", 1, 0);
			else printf("%d\n%d\n",1, 1);
			return;
		}
		int g = GetRoot(p);
		int tmp = Pow(g, a, p);
		VII ret = BabyStep(tmp, k, p);
		SII Ans;
		for (VII::iterator it = ret.begin(); it != ret.end(); it++) {
			Ans.insert(Pow(g, *it, p));
		}
		printf("%d\n", Ans.size());
		for (SII::iterator it = Ans.begin(); it != Ans.end(); it++)
			printf("%d\n", *it);
	}
}
int main(void) {
	Solve::solve();
	return 0;
}
