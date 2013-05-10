//#define Debug
#include <cstdio>
#include <cmath>
#include <iostream>
typedef long long Long;
inline Long GetSum(Long a1, Long an, Long d){
	return (a1 + an) * ( (an - a1) / d + 1 ) / 2;
}
int main(int argc,char** argv) {
	Long n, k, i, mid; std::cin >> k >> n; mid = sqrt(n);
	Long ans = 0;
	#ifdef Debug
		for (Long i = 1; i <=k ;i++ )
			ans += n % i;
		std::cout << ans << std::endl;
		ans = 0;
	#endif
	if (k > n) ans += ( (k - n) * n ), k = n;

	for (i = k; i > mid ;){
		Long d = n / i, begin = n % i, end = n % ( n / (d + 1) + 1 );
		ans += GetSum(begin , end , d);
		i = n / (d + 1);
	}

	for (i = 1; i<= std::min(mid, k); i++)
		ans += (n % i);
	
	std::cout << ans << std::endl;
	return 0;
}
