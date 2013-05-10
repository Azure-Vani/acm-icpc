#include <cstdio>
#include <algorithm>
const int MAXN = 100010;
struct _{int c, index;}lab[MAXN];
int n, f[2][MAXN], rank[2][MAXN], k; bool now, last;
inline bool cmp(const _& a, const _& b) {
	int l = a.index, r = b.index;
	if (rank[last][l] < rank[last][r]) return true;
	else return (rank[last][l] == rank[last][r]) && (rank[last][f[last][l]] < rank[last][f[last][r]]);
}
inline bool Eq(int i, int j) {return rank[last][i] != rank[last][j] || rank[last][f[last][i]] != rank[last][f[last][j]];}
inline bool P(const _& a, const _& b) {
	if (rank[last][a.index] != rank[last][b.index]) return rank[last][a.index] < rank[last][b.index];
	else return a.index < b.index;
}
int main(void) {
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++)
		lab[i].index = i, rank[now = 1][i] = lab[i].c = getchar() - 'a' + 1, getchar();
	for (int i = 1; i <= n; i++)
		scanf("%d", &f[now][i]);
	int p = 0;
	for (k = 1; (1ll << k) <= n; k++) {
		now ^= 1, last ^= 1; p = 0;
		for (int i = 1; i <= n; i++) f[now][i] = f[last][f[last][i]];
		std::stable_sort(lab + 1, lab + n + 1, cmp);
		p = rank[now][lab[1].index] = 1;
		for (int i = 2; i <= n; i++) rank[now][lab[i].index] = (p+=Eq(lab[i].index,lab[i-1].index));
	}
	std::stable_sort(lab + 1, lab + n + 1, P);
	for (int i = 1; i <= n; i++) printf("%d\n", lab[i].index);
	return 0;
}