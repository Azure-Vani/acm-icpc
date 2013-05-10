#include <iostream>
typedef unsigned long long Int64;
Int64 f[1005];
int main() {
	Int64 n; std::cin >> n;
	f[0] = f[1] = 1; int i;
	for (i = 2;f[i] = f[i - 1] + f[i - 2], f[i] <= n; i++);
	for (--i;n < f[i] || (i >= 1, n -= f[i]); i--);
	std::cout <<f[i]<<std::endl;
	return 0;
}
