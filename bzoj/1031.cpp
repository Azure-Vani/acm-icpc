//#define Debug
#include <cstdio>
#include <cstring>
namespace Solve {
        const long MAXN = 200050;
        char C[MAXN] = {'\0'};
        inline void Read(char *ch) {
                long l = 0; char c;
                while (c = getchar(), c != '\n' && c != '\r') ch[l++] = c;
        }
        long S[MAXN] = {0}, Rank[MAXN] = {0}, n;
        long yresult[MAXN] = {0}, xyreseult[MAXN] = {0}, bar[MAXN] = {0};
 
        template <class T>
        void Swap(T &a, T &b) { T c = a; a = b; b = c;}
        inline bool Equal(long *E, long l1, long l2, long delta) {
                return E[l1] == E[l2] && E[l1 + delta] == E[l2 + delta];
        }
        void Make_Array(char *s) {
                long m = 256;
                long *rx = Rank, *ry = yresult, *xy = xyreseult;
                for (long i = 0; i < n; i++) bar[rx[i] = s[i]]++;
                for (long i = 1; i < m; i++) bar[i] += bar[i - 1];
                for (long i = n - 1; i >= 0; i--) S[ --bar[rx[i]] ] = i;
 
                long p, delta;
                for (delta = 1, p = 1; p < n; delta <<= 1, m = p) {
                        p = 0;
                        for (long i = n - delta; i < n; i++) ry[p++] = i;
                        for (long i = 0; i < n; i++)
                                if (S[i] >= delta)
                                        ry[p++] = S[i] - delta;
 
                        for (long i = 0; i < n; i++) xy[i] = rx[ry[i]];
                        memset(bar, 0, sizeof(long) * (m + 1));
                        for (long i = 0; i < n; i++) bar[ xy[i] ]++;
                        for (long i = 1; i < m; i++) bar[i] += bar[i - 1];
                        for (long i = n - 1; i >= 0; i--) S[ --bar[xy[i]] ] = ry[i];
                        
                        Swap(rx, ry);
                        p = 1; rx[ S[0] ] = 0;
                        for (long i = 1; i < n; i++)
                                rx[ S[i] ] = Equal(ry, S[i], S[i - 1], delta) ? p - 1 : p++;
                }
                return;
        }
        void Work(void) {
                long t;
                Read(C);
                t = n = strlen(C);
                for (long i = 0; i < n; i++)
                        C[i + n] = C[i];
                n <<= 1;
                Make_Array(C);
                for (long i = 0, l = 0; l < t; i++)
                        if (S[i] < t)
                                putchar(C[ (S[i] + t - 1) % n ]), l++;
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::Work();
        return 0;
}