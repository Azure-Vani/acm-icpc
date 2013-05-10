//#define Debug
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
namespace Solve {
        typedef long long Int64;
        
        class HASH {public:
                #define Mod 124567
                struct Edge {
                        int value, index; Edge *next;
                        Edge(int index, int value):index(index), value(value){next = NULL;}
                }*a[Mod], *b[Mod];
                void Insert(int index, int value) {
                        int t = index % Mod;
                        Edge *tmp = new Edge(index, value);
                        if (b[t] == NULL)
                                a[t] = b[t] = tmp;
                        else
                                b[t]->next = tmp, b[t] = b[t]->next;
                }
                int Find(int index) {
                        int t = index % Mod;
                        for (Edge *p = a[t]; p; p = p->next) if (p->index == index) return p->value;
                        return -1;
                }
                void clear(void) {
                        memset(a, NULL, sizeof a);
                        memset(b, NULL, sizeof b);
                }
                #undef Mod
        }T;
 
        int Ex_gcd(int a, int b, int& x, int& y) {
                if (!b) {x = 1, y = 0;return a;}
                int r = Ex_gcd(b, a % b, x, y), t;
                t = x, x = y, y = t - a / b * y;
                return r;
        }
        inline int Gao(int a, int b, int c) {
                int x, y;
                int t = Ex_gcd(a, c, x, y);
                x = (Int64) x * b / t % c;
                return x < 0 ? x + c : x;
        }
        int gcd(int a, int b) {return !b?a:gcd(b, a%b);}
        int BabyStep(int a, int b, int c) {
                if (b >= c) return -1;
                int t = 1 % c;
                for (int i = 0; i <= 100; i++) { if (t == b) return i; t = (Int64) t * a % c; }
                int D = 1 % c, delta = 0;
                while ((t = gcd(a, c)) != 1) {
                        if (b % t) return -1;
                        b /= t, c /= t, D = (Int64) D * a / t % c;
                        delta++;
                }
                int m = ceil(sqrt(c)), Pow = 1; T.Insert(Pow, 0);
                for (int i = 1; i <= m; i++)
                        Pow = (Int64) Pow * a % c, T.Insert(Pow, i);
                int opp = Gao(Pow, 1 % c, c), gss = Gao(D, b, c);
                for (int i = 0; i <= m; i++) {
                        int t = T.Find(gss);
                        if (t != -1) return i * m + t + delta;
                        gss = (Int64) gss * opp % c;
                }
                return -1;
        }
        int a, b, c;
        void solve(void) {
                while (scanf("%d%d%d", &a, &c, &b), a != 0) {
                        T.clear();
                        int Ans = BabyStep(a, b, c);
                        if (Ans == -1) puts("No Solution"); else printf("%d\n", Ans);
                }
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        //      freopen("1.out", "w", stdout);
        #endif
        Solve::solve();
        return 0;
}