//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
        const int MAXN = 100050;
        inline int ScanInt(void) {
                int c, r = 0;
                while (c = getchar(), !isdigit(c)) {}
                r = c - '0';
                while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
                return r;
        }
 
        struct Line {
                int l, z; Line *next;
                Line(int l, int z, Line* next):l(l), next(next), z(z){}
        }*a[MAXN];
        struct pair {
                int x, y;
        }c[MAXN];
        bool cmp(const pair& a, const pair& b) {
                return a.x == b. x ? (a.y < b.y) : a.x < b.x;
        }
 
        int Ans, n;
        void Input(void) {
                n = ScanInt();
                for (int _ = 1; _ <= n; _++) c[_].x = ScanInt(), c[_].y = ScanInt();
                std::sort(c + 1, c + n + 1, cmp); c[n + 1].y = -1;
                int Now = 1;
                for (int i = 1; i <= n; i++) {
                        int x = c[i].x ,y = c[i].y;
                        if (x + y >= n) continue;
                        if (c[i + 1].y != y || c[i + 1].x != x) {
                                a[n - y] = new Line(x + 1, std::min(Now, n - x - y), a[n - y]);
                                Now = 1;
                        }else Now++;
                }
        }
 
        int f[MAXN];
        void solve(void) {
                Input();
                for (int i = 1; i <= n; i++) {
                        f[i] = f[i - 1];
                        for (Line *p = a[i]; p; p = p->next)
                                f[i] = std::max(f[i], f[p->l - 1] + p->z);
                }
                Ans = n - f[n];
                printf("%d\n", Ans);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("a.in", "r", stdin);
                freopen("a.out", "w", stdout);
        #endif
        Solve::solve();
        return 0;
}