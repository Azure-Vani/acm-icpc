//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstdlib>

namespace Solve {
	const long MAXN = 100050;
	const long BUF_SIZE = 100 * 100050;
	char buf[BUF_SIZE + 1], *pb = buf;
	#define Read_int(r) {\
		r = 0;\
		while(!isdigit( *pb )) pb++;\
		while(isdigit( *pb) ) r = r * 10 + (*pb) - '0', pb++;\
	}
	
	typedef long long Long;
	Long L[MAXN] = {0}, R[MAXN] = {0}, S[MAXN] = {0}, root = 0, sid = 0; Long K[MAXN] = {0}, M[MAXN] = {0};
	void RR(Long & t) {
		Long k = L[t];L[t] = R[k], R[k] = t;
		S[k] = S[t], S[t] = S[ L[t] ] + S[ R[t] ] + 1;
		M[k] = M[t], M[t] = M[ L[t] ] + M[ R[t] ] + K[t];
		t = k;
	}
	void LL(Long & t) {
		Long k = R[t];R[t] = L[k], L[k] = t;
		S[k] = S[t], S[t] = S[ L[t] ] + S[ R[t] ] + 1;
		M[k] = M[t], M[t] = M[ L[t] ] + M[ R[t] ] + K[t];
		t = k;
	}
	void Maintrain(Long &t) {
		if( S[ R[t] ] < S[ L[L[t]] ]) RR(t), Maintrain( R[t] ), Maintrain(t);else
		if( S[ L[t] ] < S[ R[R[t]] ]) LL(t), Maintrain( L[t] ), Maintrain(t);else
		if( S[ R[t] ] < S[ R[L[t]] ]) LL(L[t]), RR(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);else
		if( S[ L[t] ] < S[ L[R[t]] ]) RR(R[t]), LL(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);
	}
	void Insert(Long& t, Long x) {
		if( !t ) {
			t = ++sid;
			K[t] = M[t] = x;
			S[t] = 1;
			L[t] = R[t] = 0;
			return;
		}
		S[t]++; M[t] += x;
		if( x < K[t] )
			Insert(L[t], x);
		else
			Insert(R[t], x);
		Maintrain(t);
	}
	Long Delete(Long& t, Long x) {
		S[t]--;
		if( (x == K[t]) || ( x < K[t] && L[t] == 0) || ( x > K[t] && R[t] == 0) ) {
			Long r = K[t];
			M[t] -= r;
			if( L[t] == 0 || R[t] == 0) {
				t = L[t] + R[t];
			}else
				K[t] = Delete( L[t], x + 1);
			return r;
		}
		Long r;
		if( x < K[t] )
			r = Delete(L[t], x);
		else
			r = Delete(R[t], x);
		M[t] -= r;
		return r;
	}

	Long Selete(Long t, Long k) {
		if( k == S[t] - S[ R[t] ] ) return K[t];
		if( k <= S[ L[t] ] )
			return Selete(L[t], k);
		else
			return Selete(R[t], k - S[ L[t] ] - 1);
	}

	Long Cal(Long t, Long x) {
		if( !t ) return 0ll;Long l;
		if( x < K[t] )
			l = Cal( L[t], x ) + M[ R[t] ] + K[t] - (S[ R[t] ] + 1ll) * x ;
		else
			l= (S[ L[t] ] + 1ll) * x -M[ L[t] ] - K[t] + Cal( R[t], x );
		return l;
	}
	
	void Work(void) {
		Long n, m; Read_int(n); Read_int(m);
		if( m == 1 ){ puts("0"); exit(0); }
		Long k = m >> 1, a[MAXN] = {0}; k++;

		for (Long i = 1; i <= n; i++) Read_int(a[i]);

		for (Long i = 1; i < m; i++)
			Insert(root, a[i]);

		Long A = 10000000000000000ll;
		for (Long i = m; i <=n; i++){
			Insert(root, a[i]);
			Long t = Selete(root, k);
			A = std::min(A, Cal(root, t) );
			Delete(root, a[ i - m + 1]);
		}

		printf("%I64d\n", A);
	}
}

int main(int argc, char** argv ) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	fread(Solve::buf, 1, Solve::BUF_SIZE, stdin);
	Solve::Work();
	return 0;
}
