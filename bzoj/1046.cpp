#include <cstdio>
#include <algorithm>
const long MAXN = 10050;
long n, a[MAXN] = {0}, f[MAXN] = {0}, l = 0, hash[MAXN] = {0}, c[MAXN] = {0};

long Find(long u) {
	long l = 1, r = ::l;
	while(l <= r) {
		long mid = (l + r) >> 1;
		if(u < c[mid])
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l;
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	scanf("%ld", &n);
	for (long i = 1; i <= n; i++) scanf("%ld", a + i);
	c[l = 1] = a[n], f[n] = 1;

	for (long i = n - 1; i >= 1; i--) {
		long k = Find(a[i]);
		if( k > l) l++;
		c[k] = a[i];
		f[i] = k;
	}
	for (long i = 1; i <= n; i++)
		hash[ f[i] ] = i;
	
	long Q, u; scanf("%ld", &Q);
	while(~ scanf("%ld", &u) ){
		long t = hash[u];
		if(!t) puts("Impossible");
		else {
			long now = 0;
			for (long i = 1; i <= n; i++)
				if( f[i] >= u && a[i] > now){
					printf("%ld", a[i]);
					u--, now = a[i];
					if( !u ){
						puts("");
						break;
					}
					putchar(' ');
				}
		}
	}
	return 0;
}
