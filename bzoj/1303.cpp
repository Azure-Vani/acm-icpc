#include <cstdio>
#include <map>
#include <cctype>
const long kMAX = 100000;
long Read(void) {
	long r; int ch;
	while ( ch = getchar(), !isdigit(ch) );
	r = ch - '0';
	while ( ch = getchar(), isdigit(ch) ) r = ( r << 1 ) + ( r << 3 ) + ch - '0';
	return r;
}

int main(int argc,char** argv) {
	long n = Read(), b = Read(), a[kMAX] = {0}, k;
	for (long i = 1; i <= n; i++){
		a[i] = Read();
		if (a[i] < b) a[i] = -1; else
		if (a[i] > b) a[i] = 1; else
		if (a[i] = b) a[i] = 0, k = i;
		a[i] += a[i-1];
	}
	std::map <long, long> hash;
	hash[0]=1;
	long long ans=0;
	for (long  i = 1; i <k ; i++)
		hash[ a[i] ]++;
	for (long i = k; i <=n ; i++)
		ans += hash[ a[i] ];
	printf("%I64d\n", ans);
	return 0;
}
