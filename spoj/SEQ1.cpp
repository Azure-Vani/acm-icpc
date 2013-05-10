#include <cstdio>
#include <algorithm>
#define REP(i,l,r) for(int = 1; i <= n; i++)

using namespace std;

int L, A0, B0, L0, A1, B1, L1, inf;

/*
 * s[i - L1] - s[i] <= -A1
 * s[i] - s[i - L1] <= B1
 * s[i] - s[i - L0] <= L0 - A0
 * s[i - L0] - s[i] <= B0 - L0
 * s[i] - s[i - 1] <= 1
 * s[i - 1] - s[i] <= 0
 */

int dis[1001][1001];

int main(void) {
	freopen("in", "r", stdin);
	while (scanf("%d%d%d%d%d%d%d", &N, &A0, &B0, &L0, &A1, &B1, &L1) == 7) {
		memset(dis, 42, sizeof dis); inf = dis[0][0];
		REP(i, 1, n) dis[i][i] = 0;
		REP(i, 1, n) {

		}
	}
	return 0;
}

