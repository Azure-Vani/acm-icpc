//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
    #ifdef Debug
        typedef long long ull;
        #define LL "%lld"
        const long MAXN = 1000050;
    #else
        typedef long long ull;
        #define LL "%lld"
        const long MAXN = 1000050;
    #endif
    const long long inf = 10000000000LL;
    inline long Read(void) {
        long r = 0;int c;
        while (c = getchar(), !isdigit(c)) {}
        r = c - '0';
        while (c = getchar(),  isdigit(c)) r = (r << 1) + (r << 3) + c - '0';
        return r;
    }
    struct pair {ull c; ull d; pair(){}; pair(ull c, ull d):c(c), d(d){}}Q[MAXN];
    struct Edge {
        long y, z;Edge *next, *opt;bool flag;
        Edge(){}
        Edge(long y, long z, Edge* next):y(y), z(z), next(next){flag = true;}
        void* operator new(size_t, void* p){return p;}
    }*a[MAXN], POOL[MAXN << 1], *data = POOL;
 
    long inp[MAXN] = {0}, n, d[MAXN] = {0}, head = 1, tail = 0;
    void Input(void) {
        n = Read();
        for (long i = 1; i <= n; i++) {
            long y = Read(), z = Read();
            a[i] = new((void*)data++) Edge(y, z, a[i]);
            a[y] = new((void*)data++) Edge(i, z, a[y]);
            a[i]->opt = a[y];
            a[y]->opt = a[i];
            inp[i]++, inp[y]++;
        }
        for (long i = 1; i <= n; i++)
            if (inp[i] == 1) d[++tail] = i, inp[i] = 0;
    }
 
    #define max(a,b) ((a)>(b)?(a):(b))
    ull f[MAXN] = {0}, g[MAXN] = {0}, A = 0;
    long c[MAXN << 1], l; ull s[MAXN << 1];
    inline void Gao(long u) {
        ull T = 0, t = u, sp = 0;
        l = 0;
        while (true) {
            inp[t] = 0;
            c[++l] = t, s[l] = sp;
            T = max(T, g[t]);bool last = true;
            for (Edge* p = a[t]; p; p = p->next)
                if (inp[p->y] > 1) {
                    t = p->y;
                    p->opt->flag = false;
                    sp = p->z;
                    last = false;
                    break;
                }
            if (last) for (Edge* p = a[t]; p; p = p->next) 
                if (p->flag && p->y == u) 
                    {sp = p->z;break;}
            if (last) break;
        }
        for (long i = 1; i <= l; i++)
            s[i] += s[i - 1], c[i + l] = c[i];
        s[l + 1] = sp + s[l];
        for (long i = l + 2; i <= (l << 1); i++)
            s[i] = s[i - 1] + s[i - l] - s[i - l - 1];
        l <<= 1;
 
        head = 1, tail = 0;
        Q[1] = Q[0] = pair(-inf, 0);
        for (long i = 1; i <= l; i++) {
            ull now = c[i], t = f[now] - s[i];
            while (i - Q[head].d >= (l >> 1))
                Q[head] = pair(-inf, 0), head++;
            T = max(T, f[now] + s[i] + Q[head].c);
            while (head <= tail && Q[tail].c <= t)
                Q[tail] = pair(-inf, 0), tail--;
            Q[++tail] = pair(t, i);
        }
        A += T;
    }
    void Work(void) {
        Input();
        while (head <= tail) {
            long now = d[head++];
            for (Edge* p = a[now]; p; p = p->next)
                if (inp[p->y] > 1) {
                    long F = p->y;
                    inp[F]--;
                    if (inp[F] == 1)
                        d[++tail] = F, inp[F] = 0;
                    g[F] = max(max(g[F], g[now]), f[F] + f[now] + p->z);
                    f[F] = max(f[F], f[now] + p->z);
                }
        }
         
        for (long i = 1; i <= n; i++)
            if (inp[i] > 1)
                Gao(i);
        printf(LL "\n", A);
    }
}
int main(int argc, char** argv) {
    #ifdef Debug
        freopen("1.in", "r", stdin);
    #endif
    Solve::Work();
    return 0;
}
