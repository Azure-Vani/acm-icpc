//#define Debug
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
namespace Solve {
	const long MAXN = 3006;
	const long MOD = 52427;
	inline long Read(void) {
		long r = 0;int c, p;
		while (c = getchar(), !isdigit(c) && c != '-') {}
		if (c != '-') r = c - '0';
		while (p = getchar(),  isdigit(p)) r = r * 10 + p - '0';
		return c == '-' ? -r : r;
	}
	long a[MAXN], n;
	void Input(void) {
		for (long i = 1; i <= n; i++) a[i] = Read();
	}
	struct pair {
		long st, i, s, L;
		pair(){}
		inline pair(long st, long i, long s, long L):st(st), i(i), s(s), L(L){}
	};
	struct Node {
		pair y; Node *next;
		void* operator new(size_t, void* p){return p;}
	}*aq[MOD], POOL[MAXN * 3],*data = POOL;
	class Hash {
		public:
		inline long Get(long u) {
			return abs(u) % MOD;
		}
		inline pair& Find(long s) {
			long key = Get(s);
			for (Node *p = aq[key]; p; p = p->next)
				if (p->y.s == s) {
					return p->y;
				}
			static pair t(0,0,0,0);t.i = 0;
			return t;
		}
		inline void Ins(pair x) {
			pair& now = Find(x.s);
			if (now.i) {
				if (now.L < x.L || (now.L == x.L && now.st > x.st))
					now = x;
				return;
			}
			long key = Get(x.s);
			Node* o = aq[key];
			aq[key] = data++;
			aq[key]->next = o;
			aq[key]->y = x;
		}
	}T;
	void Work(void) {
		Input();
		long A = 2, vs = 1, vt = 2;
		for (long i = 1; i <= n; i++) {
			memset(aq, 0, sizeof aq);
			data = POOL;
			T.Ins(pair(i + 1, i + 1, a[i] + a[i + 1], 2));
			for (long j = i + 2; j <= n; j++) {
				pair now = T.Find(a[j]);
				if (A < now.L + 1 || (A == now.L + 1 && i < vs) || (A == now.L + 1 && i == vs && now.st < vt)) {
					A = now.L + 1;
					vs = i;
					vt = now.st;
				}
				T.Ins(pair(j, j, a[j] + a[i], 2));
				if (!now.i) continue;
				T.Ins(pair(now.st, j, a[now.i] + a[j], now.L + 1));
			}
		}
		if (A > 2) {
			vs = a[vs], vt = a[vt];
			printf("%ld\n", A);
			printf("%ld %ld", vs, vt);
			long Y;
			for (long i = 3; i <= A; i++)
				printf(" %ld", vs + vt), Y = vs, vs = vt, vt += Y;
			puts("");
		}else puts("0");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	while (~scanf("%ld\n", &Solve::n))
		Solve::Work();
	return 0;
}
