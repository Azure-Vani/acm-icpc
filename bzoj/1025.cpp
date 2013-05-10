#include <cstdio>
#include <cmath>
#include <cstring>
const long MAXN = 1100;
typedef unsigned long long ull;
long pos[MAXN] = {0};
long n;
bool Check(long u) {
        if (u == 2) return true;
        if (!(u & 1)) return false;
        for (long i = 2; i <= sqrt(u) + 1; i++)
                if (u % i == 0)
                        return false;
        return true;
}
void GetPrime(long limit) {
        for (long i = 2; i <= limit; i++)
                if (Check(i))
                        pos[ ++pos[0] ] = i;
}
ull f[MAXN][MAXN] = {0};
ull Dfs(long p, long x) {
        if (p == pos[0] + 1 && x >= 0) return 1;
        if (f[p][x] != -1) return f[p][x];
        ull& temp = f[p][x]; temp = 0;
        for (ull s = pos[p]; s <= x; s *= pos[p])
                temp += Dfs(p + 1, x - s);
        temp += Dfs(p + 1, x);
        return temp;
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        scanf("%ld", &n);
        GetPrime(n);
        memset(f, -1, sizeof f);
        printf("%I64d\n", Dfs(1, n));
        return 0;
}