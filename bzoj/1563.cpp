//#define Debug
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
namespace Solve {
        const long MAXN = 100050;
        const unsigned long long inf = 1000000000000000000ll;
        typedef unsigned long long ull;
        long L, P, sum[MAXN] = {0}, n;
        long Read(void) {
                #ifdef Debug
                        long r = 0; int c;
                        while (c = getchar(), !isdigit(c)){}
                        r = c - '0';
                        while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
                        return r;
                #else
                        long l = 1;int c;
                        while (c = getchar(), c < 33 || c > 127 || c == '-'){};
                        while (c = getchar(), c >= 33 && c <= 127 && c != '-') l++;
                        return l;
                #endif
        }
        void Input(void) {
                scanf("%ld %ld %ld\n", &n, &L, &P);
                sum[0] = 0;
                for (long i = 1; i <= n; i++) sum[i] = sum[i - 1] + Read();
        }
        inline ull Pow(long u, long k) {
                if (u < 0) u = -u;
                ull r = 1;
                for (long i = 1; i <= k; i++) {
                        r*= u;
                }
                return r;
        }
        
        ull f[MAXN] = {0};
        inline ull GetSum(long l, long r) {
                return f[l] + Pow(sum[r] - sum[l] + r - l - 1 - L , P);
        }
        inline double GetSumDouble(long l, long r) {
                return f[l] + pow( fabs(sum[r] - sum[l] + r - l - 1 - L) , P);
        }
        struct Segment {
                long l, r, d;
        }S[MAXN];
        
        void Work(void) {
                memset(f, 0, sizeof f);
                memset(S, 0, sizeof S);
                Input();
                S[1].l = 1, S[1].r = n, S[1].d = 0;
                long top = 1;
                for (long i = 1; i <= n; i++) {
                        long t;
                        for (t = top; t >= 1 && S[t].l > i; t--){}
                        if (GetSumDouble(S[t].d, i) < inf * 2) {
                                f[i] = GetSum(S[t].d, i);
                                if (f[i] > inf) f[i] = inf + 1;
                        }
                        else
                                f[i] = inf + 1;
                        while (top > 0 && S[top].l > i && GetSumDouble(S[top].d, S[top].l) > GetSumDouble(i, S[top].l))
                                top--;
                        long pos = i + 1;
                        if (top) {
                                long l = std::max(S[top].l, i + 1), r = S[top].r, d = S[top].d;
                                while (l <= r) {
                                        long mid = (l + r) >> 1;
                                        if (GetSumDouble(i, mid) < GetSumDouble(d, mid))
                                                r = mid - 1;
                                        else
                                                l = mid + 1;
                                }
                                pos = l;
                        }
                        if (pos > n) continue;
                        if (S[top].l == pos) top--;
                        else S[top].r = pos - 1;
                        S[++top].l = pos, S[top].r = n, S[top].d = i;
                }
                if (f[n] <= inf) {
                        printf("%I64d\n", f[n]);
                }
                else
                        puts("Too hard to arrange");
                puts("--------------------");
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
                freopen("1.out", "w", stdout);
        #endif
        long T; scanf("%ld", &T);
        while( T-- ) Solve::Work();
        return 0;
}