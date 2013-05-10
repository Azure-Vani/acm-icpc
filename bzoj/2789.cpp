#include <cstdio>
#include <algorithm>
#include <vector>
const int MAXN = 1000010;
int n; char c1[MAXN], c2[MAXN];
std::vector<int> V[27]; int pos[27], c[MAXN], a[MAXN];
long long Ans = 0;
int main(void) {
	scanf("%d", &n); scanf("%s", c1); scanf("%s", c2);
	for (int i = 0; i < n; i++) V[c2[i] - 'A'].push_back(i+1);
	for (int i = 0; i < n; i++) a[i] = V[c1[i] - 'A'][pos[c1[i] - 'A']++];
	for (int i = 0; i < n; i++) {
		for (int j = (n - a[i] + 1); j; j-=j&-j) Ans += c[j];
		for (int j = (n - a[i] + 1); j <= n; j+=j&-j) c[j]++;
	}
	printf("%lld\n", Ans);
	return 0;
}