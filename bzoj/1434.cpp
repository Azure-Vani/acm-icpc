#include <cstdio>
#include <cmath>
#include <cstring>
namespace Solve {
        const long MAXN = 202;
        long n, m;bool S[MAXN];char ch[MAXN];
        #define Lowbit(x) ((x)&(-(x)))
        inline long sg(long x, long y) {
                if (x == 0 || y == 0)
                        return long( log(Lowbit(x + y + 1)) / log(2) + 0.5);
                else return x + y;
        }
        inline void Work(void) {
                memset(S, 0, sizeof S);
                scanf("%ld %ld\n", &n, &m);
                for (long i = 0; i < n; i++) {
                        gets(ch);
                        for (long j = 0; j < m; j++)
                                if (ch[j] == 'T')
                                        S[sg(i, j)] ^= 1;
                }
                bool A = false;
                for (long i = 0; i < (n + m) && !A; i++) A |= S[i];
                puts(A?"-_-":"=_=");
        }
}
int main(int argc, char** argv) {
        long _;scanf("%ld", &_);
        while (_--)
                Solve::Work();
        return 0;
}
 