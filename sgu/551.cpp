#include <cstdio>

using namespace std;

int n, t1, t2;

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &t1, &t2);
	int i = 1, cnt = 0;;
	for (int p1 = 1, p2 = 1; p1 || p2; i++) {
		if (p1 && i % t1 == 0) cnt++;
		if (p2 && i % t2 == 0) cnt++;
		if (p1 && i % t1 == 0 && cnt >= n) p1 = 0;
		if (p2 && i % t2 == 0 && cnt >= n) p2 = 0;
	}
	printf("%d %d\n", cnt , i - 1);
	return 0;
}

