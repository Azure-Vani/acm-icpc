#include <cstdio>
#include <algorithm>
namespace Solve{
	const long MAXN = 200000;
	const long Inf = 0x6EEEEEEE;

	long S[MAXN] = {0}, R[MAXN] = {0}, L[MAXN] = {0}, K[MAXN] = {0}, sid = 0, root = 0;
	void RR(long &t) {
		long k = L[t]; L[t] = R[k], R[k] = t;
		S[k] = S[t], S[t] = S[ L[t] ] + S[ R[t] ] + 1;
		t = k;
	}
	void LL(long &t) {
		long k = R[t]; R[t] = L[k], L[k] = t;
		S[k] = S[t], S[t] = S[ L[t] ] + S[ R[t] ] + 1;
		t = k;
	}
	void Maintrain(long &t) {
		if(S[L[t]] < S[R[R[t]]]) LL(t), Maintrain(L[t]), Maintrain(t); else
		if(S[R[t]] < S[L[L[t]]]) RR(t), Maintrain(R[t]), Maintrain(t); else
		if(S[L[t]] < S[L[R[t]]]) RR(R[t]), LL(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);else
		if(S[R[t]] < S[R[L[t]]]) LL(L[t]), RR(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);
	}
	void Insert(long &t, long x) {
		if(!t) {
			t = ++sid;
			S[t] = 1;
			K[t] = x;
			return;
		}
		S[t]++;
		if(x < K[t])
			Insert(L[t], x);
		else
			Insert(R[t], x);
		Maintrain(t);
	}
	
	long Succ(long t, long x) {
		if(!t) return Inf;
		if(x > K[t]) 
			return Succ(R[t], x);
		else{
			long r = Succ(L[t],x);
			if(r != Inf) return r; else return K[t];
		}
	}
	long Prev(long t, long x) {
		if(!t) return Inf;
		if(x < K[t])
			return Prev(L[t], x);
		else{
			long r = Prev(R[t], x);
			if(r != Inf) return r; else return K[t];
		}
	}
	
	inline long abs(long x){ return ((x)<0?(-(x)):(x)); }
	void Work(void) {
		long Q, u; long long ans = 0;
		scanf("%ld%ld", &Q,&u);	ans += abs(u);
		Insert(root, u);

		for (long i = 1; i < Q; i++, u = 0) {
			scanf("%ld",&u);
			long l1 = Succ(root, u), l2 = Prev(root, u);
			ans += std::min(abs(l1 - u),abs(l2 - u));
			Insert(root, u);
		}
		printf("%I64d\n", ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in","r",stdin);
	#endif
	Solve::Work();
	return 0;
}
