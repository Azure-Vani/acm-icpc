#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
namespace Solve {
        const long MAXN = 60;
        const long inf = 0x6eeeeeee;
 
        struct Edge {
                long y, c, z; Edge *next, *opt;
                Edge(long y, long z, long c, Edge* next) : y(y), z(z), c(c), next(next){}
        }*a[MAXN];
 
        inline void Add(long x, long y, long z, long c) {
                a[x] = new Edge(y, z, c, a[x]);
                a[y] = new Edge(x, 0, -c, a[y]);
                a[x] -> opt = a[y], a[y] -> opt = a[x];
        }
        long vs, vt;
        void Input(void) {
                long n, m, s; scanf("%ld%ld%ld", &n, &m, &s);
                vs = n + 1, vt = n + 2;
                long u[MAXN] = {0}, d[MAXN] = {0};
                for (long i = 1; i <= n; i++) scanf("%ld", u + i);
                for (long i = 1; i <= n; i++) scanf("%ld", d + i);
                for (long i = 1; i <= n; i++) {
                        if(i != n) Add(i, i + 1, s, m);
                        Add(vs, i, inf, d[i]);
                        Add(i, vt, u[i], 0);
                }
        }
        long A = 0, dis[MAXN] = {0};bool vis[MAXN] = {0};
        long Argu(long u, long sum) {
                if( u == vt ) return sum;
                vis[u] = true;
                long r = 0;
                for (Edge* p = a[u]; r < sum && p; p = p -> next) 
                        if( p -> z > 0 && !vis[p -> y] && dis[p -> y] == dis[u] + p -> c) {
                                long t = std::min(sum - r, p -> z);
                                t = Argu(p -> y, t);
                                r += t; p -> z -= t; p -> opt -> z += t; A += (t * p ->c);
                        }
                return r;
        }
        bool Spfa(void) {
                long head = 1, tail = 1; bool hash[MAXN] = {0};
                std::queue<long> Q;
                hash[vs] = true;
                memset(dis, 101, sizeof dis);
                dis[vs] = 0;
                Q.push(vs);
                while( Q.size() ) {
                        long now = Q.front(); Q.pop();
                        for (Edge* p = a[now]; p; p = p -> next)
                                if( p -> z > 0 && dis[p -> y] > dis[now] + p -> c) {
                                        dis[p -> y] = dis[now] + p -> c;
                                        if( !hash[ p -> y ] ) {
                                                hash[p -> y] = true;
                                                Q.push(p -> y);
                                        }
                                }
                        hash[now] = false;
                }
                if( dis[vt] == dis[0] ) return false;
                do {memset(vis, 0, sizeof vis);} while( Argu(vs, inf) );
                return true;
        }
        void Work(void) {
                Input();
                while( Spfa() );
                printf("%ld\n", A);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::Work();
        return 0;
}