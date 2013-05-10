//#define Debug
#include <algorithm>
#include <cctype>
#include <cstdio>
namespace Solve{
	const long V_num = 10550;
	const long E_num = 50550;

	struct Edge {
		long y; Edge* next;
		Edge() {}
		Edge(long y, Edge *next): y(y), next(next) {}
		void* operator new(size_t, void* p) {return p;}
	}*a[V_num], POOL[E_num << 1], *data = POOL, *e[V_num];
	
	long Read(void) {
		long r; int ch;
		while ( ch = getchar(), !isdigit(ch) );
		r = ch - '0';
		while ( ch = getchar(), isdigit(ch) ) r = (r << 1) + (r << 3) + ch - '0';
		return r;
	}
	
	long n;
	void Input(void) {
		n = Read(); long m = Read();
		while( m-- ) {
			long x = Read(), y = Read();
			a[x] = new( (void* ) data++ ) Edge(y, a[x]);
		}
	}
	
	long low[V_num] = {0}, dnf[V_num] = {0}, stack[V_num] = {0}, belong[V_num] = {0}, sum[V_num] = {0}, index = 0, top = 0, num = 0;
	bool in_stack[V_num] = {0};

	void Tarjan(long u) {

		dnf[u] = low[u] = ++index;
		in_stack[ stack[ ++top ] = u ] = true;

		for (Edge *p = a[u]; p; p = p -> next) {
			long t = p -> y;
			if( !dnf[t] ){
				Tarjan(t);
				low[u] = std::min(low[u], low[t]);
			}else if(in_stack[t]) 
				low[u] = std::min(low[u], dnf[t]);
		}

		if(low[u] == dnf[u]) {
			num++;
			long t;
			do{
				t = stack[ top-- ];
				sum[ belong[t] = num ] ++;
				in_stack[t] = false;
			}while(t != u);
		}
	}
	long inp[V_num] = {0}, d[V_num] = {0}, head = 1, tail = 0;
	void Work(void) {
		for (long i = 1; i <= n; i++)
			if( !dnf[i] )
				Tarjan(i);
		for (long i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p -> next){
				long x = belong[i], y = belong[ p -> y ];
				if (x != y) {
					e[x] = new( (void*) data++) Edge(y, e[x]);
					inp[y]++;
				}
			}
		for (long i = 1; i <= num; i++)
			if (!inp[i]) d[++tail] = i;
		while(head <= tail){
			long now = d[head++];
			for (Edge *p = e[now]; p; p = p -> next){
				inp[p -> y]--;
				if( !inp[p -> y] ) d[ ++tail ] = p -> y;
			}
		}
		printf("%ld\n",sum[ d[tail] ]);
	}
	
	void solve(void) {
		Input();
		Work();
	}
}

int main(int argc,char **argv) {
	#ifdef Debug
		freopen("1.in","r",stdin);
	#endif
	Solve::solve();
	return 0;
}
