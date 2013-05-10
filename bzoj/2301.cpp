#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#define LL "%lld"
const int MAXN = 50001;
int miu[MAXN], Prime[MAXN], l = 0;
int tag[MAXN];
typedef long long int64;
void GetPrime(void) {
    for (int i = 2; i < MAXN; i++) {
        if (!tag[i]) Prime[++l] = i, tag[i] = i;
        for (int j = 1; j <= l && Prime[j] * i < MAXN; j++) {
            tag[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0)
                break;
        }
    }
}
 
inline int Gao(int u) {
    int s = 1;
    while (u != 1) {
        if (tag[u] == tag[u / tag[u]]) return 0;
        u /= tag[u];
        s *= -1;
    }
    return s;
}
 
void GetMiu(void) {
    miu[1] = 1;
    for (int i = 2; i < MAXN; i++) miu[i] += miu[i - 1] + Gao(i);
}
 
namespace Solve {
    int64 Work(int a, int b, int k) {
        int64 ret = 0;
        if (a > b) std::swap(a, b);
        if (!a) return 0;
        a /= k, b /= k;
        int N = a, delta, t;
        for (int i = 1; i <= N; i = delta + 1) {
            delta = std::min(a / (a / i), b / (b / i));
            ret += (long long)(a / i) * (b / i) * (miu[delta] - miu[i - 1]);
        }
        return ret;
    }
 
    inline int ScanInt(void) {
        int c, r;
        while (c = getchar(), !isdigit(c)) {}
        r = c - '0';
        while (c = getchar(),  isdigit(c)) r = (r << 1) + (r << 3) + c - '0';
        return r;
    }
 
    void solve(void) {
        int a = ScanInt(), b = ScanInt(), c = ScanInt(), d = ScanInt(), k = ScanInt();
        int64 l1, l2, l3, l4;
        l1 = Work(a - 1, c - 1, k); l2 = Work(a - 1, d, k); l3 = Work(c - 1, b, k); l4 = Work(b, d, k);
        printf(LL "\n", l4 - l2 - l3 + l1);
    }
}
 
int main(int argc, char** argv) {
    #ifdef STDIO
        freopen("b.in", "r", stdin);
        freopen("b.out", "w" ,stdout);
    #endif
    GetPrime();
    GetMiu();
    int _; scanf("%d", &_);
    while (_--) 
        Solve::solve();
    return 0;
}
 