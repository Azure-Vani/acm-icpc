//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const long MAXN = 1024*1024*2+10;

	long Read(void) {
		long r = 0; int ch;
		while( ch = getchar(), !isdigit(ch) );
		r = ch - '0';
		while( ch = getchar(), isdigit(ch) ) r = r * 10 + ch - '0';
		return r;
	}
	void Read_string(char *ch, long l) {
		char t;long b = 0;
		while( t = getchar(), t < 32 || t > 126);
		if(t != '\n') b = 1, ch[0] = t;
		for (long i = b; i < l;){
			t = getchar();
			if( t != '\n' ) ch[i++] = t;
		}
		ch[l] = '\0';
	}
	void Read_word(char *ch) {
		long l = 0; int t;
		while(t = getchar(), !isalpha(t) );
		ch[l++] = t;
		while(t = getchar(), isalpha(t) ) ch[l++] = t;
		ch[l] = '\0';
	}
	struct Node {
		long l, r, p, size; char c;
	}*S; long root = 0, sid = 0;

	struct Tree {
		void Print(long x) {
			if( !x ) return;
			Print(S[x].l);
			putchar(S[x].c);
			Print(S[x].r);
		}
		void RR(long x) {
			long L = S[x].l, F = S[x].p;
			S[x].l = S[L].r, S[ S[x].l ].p = x;
			S[L].r = x, S[x].p = L;
			S[L].p = F;
			if( x == S[F].l )
				S[F].l = L;
			else
				S[F].r = L;
			S[L].size = S[x].size, S[x].size = S[ S[x].l ].size + S[ S[x].r ].size + 1;
		}
		void LL(long x) {
			long R = S[x].r, F = S[x].p;
			S[x].r = S[R].l, S[ S[x].r ].p = x;
			S[R].l = x, S[x].p = R;
			S[R].p = F;
			if( x == S[F].l )
				S[F].l = R;
			else
				S[F].r = R;
			S[R].size = S[x].size, S[x].size = S[ S[x].r ].size + S[ S[x].l ].size + 1;
		}
		void Splay(long x, long G) {
			long F, FF;
			while( (F = S[x].p) != G )
				if( (FF = S[F].p) == G)
					if(x == S[F].l)
						RR(F);
					else
						LL(F);
				else
					if(x == S[F].l)
						if(F == S[FF].l)
							RR(FF), RR(F);
						else
							RR(F), LL(FF);
					else
						if(F == S[FF].l)
							LL(F), RR(FF);
						else
							LL(FF), LL(F);
			if( !G ) root = x;
		}
		long Selete(long k) {
			long t = root, L;
			S[0].size = 0;
			while( k != S[ L = S[t].l ].size + 1 )
				if( k <= S[L].size )
					t = L;
				else
					t = S[t].r, k = k - S[L].size - 1;
			return t;
		}
		long Build(long l, long r, char *ch = NULL) {
			if(l > r) return 0;
			long mid = (l + r) >> 1;
			long x = ++sid;
			S[x].l = Build(l, mid - 1, ch);
			S[x].r = Build(mid + 1, r, ch);
			if(ch) S[x].c = ch[mid];
			S[ S[x].l ].p = S[ S[x].r ].p = x;
			S[x].size = r - l + 1;
			return x;
		}
		void Insert(long k, char *ch) {
			long t = Build(0, strlen(ch) - 1, ch);
			long l = k, r = k + 1;
			Splay( l = Selete(l), 0 );
			Splay( r = Selete(r), l );
			S[r].l = t;
			S[t].p = r;
			S[r].size += strlen(ch), S[l].size += strlen(ch);
		}
		void Delete(long l, long r) {
			long s = r - l + 1;
			Splay( l = Selete(l - 1), 0 );
			Splay( r = Selete(r + 1), l );
			S[r].l = 0;
			S[l].size -= s, S[r].size -= s;
		}
		void Get(long l, long r) {
			Splay( l = Selete(l - 1), 0 );
			Splay( r = Selete(r + 1), l );
			Print( S[r].l );
			puts("");
		}
	}T;
	long V = 1;char *cs;
	void Work(void) {
		S = new Node[MAXN];
		cs = new char[MAXN];
		long Q = Read(); char ch[50];
		root = T.Build(0, 1, "||");
		for (long i = 1; i <= Q; i++) {
			Read_word(ch);
			if(ch[0] == 'M') 
				V = Read(), V++;else 
			if(ch[0] == 'I') {
				long u = Read();
				Read_string(cs, u);
				T.Insert(V, cs);
			}else
			if(ch[0] == 'D') {
				long u = Read();
				T.Delete(V + 1, V + u);
			}else
			if(ch[0] == 'G') {
				long u = Read();
				T.Get(V + 1, V + u);
			}else
			if(ch[0] == 'P') V--;
			else
			if(ch[0] == 'N') V++;
		#ifdef Debug
			//T.Print(root); puts("");
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
