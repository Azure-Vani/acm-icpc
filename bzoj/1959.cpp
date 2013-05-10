#include <cstdio>
#include <algorithm>
namespace Solve {
        const int MAXN = 100005;
        struct pair{int x, y;}a[MAXN];
        inline bool cmp(const pair& a, const pair& b) {return a.x > b.x;}
        int n, c[MAXN];
        void solve(void) {
                scanf("%d", &n);
                for (int i = 0; i < n; i++) scanf("%d %d",&a[i].x, &a[i].y);
                std::sort(a, a + n, cmp);
                int L = 1; c[L] = a[0].y;
                for (int i = 1; i < n; i++) {
                        int tmp = std::lower_bound(c + 1, c + L + 1, a[i].y) - c;
                        c[tmp] = a[i].y;
                        if (tmp > L) L = tmp;
                }
                printf("%d\n", L);
        }
}
int main(int argc, char** argv) {
        Solve::solve();
        return 0;
}