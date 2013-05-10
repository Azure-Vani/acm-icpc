//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
        const long MAXN = 52;
        long A, B, n; char map[MAXN][MAXN] = {0};
        long f[MAXN] = {0};
        long c1 = 0, c2 = 0, c3 = 0;
        bool E[MAXN][MAXN] = {0};
        long Find(long x) {
                if (f[x] == x) return x;
                else return f[x] = Find(f[x]);
        }
        inline void Mix(long x, long y) {
                if ( (x = Find(x)) != (y = Find(y)))
                        f[x] = f[y];
        }
 
        struct Edge {
                long y; Edge* next;
                Edge(long y, Edge* next):y(y), next(next){}
        }*max[MAXN], *min[MAXN];
        inline void AddEdge(long x, long y) {
                if (E[x][y]) return; else E[x][y] = true;
                min[x] = new Edge(y, min[x]);
                max[y] = new Edge(x, max[y]);
        }
        void Input(void) {
                scanf("%ld %ld %ld\n", &n, &A, &B);
                for (long i = 1; i <= n; i++) f[i] = i;
                for (long i = 1; i <= n; i++, scanf("\n"))
                        for (long j = 1; j <= n; j++) {
                                map[i][j] = getchar(); if (map[i][j] == '=') Mix(i, j);
                        
                        }
                for (long i = 1; i <= n; i++) Find(i);
                for (long i = 1; i <= n; i++)
                        for (long j = 1; j <= n; j++)
                                if (map[i][j] == '+' || map[j][i] == '-')
                                        AddEdge(f[i], f[j]);
                                else if (map[i][j] == '-' || map[j][i] == '+')
                                        AddEdge(f[j], f[i]);
        }
        long W[MAXN] = {0};
        long GetMax(long u) {
                if (W[u]) return W[u];
                long Max = 0;
                for (Edge* p = min[u]; p; p = p->next)
                        Max = std::max(Max, GetMax(p->y));
                return W[u] = Max + 1;
        }
        long GetMin(long u) {
                if (W[u]) return W[u];
                long Min = 4;
                for (Edge* p = max[u]; p; p = p->next)
                        Min = std::min(Min, GetMin(p->y));
                return W[u] = Min - 1;
        }
        void Gao(long a1, long a2, long b1, long b2) {
                a1 = f[a1], b1 = f[b1], a2 = f[a2], b2 = f[b2];
                if (a1 > a2) std::swap(a1, a2);
                if (b1 > b2) std::swap(b1, b2);
                if (a1 == b1 && a2 == b2) {c2++; return;}
                if (a1 == b1) a1 = b1 = n + 1;
                if (a1 == b2) a1 = b2 = n + 1;
                if (a2 == b1) a2 = b1 = n + 1;
                if (a2 == b2) a2 = b2 = n + 1;
 
                bool t1 = false, t2 = false ,t3 = false;
                for (long i = 0; i < 16; i++) {
                        long d = 0;
                        memset(W, 0, sizeof W);
                        if (i & 1) d += GetMax(a1);
                        else d += GetMin(a1);
                        if (i & 2) d += GetMax(a2);
                        else d += GetMin(a2);
                        if (i & 4) d -= GetMax(b1);
                        else d -= GetMin(b1);
                        if (i & 8) d -= GetMax(b2);
                        else d -= GetMin(b2);
                        if (d > 0) if (t2 || t3) return; else t1 = true;
                        if (d== 0) if (t1 || t3) return; else t2 = true;
                        if (d < 0) if (t1 || t2) return; else t3 = true;
                }
                c1 += t1, c2 += t2, c3 += t3;
        }
        void Work(void) {
                Input();
                for (long i = 1; i <= n; i++)
                        for (long j = i + 1; j <= n; j++)
                                if (i != A && i != B && j != A && j != B)
                                        Gao(A, B, i, j);
                printf("%ld %ld %ld\n", c1, c2, c3);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::Work();
        return 0;
}