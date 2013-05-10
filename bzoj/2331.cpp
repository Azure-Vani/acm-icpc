//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXS = 180000;
	const int MAXN = 105;
	const int Mod = 20110520;

	bool map[MAXN][MAXN]; int n, m, Mx, My;
	int pow[19] = {1, 1};
	void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++, scanf("\n"))
			for (int j = 1; j <= m; j++) {
				map[i][j] = getchar() == '_';
				if (map[i][j]) Mx = i, My = j;
			}
		if (n < m) {
			bool tmp[MAXN][MAXN] = {0};
			for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
				tmp[j][i] = map[i][j];
			memcpy(map, tmp, sizeof map);
			std::swap(n, m);
			std::swap(Mx, My);
		}
		for (int i = 2; i <= 15; i++) pow[i] = pow[i - 1] * 3;
	}
	
	int f[2][MAXS];
	int d[2][MAXS], top[2], Sum = 0;
	bool topnow = 0, topnext = 1, now = 0, next = 1;
	
	#define P(S, x) ((S % pow[(x) + 1]) - (S % pow[(x)]))
	#define get(S, x) (P(S, x) / pow[x])
	inline void Add(int &a, int b) {a = a + b; if (a >= Mod) a -= Mod;}
	inline void Push(int S, int Sum) {if (!f[next][S]) d[topnext][++top[topnext]] = S; Add(f[next][S], Sum);}
	inline int Make(int S, int i, int x) {
		S -= P(S, i);
		S += (x * pow[i]);
		return S;
	}
	inline void Renew(int S, int j, int x1, int x2) {
		int Tmp = Make(S, j, x1), Cur = Make(Tmp, j + 1, x2);
		Push(Cur, Sum);
	}

	void Work(void) {
		f[next][0] = 1;
		top[topnext] = 1;

		int Ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				now ^= 1, next ^= 1;
				memset(f[next], 0, sizeof f[next]);
				topnow ^= 1, topnext ^= 1;
				top[topnext] = 0;
				for (int k = 1; k <= top[topnow]; k++) {
					register int Status = d[topnow][k]; Sum = f[now][Status]; if (!Sum) continue;
					register int lt = get(Status, j), up = get(Status, j + 1);
					register int Tmp = 0, Cur = 0;
					if (!map[i][j]) {
						if (lt == 0 && up == 0)
							Renew(Status, j, 0, 0);
						continue;
					}
					if (lt == 0 && up == 0) {
						if (map[i + 1][j] && map[i][j + 1])
							Renew(Status, j, 2, 2);
						if (map[i + 1][j]) 
							Renew(Status, j, 1, 0);
						if (map[i][j + 1]) 
							Renew(Status, j, 0, 1);
					}else
					if (lt == 1 && up == 1) {
						Renew(Status, j, 0, 0);
						if (i == Mx && j == My)
							Add(Ans, Sum);
					}
					else
					if (lt == 1 && up == 0) {
						if (map[i + 1][j])
							Renew(Status, j, 2, 0);
						if (map[i][j + 1])
							Renew(Status, j, 0, 1);
					}else
					if (lt == 0 && up == 1) {
						if (map[i + 1][j])
							Renew(Status, j, 1, 0);
						if (map[i][j + 1])
							Renew(Status, j, 0, 2);
					}else
					if (lt == 2 && up == 0) {
						if (map[i][j + 1])
							Renew(Status, j, 0, 2);
						Renew(Status, j, 0, 0);
						if (i == Mx && j == My)
							Add(Ans, Sum);
					}else
					if (lt == 0 && up == 2) {
						if (map[i + 1][j])
							Renew(Status, j, 2, 0);
						Renew(Status, j, 0, 0);
						if (i == Mx && j == My)
							Add(Ans, Sum);
					}
				}
			}
			next ^= 1, now ^= 1;
			memset(f[next], 0, sizeof f[next]);
			for (int k = 1; k <= top[topnext]; k++) {
				int &t = d[topnext][k];
				Add(f[next][t * 3], f[now][t]);
				t *= 3;
			}
		}
		printf("%d\n", Ans);
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("floor.in", "r", stdin);
		freopen("floor.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
