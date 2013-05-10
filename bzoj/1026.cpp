//#define Debug
#include <cstdio>
const long MAXN = 20;
long f[MAXN][MAXN] = {0};
#define abs(x) ((x)<0?(-(x)):(x))

long Work(long n) {
	if( n < 0) return 0;
	long l = 0, temp = n, a[MAXN] = {0};
	while(temp > 0) a[ ++l ] = temp % 10, temp /= 10;

	long r = 0;
	
	for (long i = l - 1; i >= 1; i--)
		for (long j = 1; j <= 9; j++)
			r += f[i][j];
	r++;

	a[l + 1] = 100;
	for (long i = l; i >= 1; i--) {
		for (long j = i == l ? 1 : 0; (i == 1 && j <= a[i]) || j < a[i]; j++)
			if( abs(j - a[i + 1]) >= 2)
				r += f[i][j];
		if(abs(a[i] - a[i + 1]) < 2) break;
	}
	return r;
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif

	for(long i = 0; i <= 9; i++)
		f[1][i] = 1;
	for(long i = 2; i <= 10; i++)
		for (long j = 0; j <= 9; j++)
			for (long k = 0; k <= 9; k++)
				if( abs(k - j) >= 2)
					f[i][j] += f[i - 1][k];
	long l1, l2;
	scanf("%ld %ld", &l1, &l2);
	long A = Work(l2);
	long B = Work(l1 - 1);
	printf("%ld", abs( A - B ));
	return 0;
}
