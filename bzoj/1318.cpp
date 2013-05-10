#include <cstdio>
const int MAXN = 100050;
int n, a[MAXN], vis[MAXN];
int main(int argc, char** argv) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	int Ans = 0;
	for (int i = 1; i <= n; i++) if (a[i] == 1){
		vis[1] = i; int Limit = 0;
		for (int j = i - 1; j >= 1; j--) if (vis[a[j]] != i) {
			vis[a[j]] = i;
		}else break;
		for (int j = i + 1; j <= n; j++) if (vis[a[j]] != i) {
			vis[a[j]] = i;
		}
		while (vis[++Limit] == i) {}
		Ans = Ans > Limit - 1? Ans : Limit - 1;
	}
	printf("%d\n", Ans);
	return 0;
}
