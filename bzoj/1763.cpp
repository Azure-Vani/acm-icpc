//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
namespace Solve {
        const int MAXN = 100050;
        
        int L, n, a[MAXN];
        void Input(void) {
                scanf("%d%d", &L, &n); L <<= 1;
                for (int i = 1; i <= n; i++) scanf("%d %*c\n", &a[i]);
                std::sort(a + 1, a + n + 1);
        }
        
        void solve(void) {
                Input();
                for (int i = 1; i <= n; i++) if (!(i & 1)) a[i] = L - a[i];
                std::sort(a + 1, a + n + 1);
                long double now = a[1], delta = double(L) / double(n);
                long double max = 0, min = 0x6eeeeeee;
                for (int i = 1; i <= n; i++, now += delta) {
                        max = std::max(a[i] - now, max);
                        min = std::min(a[i] - now, min);
                }
                std::cout.precision(6);
                std::cout << std::fixed << (max - min) / 2.0 << std::endl;
        }
}
int main(int argc, char** argv) {
        Solve::solve();
        return 0;
}