//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 1005;
	const int MAXS = 270;
	
	int n, a[MAXN], b[MAXN];
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
	}
	
	inline void Min(int &a, int b) {
		a = std::min(a, b);
	}
	
	#define __(x) ((x) + 8)
	int f[MAXN][MAXS][16];
	int Work(void) {
		memset(f, 101, sizeof f);
		int inf = f[0][0][0];
		
		f[1][0][__(-1)] = 0;
		for (int i = 1; i <= n; i++) {
			for (int state = 0; state < (1 << 8); state++) {
				for (int k = -8; k <= 7; k++) if (f[i][state][__(k)] < inf && i + k >= 0 && i + k <= n) {
					if (state & 1) {
						Min(f[i + 1][state >> 1][__(k - 1)], f[i][state][__(k)]);
					}  else {
						int Max_Anger = inf;
						for (int l = 0; l <= b[i] && i + l <= n; l++)
							if ((state & (1 << l)) == 0) {
								Min(Max_Anger, i + l + b[i + l]);
								if (i + l > Max_Anger) break;
								Min(f[i][state | (1 << l)][__(l)], f[i][state][__(k)] + (i + k == 0 ? 0 : a[i + k] ^ a[i + l]));
							}
						}
					}
				}
			}

		int A = inf;
		for (int i = -8; i <= 0; i++)
			Min(A, f[n][1][__(i)]);
		return A;
	}
	
	void solve(void) {
		Input();
		printf("%d\n", Work());
	}

}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	
	int _; scanf("%d", &_);
	while (_--)
		Solve::solve();
	return 0;
}
