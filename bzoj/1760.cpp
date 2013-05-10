//#define Debug
#include <cctype>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
namespace Solve {
        const int MAXN = 100050;
 
        struct Node {
                int x, y, index;
                inline friend bool operator <(const Node& a, const Node& b) {
                        return a.x == b.x ? a.y < b.y : a.x < b.x;
                }
                inline bool operator==(const Node& b) {
                        return x == b.x && y == b.y;
                }
                Node(int x, int y, int index):x(x), y(y), index(index){}
        };
        typedef std::vector<Node> II;
 
        struct Edge {
                int y; Edge *next, *opt; bool flag;
                Edge(int y, Edge *next):y(y), next(next){flag = true;}
        }*a[MAXN];
 
        int n, color[MAXN];
        II T;
 
        inline void AddEdge(int x, int y) {
                a[x] = new Edge(y, a[x]);
                a[y] = new Edge(x, a[y]);
                a[x]->opt = a[y];
                a[y]->opt = a[x];
        }
 
        inline int ScanInt(void) {
                int c, r;
                while (c = getchar(), !isdigit(c)) {}
                r = c - '0';
                while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
                return r;
        }
 
        void Input(void) {
                scanf("%d", &n);n -= 2;
                int tmp[3];
                for (int i = 1; i <= n; i++) {
                        for (int j = 0; j < 3; j++) tmp[j] = ScanInt();
                        std::sort(tmp, tmp + 3);
                        color[i] = ScanInt();
                        for (int l1 = 0; l1 < 2; l1++) for (int l2 = l1 + 1; l2 < 3; l2++)
                                T.push_back(Node(tmp[l1], tmp[l2], i));
                }
        }
 
        void MakeTree (void) {
                std::sort(T.begin(), T.end());
                int N = T.size(), nEdge = 0;;
                for (int i = 1; i < N; i++)
                        if (T[i] == T[i - 1])
                                AddEdge(T[i].index, T[i - 1].index), nEdge++;
                assert(nEdge == n - 1);
        }
 
        int son[MAXN], d[MAXN], belong[MAXN], deep[MAXN], father[MAXN];
        void Prepare(void) {
                int head = 1, tail = 1;
                d[1] = 1;
                while (head <= tail) {
                        int now = d[head++];
                        for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
                                p->opt->flag = false;
                                deep[ d[++tail] = p->y ] = deep[now] + 1;
                                father[p->y] = now;
                        }
                }
                for (int i = tail, t; i >= 1; i--) t = d[i], son[t]++, son[father[t]] += son[t];
                for (int i = 1, t; i <= tail; i++) {
                        int best = 0, tmp = 0, t = d[i];
                        if (!belong[t]) belong[t] = t;
                        for (Edge *p = a[t]; p; p = p->next) if (p->flag && son[p->y] > best)
                                best = son[p->y], tmp = p->y;
                        belong[tmp] = belong[t];
                }
        }
 
        inline int LCA(int a, int b) {
                while (true) {
                        if (deep[a] > deep[b]) std::swap(a, b);
                        if (belong[a] == belong[b]) return a;
                        if (deep[belong[a]] < deep[belong[b]]) b = father[belong[b]];
                        else a = father[belong[a]];
                }
        }
 
        int colorLCA[MAXN];
        inline void GetAllLca(void) {
                for (int i = 1; i <= n; i++) {
                        int c = color[i];
                        if (!colorLCA[c]) colorLCA[c] = i;
                        else colorLCA[c] = LCA(colorLCA[c], i);
                }
        }
 
        int low[MAXN];
        int MainWork(void) {
                int ret = 0;
                for (int i = n; i > 1; i--) {
                        int t = d[i], c = color[t];
                        low[t] = deep[colorLCA[c]];
                        for (Edge *p = a[t]; p; p = p->next) if (p->flag)
                                low[t] = std::min(low[t], low[p->y]);
                        if (deep[t] <= low[t]) ret++;
                }
                return ret;
        }
 
        void solve(void) {
                Input();
                MakeTree();
                Prepare();
                GetAllLca();
                printf("%d\n", MainWork());
        }
}
int main(int argc, char** argv) {
        Solve::solve();
        return 0;
}