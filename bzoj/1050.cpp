#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>
#include <set>
namespace Solve{
	const long V = 502;
	const long E = 5055;
	const long C = 30055;

	struct Edge {
		long y, z; Edge *next;
		Edge(long y, long z,  Edge *next): y(y), z(z),  next(next){}
	}*a[V];

	long Read(void) {
		long r; int ch;
		while( ch = getchar(), !isdigit(ch) );
		r = ch - '0';
		while( ch = getchar(), isdigit(ch) ) r = (r << 1) + (r << 3) + ch - '0';
		return r;
	}
	
	long n, m, vs, vt, max = 0;
	void Input(void) {
		n = Read(), m = Read();
		for (long i = 1; i <= m; i++){
			long x = Read(), y = Read(), v = Read(); 
			a[x] = new Edge(y, v, a[x]);
			a[y] = new Edge(x, v, a[y]);
		}
		vs = Read(), vt = Read();
	}
	
	long Gcd(long a, long b) {
		if(b)
			return Gcd(b, a % b);
		else
			return a;
	}
	typedef std::pair<long, long> II;
	long f[V][C] = {0}; bool hash[V][E] = {0};
	void Work(void) {
		std::queue<II> Q; Q.push( std::make_pair(vs, 0) );
		
		bool OK = false; long max,min;

		memset(f, -1, sizeof f);f[vs][0] = 0x6eeeeeee;
		while(Q.size()) {
			long now = Q.front().first, c = Q.front().second; Q.pop();
			
			for (Edge *p = a[now]; p; p = p -> next){
				long t = std::max(c, p -> z ), u = p -> y;
				if( f[u][t] < std::min(f[now][c], p -> z) ){
					f[u][t] = std::min(f[now][c], p -> z);
					if(OK)
						if(max * f[u][t] < min * t)
							continue;

					if(!hash[u][t])
						hash[u][t] = true, Q.push( std::make_pair(u, t) );
					
					if( u == vt )
						max = t, min = f[u][t], OK = true;
				}
			}
			hash[now][c] = false;
		}
		if(!OK)
			puts("IMPOSSIBLE");
		else{
			long t = Gcd(max, min);
			if( t == min ) printf("%ld\n", max/t);
				else
					printf("%ld/%ld\n",max/t,min/t);
		}

	}

}
int main(int argc, char **argv) {
	#ifdef Debug
		freopen("1.in","r",stdin);
	#endif
	Solve::Input();
	Solve::Work();
}