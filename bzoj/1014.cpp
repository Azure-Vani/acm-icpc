//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
namespace Solve {
        const long MAXN = 200050;
        const long seed = 13331;
        typedef unsigned long long ull;
 
        inline char ReadChar(void) {
                char r;
                while (r = getchar(), !isalpha(r)){}
                return r;
        }
        inline long Read(void) {
                long r = 0;char ch;
                while (ch = getchar(), !isdigit(ch)){};
                r = ch - '0';
                while (ch = getchar(), isdigit(ch)) r = r * 10 + ch - '0';
                return r;
        }
 
        struct Node {
                long l, r, p, size; ull hash;
                Node():l(0), r(0), size(0), p(0), hash(0){}
                char c;
        }S[MAXN]; long sid = 0, root = 0;
 
        ull P[100001] = {0};
        class Tree {
                public:
                        inline void Updata(long x) {
                                if (!x) return;
                                S[0].size = S[0].hash = 0;
                                S[x].size = S[ S[x].l ].size + S[ S[x].r ].size + 1;
                                ull ret = S[ S[x].l ].hash; ret = ret * seed + S[x].c; ret = ret * P[ S[ S[x].r ].size ] + S[ S[x].r ].hash;
                                S[x].hash = ret;
                        }
                        inline void RR(long x) {
                                long L = S[x].l, F = S[x].p;
                                S[x].l = S[L].r, S[ S[x].l ].p = x;
                                S[L].r = x, S[x].p = L;
                                S[L].p = F;
                                if (x == S[F].l) S[F].l = L; else S[F].r = L;
                                Updata(x);Updata(L);
                        }
                        inline void LL(long x) {
                                long R = S[x].r, F = S[x].p;
                                S[x].r = S[R].l, S[ S[x].r ].p = x;
                                S[R].l = x, S[x].p = R;
                                S[R].p = F;
                                if (x == S[F].l) S[F].l = R; else S[F].r = R;
                                Updata(x);Updata(R);
                        }
                        inline void Splay(long x, long G) {
                                long F, FF;
                                while ((F = S[x].p) != G && S[x].p != x)
                                        if ((FF = S[F].p) == G)
                                                if (x == S[F].l)
                                                        RR(F);
                                                else
                                                        LL(F);
                                        else
                                                if (x == S[F].l)
                                                        if (F == S[FF].l)
                                                                RR(FF), RR(F);
                                                        else
                                                                RR(F), LL(FF);
                                                else
                                                        if (F == S[FF].l)
                                                                LL(F), RR(FF);
                                                        else
                                                                LL(FF), LL(F);
                                if (!G) root = x;
                        }
                        inline long Select(long k) {
                                long t = root, L;
                                S[0].size = 0;
                                while (S[ L = S[t].l ].size + 1 != k)
                                        if (k <= S[L].size)
                                                t = L;
                                        else
                                                t = S[t].r, k = k - S[L].size - 1;
                                return t;
                        }
                        inline long New(char c) {
                                long t = ++sid;
                                S[t].hash = S[t].c = c; S[t].size = 1;
                                return t;
                        }
                        inline void Insert(long x, char c) {
                                long l = x + 1, r = l + 1;
                                Splay( l = Select(l), 0 );
                                Splay( r = Select(r), l );
                                S[r].l = New(c);
                                S[ S[r].l ].p = r;
                                Updata(r); Updata(l);
                                Splay(x, 0);
                        }
                        inline void Replace(long x, char c) {
                                long l = x, r = x + 2;
                                Splay( l = Select(l), 0 );
                                Splay( r = Select(r), l );
                                long t = S[r].l;
                                S[t].c = S[t].hash = c;
                                Updata(r); Updata(l);
                                Splay(x, 0);
                        }
                        long Build(long l, long r, char* c) {
                                if (l > r) return 0;
                                long mid = (l + r) >> 1;
                                long t = New(c[mid]);
                                S[ S[t].l = Build(l, mid - 1, c) ].p = t;
                                S[ S[t].r = Build(mid + 1, r, c) ].p = t;
                                Updata(t);
                                return t;
                        }
                        inline ull Hash(long l, long r) {
                                l++, r++;
                                Splay( l = Select(l - 1), 0 );
                                Splay( r = Select(r + 1), l );
                                return S[ S[r].l ]. hash;
                        }
                        bool Check(long a, long b, long t, long limit) {
                                if (a + t - 1 > limit || b + t - 1 > limit) return false;
                                ull l1 = Hash(a, a + t - 1);
                                ull l2 = Hash(b, b + t - 1);
                                return l1 == l2;
                        }
                        long Ask(long a, long b) {
                                long l = 0, r = S[root].size - 2, n = S[root].size - 2;
                                if (Check(a, b, r, n)) return true;
                                while (l <= r) {
                                        long mid = (l + r) >> 1;
                                        if (Check(a, b, mid, n))
                                                l = mid + 1;
                                        else
                                                r = mid - 1;
                                }
                                return r;
                        }
                        void Print(long x) {
                                if (!x) return;
                                Print(S[x].l);
                                putchar(S[x].c);
                                Print(S[x].r);
                        }
        };
        long l;
        void Work(void) {
                P[0] = 1;
                for (long i = 1; i <= 100000; i++) P[i] = P[i - 1] * seed;
                
                char ch[MAXN] = {0};
                scanf("%s", ch + 1);ch[0] = '|';
                long n = strlen(ch);
                ch[n] = '|'; ch[n + 1] = '\0';
                Tree T;
                root = T.Build(0, n, ch);
 
                long Q = Read(), a, b; l = n - 1;
                for (long oo = 1; oo <= Q; oo++) {
                        #ifdef Debug
                                //T.Print(root); puts("");
                        #endif
                        char c = ReadChar();
                        if (c == 'Q') a = Read(), b = Read(), printf("%ld\n", T.Ask(a, b));else
                        if (c == 'R') a = Read(), c = ReadChar(), T.Replace(a, c);else
                        if (c == 'I') a = Read(), c = ReadChar(), T.Insert(a, c), l++;
                }
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
                freopen("1.out", "w", stdout);
        #endif
        Solve::Work();
        return 0;
}