#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>

namespace Solve {
	const long MAXN = 100050;
	const long long Inf = 1000000000000000000ll;
	typedef long long Long;

	struct Node {
		long l, r, p, size;
		bool rev;
		Long v, t, max;
		inline void Swap(void) {
			long c = l; l = r; r = c;
			rev ^= 1;
		}
		inline void Add(Long u) {
			t += u, v += u, max += u;
		}
		void Print(Long ,bool);
	};
	Node S[MAXN];long root = 0, sid = 0;
	
	void Node::Print(Long o = 0, bool re = 0) {
		long L = l, R = r;
		if( re ) {long c = L; L = R, R = c;}

		if( L ) S[L].Node::Print(o + t, re ^ rev);
		printf("%lld ", v + o);
		if( R ) S[R].Node::Print(o + t, re ^ rev);
	}

	struct Tree {
		void Print(void) {
			S[root].Print();
			puts("");
		}
		void Pass(long x) {
			if( S[x].rev ) {
				S[ S[x].l ].Swap(), S[ S[x].r ].Swap();
				S[x].rev = 0;
			}
			if( S[x].t ) {
				S[ S[x].l ].Add( S[x].t ), S[ S[x].r ].Add( S[x].t );
				S[x].t = 0;
			}
		}
		void Updata(long x) {
			long L = S[x].l, R = S[x].r;
			S[x].max = std::max( S[x].v, std::max(S[ L ].max, S[ R ].max) );
			S[x].size = S[ L ].size + S[ R ].size + 1;
		}
		void RR(long x) {
			long L = S[x].l, F = S[x].p;
			Pass(x), Pass(L);
			
			S[ x ].l = S[ L ].r, S[ S[x].l ].p = x;
			S[ L ].r = x, S[ x ].p = L;
			S[ L ].p = F;
			if( x == S[ F ].l )
				S[ F ].l = L;
			else
				S[ F ].r = L;
			Updata(x), Updata(L);
		}
		void LL(long x) {
			long R = S[x].r, F = S[x].p;
			Pass(x), Pass(R);

			S[ x ].r = S[ R ].l, S[ S[x].r ].p = x;
			S[ R ].l = x, S[ x ].p =R;
			S[ R ].p = F;
			if( x == S[ F ].l )
				S[ F ].l = R;
			else
				S[ F ].r = R;
			Updata(x), Updata(R);
		}
		void Splay(long x, long G) {
			long F, FF;
			while ( (F = S[x].p) != G) {
				if( (FF = S[F].p) == G ) {

					if( x == S[F].l )
						RR( F );
					else
						LL( F );

				}else {
					if( x == S[ F ].l ) {
						if( F == S[ FF ].l ) {
							RR( FF );
							RR( F );
						}else {
							RR( F );
							LL( FF );
						}
					}else{
						if( F == S[ FF ].l) {
							LL( F );
							RR( FF );
						}else {
							LL( FF );
							LL( F );
						}
					}
				}
			}
			if( G == 0 ) root = x;
		}
		long Select(long k, long x) {
			long L = S[x].l;
			if( k == S[L].size + 1) return x;
			Pass( x );
			if( k <= S[L].size) 
				return Select(k, L);
			else
				return Select(k - S[L].size - 1, S[x].r);
		}
		void SetRoot(long _x) {
			root = _x;
		}
		long Build(long l, long r) {
			if( l > r ) return 0;
			long mid = (l + r) >> 1;
			long x = ++sid;
			S[ x ].size = r - l + 1;
			S[ x ].l = Build(l, mid - 1);
			S[ x ].r = Build(mid + 1, r);
			if( S[x].l ) S[ S[x].l ].p = x;
			if( S[x].r ) S[ S[x].r ].p = x;
			return x;
		}
		void Reverse(long l, long r) {
			Splay( l = Select(l - 1, root), 0);
			Splay( r = Select(r + 1, root), l);
			S[ S[r].l ].Swap();
		}
		void Add(long l, long r, Long t) {
			Splay( l = Select(l - 1, root), 0);
			Splay( r = Select(r + 1, root), l);
			S[ S[r].l ].Add(t);
		}
		void Max(long l, long r) {
			Splay( l = Select(l - 1, root), 0);
			Splay( r = Select(r + 1, root), l);
			printf("%lld\n", S[ S[r].l ].max);
		}
	}T;
	
	
	const long MAXN_BUF = 100000 * 100;

	char buf[MAXN_BUF + 1], *pb = buf; long Sign;
	#define Read(t) { \
		(t) = 0; \
		while( !isdigit(*pb) && (*pb) != '-' ) pb++; \
		if( (*(pb)) == '-' ) Sign = -1, pb++;else Sign = 1; \
		while( isdigit(*pb) ) (t) = ((t) << 1) + ((t) << 3) + (*pb) - '0',pb++; \
		(t) *= Sign; \
	}
	void Work(void) {
		long n, m;
		fread(buf, 1, MAXN_BUF, stdin);
		Read(n); 
		Read(m);

		S[1].p = 0; S[0].max = -Inf;
		T.SetRoot( T.Build(0, n + 1) );

		for (long i = 1; i <= m; i++) {
			long flag, l1, l2, u; Read(flag); Read(l1); Read(l2);
			l1++, l2++;
			if( flag == 1 ) {
				Read(u);
				T.Add( l1, l2, u);
			}else
			if( flag == 2) 
				T.Reverse(l1, l2);
			else
			if( flag == 3)
				T.Max(l1, l2);
			#ifdef Debug
				T.Print();
			#endif
		}
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}
