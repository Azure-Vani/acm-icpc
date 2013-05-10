//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
        const int MAXN = 1005;
        struct Pair {
                int x, y, v;
                inline bool friend operator <(const Pair &a, const Pair &b) {
                        return a.x < b.x;
                }
        }a[MAXN];
 
        int n, x0, f[MAXN][MAXN][2], w[MAXN][MAXN], S = 0;
        void Input(void) {
                scanf("%d%d", &n, &x0);
                for (int i = 1; i <= n; i++) scanf("%d", &a[i].x);
                for (int i = 1; i <= n; i++) scanf("%d", &a[i].y);
                for (int i = 1; i <= n; i++) scanf("%d", &a[i].v), S += a[i].v;
                
                a[++n].x = x0;
                std::sort(a + 1, a + n + 1);
                for (int i = 1; i <= n; i++)
                        for (int j = i; j <= n; j++)
                                w[i][j] = w[i][j - 1] + a[j].v;
                for (int i = 1; i <= n; i++)
                        for (int j = i; j <= n; j++)
                                w[i][j] = S - w[i][j];
        }
        bool vis[MAXN][MAXN];
 
        void Dfs(int l, int r) {
                if (vis[l][r]) return;
                if (l == r) {
                        if (a[l].x == x0) f[l][r][1] = f[l][r][0] = 0; else f[l][r][1] = f[l][r][0] = -0x6eeeeeee;
                        return;
                }
                vis[l][r] = true;
                Dfs(l + 1, r);
                Dfs(l, r - 1);
                f[l][r][0] = a[l].y + std::max(f[l + 1][r][0] - (a[l + 1].x - a[l].x) * w[l + 1][r], 
                                               f[l + 1][r][1] - (a[r].x - a[l].x) * w[l + 1][r]);
                f[l][r][1] = a[r].y + std::max(f[l][r - 1][0] - (a[r].x - a[l].x) * w[l][r - 1], 
                                               f[l][r - 1][1] - (a[r].x - a[r - 1].x) * w[l][r - 1]);
                return;
        }
 
        void solve(void) {
                Input();
                Dfs(1, n);
                printf("%.3lf\n", double(std::max(f[1][n][0], f[1][n][1])) / 1000.0);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::solve();
        return 0;
}