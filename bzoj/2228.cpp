//#define Debug
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
    const int MAXN = 152;
    bool a[MAXN][MAXN][MAXN];
 
    int h, n, m;
    void Input(void) {
        scanf("%d%d%d\n", &n, &m, &h);
        for (int i = 1; i <= m; i++) 
            for (int j = 1; j <= n; j++, getchar()) 
                for (int k = 1; k <= h; k++) 
                    a[k][j][i] = getchar() == 'N';
    }
     
    int f[MAXN][MAXN][MAXN], Ans = 0;
    int L[MAXN], R[MAXN], stack[MAXN], top;
 
    void Cal(int a[], int n) {
        top = 0;stack[0] = 0;
        for (int i = 1; i <= n; i++) {
            while (top && a[stack[top]] >= a[i]) top--;
            L[i] = i - stack[top] - 1;
            stack[++top] = i;
        }
        top = 0; stack[0] = n + 1;
        for (int i = n; i >= 1; i--) {
            while (top && a[stack[top]] >= a[i]) top--;
            R[i] = stack[top] - i - 1;
            stack[++top] = i;
        }
        for (int i = 1; i <= n; i++) {
            assert(L[i] >= 0);
            assert(R[i] >= 0);
            Ans = std::max(Ans, a[i] * (L[i] + R[i] + 1));
        }
    }
 
    void Work(bool a[MAXN][MAXN][MAXN], int p) {
        memset(f, 0, sizeof f);
        int n = Solve::n, m = Solve::m, h = Solve::h;
        if (p == 1) std::swap(n, h);
        if (p == 2) std::swap(m, h);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= h; k++) if (!p ? a[k][i][j] : p == 1 ? a[i][k][j] : a[j][i][k]) {
                    f[i][j][k] = std::min(f[i][j - 1][k], f[i - 1][j][k]);
                    f[i][j][k] = std::min(f[i][j][k], f[i - 1][j - 1][k]);
                    f[i][j][k]++;
                }else f[i][j][k] = 0;
                Cal(f[i][j], h);
            }
    }
 
    bool b[MAXN][MAXN][MAXN];
    void solve(void) {
        Input();
        for (int _ = 0; _ < 3; _++) Work(a, _);
        printf("%d\n", Ans << 2);
    }
}
int main(int argc, char** argv) {
    #ifdef Debug
        freopen("1.in", "r", stdin);
        freopen("1.out", "w", stdout);
    #endif
    Solve::solve();
    return 0;
}