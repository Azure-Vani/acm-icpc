#include <cstdio>
#include <iostream>
#include <cmath>

typedef unsigned long long Long;
const long MAXN = 55000;

Long d[MAXN] = {0}, sid = 0;
Long ans = 0, max = 0, n;

void Dfs(Long k, Long num, Long now, Long limit) {
	if(num > max) {
		ans = 2147483647ll;
		max = num;
	}
	if(num == max && now < ans) ans = now;
	if( k > sid ) return;
	Long t = now;
	for (long i = 1; i <= limit; i++){
		t *= d[k];
		if( t > n) break;
		Dfs(k + 1, num * (i + 1), t, i);
	}
}
int main(int argc, char **argv) {
	std::cin >>n;
	bool hash[MAXN] = {0};
	for(long i = 2; i <= std::sqrt(n); i++)
		if(!hash[i]){
			d[++sid] = i;
			for (long j = 2; j * i <= std::sqrt(n); j++)
				hash[j * i] = true;
		}
	Dfs(1,1,1,20);
	std::cout <<ans<<std::endl;
	return 0;
}
