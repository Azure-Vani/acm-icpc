//#define Debug
#ifdef unix
	#define LL "%lld"
#else
	#define LL "%I64d"
#endif
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const long MAXN = 1000050;
	typedef long long Long;
	#define abs(x) ((x) > 0 ? (x) :(-(x)))
	long Read(void) {
		long r = 0; int ch;
		while(ch = getchar(), !isdigit(ch)){}
		r = ch - '0';
		while(ch = getchar(), isdigit(ch)) r = r * 10 + ch - '0';
		return r;
	}
	long n;
	struct Node {
		long l, r, key, dis;
		Node():l(0), r(0), key(0), dis(0){}
		inline void Updata(void);
	}S[MAXN];
	long sid = 0, T[MAXN] = {0};
	inline void Node::Updata(void) {
		if (S[l].dis < S[r].dis) std::swap(l, r);
		dis = S[r].dis + 1;
	}
	long Mix(long l1, long l2) {
		if (!l1 || !l2) return l1 + l2;
		if (S[l1].key < S[l2].key) std::swap(l1, l2);
		S[l1].r = Mix(S[l1].r, l2);
		S[l1].Updata();
		return l1;
	}
	long Z[MAXN] = {0};
	void Work(void) {
		long m = 0, n = Read();
		S[0].dis = -1;
		for (long i = 1; i <= n; i++) {
			S[i].key = Read() - i;m++;
			Z[m] = T[m] = i;
			while(m > 1 && S[ T[m] ].key < S[ T[m - 1] ].key) {
				long t = Mix(T[m - 1], T[m]);
				T[--m] = t;
				long length = i - Z[m] + 1;
				if( ((Z[m + 1] - Z[m]) & 1) && ((Z[m] - Z[m - 1]) & 1) )
					T[m] = Mix(S[ T[m] ].l, S[ T[m] ].r);
				Z[m] = Z[m + 1];
			}
		}
		Long A = 0;
		for (long i = 1; i <= m; i++) 
			for (long j = Z[i - 1] + 1; j <= Z[i]; j++)
				A += abs( S[ T[i] ].key - S[j].key);
		printf(LL "\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}
