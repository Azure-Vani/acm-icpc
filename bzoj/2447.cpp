//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
    const int MAXN = 50050;
    const int MAXH = 100;
 
    int n, w[MAXN], p[MAXN];
    struct Edge {
        int y; Edge *next, *opt; bool flag;
        Edge(int y, Edge *next):y(y), next(next){flag = true;}
    }*a[MAXN];
 
    void Input(void) {
        scanf("%d", &n);
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[x] = new Edge(y, a[x]); a[y] = new Edge(x, a[y]);
            a[x]->opt = a[y]; a[y]->opt = a[x];
        }
        for (int i = 1; i <= n; i++) scanf("%d", w + i);
    }
 
    int level[MAXN], Sum[MAXN], value[MAXN], Max1[MAXN], Max2[MAXN];
    void Dfs(int u) {
        value[u] = w[u];
        for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
            p->opt->flag = false; level[p->y] = level[u] + 1; Solve::p[p->y] = u;
            Dfs(p->y);
            value[u] += value[p->y];
            Sum[u] += Sum[p->y] + value[p->y];
            if (value[p->y] > value[Max1[u]])
                Max2[u] = Max1[u], Max1[u] = p->y;
            else if (value[p->y] > value[Max2[u]])
                Max2[u] = p->y;
        }
    }
 
    int Ans = 1050000000, Now;
 
    inline void Gao(int t, int u, int root) {
        while (true) {
            int tmp = (Max1[t] != u && value[Max1[t]] > value[Max2[t]]) ? Max1[t] : Max2[t];
            if (tmp && tmp != u && (value[tmp] << 1 ) > root) {
                Now -= (value[tmp] << 1) - root;
                t = tmp;
            }else break;
        }
    }
    inline void Work(int u) {
        for (int t = p[u]; t; t = p[t]) value[t] -= value[u];
        Now = Sum[1] - value[u] * level[u];
        Gao(1, u, value[1]);
        Gao(u, u, value[u]);
        Ans = std::min(Ans, Now);
        for (int t = p[u]; t; t = p[t]) value[t] += value[u];
    }
 
    void solve(void) {
        Input();
        Dfs(1);
        for (int i = 2; i <= n; i++)
            Work(i);
        printf("%d\n", Ans);
    }
}
int main(int argc, char** argv) {
    #ifdef Debug
        freopen("1.in", "r", stdin);
    #endif
    Solve::solve();
    return 0;
}