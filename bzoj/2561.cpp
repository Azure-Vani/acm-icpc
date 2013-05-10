//#define FILEIO
#define INPUT "in"
#define OUTPUT "out"
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))
namespace Solve {
    const int MAXN = 20010;
    const int inf = 0x7fffffff;
    struct Edge {
        int y, f, c; Edge *next, *opt;
        Edge(int y, int f, int c, Edge *next):y(y), f(f), c(c), next(next){}
        Edge(){}
        inline void* operator new(size_t, void* p) {return p;}
    }*a[MAXN], *e[MAXN], M[800009], *data = M;
    
    int ScanInt(void) {
        int c, r = 0, d;
        while (!isdigit(c = getchar()) && c != '-');
        if (c != '-') r = c - '0';
        while ( isdigit(d = getchar())) r = r * 10 + d - '0';
        return c=='-'?-r:r;
    }
    inline void Add(int x, int y, int c) {
        a[x] = new((void*)data++) Edge(y, 1, c, a[x]);
        a[y] = new((void*)data++) Edge(x, 0, c, a[y]);
        a[x]->opt = a[y];
        a[y]->opt = a[x];
    }
    int n, m, vs, vt, L;
    inline void Input(void) {
        n = ScanInt(), m = ScanInt();
        rep(i,1,m) {
            int x = ScanInt(), y = ScanInt(), z = ScanInt();
            Add(x, y, z);
            Add(y, x, z);
        }
        vs = ScanInt(), vt = ScanInt(), L = ScanInt();
    }
    bool (*check)(int);
    int level[MAXN], d[MAXN];
    inline bool Bfs(void) {
        memset(level, -1, sizeof level);
        d[1] = vs; level[vs] = 0;
        int head = 1, tail = 1;
        while (head <= tail) {
            int now = d[head++];
            e[now] = a[now];
            for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && check(p->c) && level[p->y] == -1)
                level[d[++tail] = p->y] = level[now] + 1;
        }
        return level[vt] != -1;
    }
    inline int Extend(int u, int sum) {
        if (u == vt) return sum;
        int r = 0, t;
        for (Edge *p = e[u]; p && r < sum; p = p->next) if (check(p->c) && level[p->y] == level[u] + 1 && p->f > 0) {
            t = std::min(sum - r, p->f);
            t = Extend(p->y, t);
            p->f -= t, p->opt->f += t, r += t;
            e[u] = p;
        }
        if (!r) level[u] = -1;
        return r;
    }
    inline int Dinic(void) {
        int r = 0, t;
        while (Bfs()) {
            while ((t = Extend(vs, inf))) r += t;
        }
        return r;
    }
    bool le(int u) {
        return u < L;
    }
    bool ge(int u) {
        return u > L;
    }
    inline int Work(void) {
        int r = 0;
        check = le;
        r += Dinic();
        check = ge;
        r += Dinic();
        return r;
    }
    void solve(void) {
        Input();
        printf("%d\n",Work());
    }
}
int main(int argc, char* argv[]) {
    #ifdef FILEIO
        freopen(INPUT, "r", stdin);
        freopen(OUTPUT, "w", stdout);
    #endif
    Solve::solve();
    return 0;
}