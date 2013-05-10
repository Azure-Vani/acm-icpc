//#define Debug
#include <cstring>
#include <cstdio>
namespace Solve{
        const long MAXN = 55;
        const long V = MAXN * 7;
        const long inf = 0x6eeeeeee;
        
        struct Edge {
                long y, z;Edge *next, *opt;
                Edge(long y, long z, Edge* next):y(y), z(z), next(next){}
        }*a[V];
        
        inline void Add (long x, long y, long z) {
                a[x] = new Edge(y, z, a[x]);
                a[y] = new Edge(x, 0, a[y]);
                a[x] -> opt = a[y];
                a[y] -> opt = a[x];
        }
        
        long n, k, vs = 0, vt ;
        void Input(void) {
                scanf ("%ld %ld",&n, &k);getchar();
		vt = n * 6 + 1;
                for ( long i = 1; i <= n; i++, scanf("\n") )
                        for ( long j = 1; j <= n; j++ )
                                if (getchar() == 'Y') {
                                        Add (i * 3 - 1, (j + n) * 3 - 1, 1);
                                }else {
                                        Add (i * 3 - 2, (j + n) * 3 - 2, 1);
                                }
                
                for ( long i = 1; i <= n; i++){
                        Add(i * 3, i * 3 - 2, k);
                        Add(i * 3, i * 3 - 1, inf);
                        Add( (i + n) * 3 - 2, (i + n) * 3, k);
                        Add( (i + n) * 3 - 1,  (i + n) * 3, inf);
                        Add( vs, i * 3, 0);
                        Add( (i + n) * 3, vt ,0);
                }
        }
        long level [V] = {0};
        bool Bfs(void) {
                long d[V] = {0}, head = 1, tail = 1;
                d[1] = vs;
                memset( level, -1, sizeof level);
		level[vs] = 0;
                while(head <= tail) {
                        long now = d[head++];
                        for (Edge *p = a[now]; p; p = p -> next)
                                if (p -> z > 0 && level[p -> y] == -1)
                                        level[ d[++tail] = p->y ] = level[now] + 1;
                        }
                return level[vt] != -1;
        }
        
        long Extend(long u, long sum ){
                if( u == vt) return sum;
                long r = 0,  t;
                for (Edge *p = a[u]; p && r<sum; p = p -> next)
                        if (p -> z > 0 && level[p -> y] == level[u] + 1){
                                t = p -> z;
                                if(sum - r < t) t = sum - r;
                                t = Extend(p -> y, t);
                                p -> z -= t, p -> opt -> z += t,r += t;
                        }
                if(!r) level[u] = -1;
                return r;
        }
        long Dinic(void) {
                long r = 0, t;
                while(Bfs()) while( t =  Extend(vs, inf) ) r+=t;
                return r;
        }
        void Work(void) {
                long F = 0;
                for (long i = 1; ; i++){
                        for (Edge *p = a[vs]; p; p = p -> next) p -> z++;
                        for (Edge *p = a[vt]; p; p = p -> next) p -> opt -> z ++;
                        F += Dinic();
                        if (F != i * n) {
                                printf("%ld\n",i-1);
                                break;
                        }
                }
        }
        void solve(void){
                Input();
                Work();
        }
}
int main(int argc,char** argv){
        #ifdef Debug
                freopen ( "1.in", "r", stdin);
        #endif
        Solve::solve();
        return 0;
}