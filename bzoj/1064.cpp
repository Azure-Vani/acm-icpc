//#define Debug
#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
long i;
namespace Solve {
        const long MAXN = 105000;
        #define abs(x) ((x)>0?(x):(-(x)))
        long Read(void) {
                long r = 0;int ch;
                while(ch = getchar(), !isdigit(ch)){}
                r = ch - '0';
                while(ch = getchar(), isdigit(ch)) r = r * 10 + ch - '0';
                return r;
        }
        struct Edge {
                long y, z; Edge* next;
                Edge(long y, long z, Edge* next):y(y), z(z), next(next){}
        }*a[MAXN];
 
        long n, m, hash[MAXN] = {0};
        void Input(void) {
                n = Read(), m = Read();
                for (long i = 1; i <= m; i++) {
                        long x = Read(), y = Read();
                        a[x] = new Edge(y, 1, a[x]);
                        a[y] = new Edge(x, -1, a[y]);
                }
        }
 
        long S[MAXN] = {0}, l = 0, F[MAXN] = {0}, MAX[MAXN] = {0}, MIN[MAXN] = {0};
        void Dfs(long u) {
                hash[u] = ::i;
                long t;
                for (Edge* p = a[u]; p; p = p->next)
                        if (!hash[p->y])
                                F[p->y] = F[u] + p->z, Dfs(p->y);
                        else if (hash[p->y] == ::i && (t = abs(F[u] - F[p->y] + p->z))) {
                                S[++l] = t;
                        }
        }
        
        long Gcd(long a, long b) {
                long t;
                while(t = a) {
                        a = b % a, b = t;
                }
                return b;
        }
        void Work(void) {
                for (long i = 1; i <= n; i++)
                        if( !hash[i] )
                                ::i++, Dfs(i);
                if(l) {
                        long A = S[1];
                        for (long i = 2; i <= l; i++)
                                A = Gcd(A, S[i]);
                        if (A < 3)
                                puts("-1 -1");
                        else {
                                printf("%ld", A);
                                long i;
                                for (i = 3; A%i;i++){}
                                printf(" %ld\n", i);
                        }
                }else {
                        memset(MIN, 101, sizeof MIN);
                        memset(MAX, -101, sizeof MAX);
                        for (long i = 1; i <= n; i++) {
                                MAX[ hash[i] ] = std::max(MAX[ hash[i] ], F[i]);
                                MIN[ hash[i] ] = std::min(MIN[ hash[i] ], F[i]);
                        }
                        long A = 0;
                        for (long i = 1; i <= ::i; i++)
                                A += (MAX[i] - MIN[i] + 1);
                        if (A >= 3)
                                printf("%ld 3\n", A);
                        else
                                puts("-1 -1");
                }
        }
        void solve(void) {
                Input();
                Work();
        }
}
int main(int argc, char** argv) {
 
        const long MAXNSTACK = 10000000;
        static int stack[MAXNSTACK * 5], bak;
        __asm__ __volatile__(
                "movl %%esp, %0\n\t"
                "movl %1, %%esp\n\t":
                "=g"(bak):
                "g"(stack + MAXNSTACK * 5 - 1):
        );
 
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::solve();
        
        __asm__ __volatile__(
                "movl %0, %%esp\n\t":
                :
                "g"(bak)
        );
 
        return 0;
}