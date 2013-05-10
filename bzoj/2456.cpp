#include <cstdio>
int n, k, t, a;
int main(void) {
	scanf("%d", &n);
	while (n--) scanf("%d", &t),(!k)?(a=t,k=1):(k-=((a!=t)?1:-1));
	printf("%d\n", a);
}