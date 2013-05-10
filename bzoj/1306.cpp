//#define Debug
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <map>
namespace Solve{
	long n, c[10] = {0}, ans = 0;
	void Input(void) {
		scanf("%ld", &n);
		for (long i = 1; i <= n; i++){
			scanf("%ld",c + i);
			if (c[i] > 3 * n)  {
				puts("0");
				exit(0);
			}
		}
	}
	std::map <unsigned long long,long> Q;
	void Dfs(long l1, long l2) {
		if ( l1 >= n) {
			ans++;
			return;
		}
		
		unsigned long long aim = l1 *10 + l2;long p[10]; memcpy(p,c,sizeof p);
		std::sort(p + 1, p + n + 1);
		for (long i = 1; i <= n; i++) aim = aim * 100 + c[i];

		if( Q.count(aim) ){ ans += Q[aim]; return;}

		long c1 = 0, c2 = 0, w = ans;
		for (long i = 0;i <= 2; i++){
			c1 += i; if(c1 == 1) c2 = 1;else c2 = 3 - c1;

			if( c[l2] - c2 > (n - l1 - 1) * 3 || c[l2] - c2 < 0) continue;
			if( c[l1] - c1 > (n - l2 ) * 3 || c[l1] - c1 < 0) continue;
			
			c[l2] -= c2, c[l1] -= c1;
			Dfs( l2 == n ? l1 + 1 : l1, l2 == n ? l1 + 2 : l2 +1);
			c[l2] += c2, c[l1] += c1;
		}
		
		Q[aim] = ans - w;
	}
	void solve(void) {
		Input();
		Dfs(1,2);
		printf("%ld\n",ans);
	}
}
int main(int argc, char** argv){
	#ifdef Debug
		freopen ("1.in","r",stdin);
	#endif
	Solve::solve();
	return 0;
}