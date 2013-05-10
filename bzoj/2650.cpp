#define STDIO
#define INPUT "2364.in"
#define OUTPUT "2364.out"
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
#define round(x) ((Int64)((x) + 0.5))
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
    typedef long long Int64;
    const Int64 MAXN = 1000010;
    const Int64 inf = 1000000000000ll;
    const Int64 INF = (~0ULL) >> 2;
    template <class T>
        inline T abs(T a) {
            return a < 0 ? -a : a;
        }
    inline Int64 ScanInt64(void) {
        Int64 c, r = 0;
        while (!isdigit(c = getchar()));
        r = c - '0';
        while ( isdigit(c = getchar())) r = r * 10ll + c - 48ll;
        return r;
    }
    Int64 n, c, h[MAXN];
    Int64 sum[MAXN], pow_sum[MAXN];
    inline void Input(FILE *fin) {
        n = ScanInt64(), c = ScanInt64();
        for (Int64 i = 2; i <= n + 1; i++)
            h[i] = ScanInt64();
        h[1] = h[n + 2] = inf;
        for (Int64 i = 1; i <= n + 2; i++) {
            sum[i] = sum[i - 1] + h[i];
            pow_sum[i] = pow_sum[i - 1] + h[i] * h[i];
        }
    }
    Int64 f[MAXN];
    Int64 stack[MAXN], top;
    inline Int64 Gao(Int64 a, Int64 b, Int64 c, Int64 minx, Int64 maxx) {
        double div = (double)b / (a * (-2.0));
        Int64 x;
        if (minx <= div && div <= maxx)
            x = round(div);
        if (minx > div)
            x = minx;
        if (maxx < div)
            x = maxx;
        return a * x * x + b * x + c;
    }
    inline Int64 Cal(Int64 l, Int64 r, Int64 minx) {
        if (l + 1 == r) return (l == 1 || r == n + 2) ? 0 : abs(h[r] - h[l]) * c;
        Int64 A, B, C;
        A = r - l - 1, B = -2 * (sum[r - 1] - sum[l]), C = pow_sum[r - 1] - pow_sum[l];
        Int64 maxx = std::min(h[l], h[r]);
        if (l != 1)
            B -= c, C += c * h[l];
        if (r != n + 2)
            B -= c, C += c * h[r];
        return Gao(A, B, C, minx, maxx);
    }
    inline Int64 Work(void) {
        f[1] = 0; stack[top = 1] = 1;
        for (Int64 i = 2; i <= n + 2; i++) {
            f[i] = INF;
            Int64 last = 0;
            while (top && h[stack[top]] < h[i]) {
                f[i] = std::min(f[i], f[stack[top]] + Cal(stack[top], i, last));
                last = h[stack[top--]];
            }
            f[i] = std::min(f[i], f[stack[top]] + Cal(stack[top], i, last));
            stack[++top] = i;
        }
        return f[n + 2];
    }
    inline void solve(FILE *fin, FILE *fout) {
        Input(fin);
        Int64 Ans = Work();
        fprintf(fout, LL "\n", Ans);
    }
}
int main(int argc, char* argv[]) {
#ifdef STDIO
    Solve::solve(stdin, stdout);
#else
    FILE *fin = fopen(INPUT, "r"),
         *fout = fopen(OUTPUT, "w");
    Solve::solve(fin, fout);
    fclose(fin);
    fclose(fout);
#endif
    return 0;
}