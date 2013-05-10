//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cmath>
namespace Data {
        const double eps = 1e-7;
        struct Node {
                Node *ch[2], *p;
                int x, y; double S;
                inline bool dir(void) {return this == p->ch[1];}
                inline void SetC(Node* x, bool d) {
                        ch[d] = x; x->p = this;
                }
        }Tnull, *null = &Tnull;
        
        class SplayTree {
                public:
                Node *root;
                double Ans;int nLimit;
                SplayTree(int L = 0):nLimit(L){root = null;Ans = 0;}
                inline void rotate(Node *x) {
                        Node *p = x->p; bool d = x->dir();
                        p->p->SetC(x, p->dir());
                        p->SetC(x->ch[!d], d);
                        x->SetC(p, !d);
                }
                inline void Splay(Node *x, Node *G) {
                        while (x->p != G)
                                if (x->p->p == G) rotate(x);
                                else if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
                                        else {rotate(x); rotate(x);}
                        if (G == null) root = x;
                }
                Node* GetMin(Node *x) {
                        if (x == null) return null;
                        while (x->ch[0] != null) x = x->ch[0];
                        return x;
                }
                Node* GetMax(Node *x) {
                        if (x == null) return null;
                        while (x->ch[1] != null) x = x->ch[1];
                        return x;
                }
                Node* Succ(Node *x) {
                        if (x == null) return x;
                        Splay(x, null);
                        return GetMin(x->ch[1]);
                }
                Node* Prev(Node *x) {
                        if (x == null) return x;
                        Splay(x, null);
                        return GetMax(x->ch[0]);
                }
                #define pow(x) ((x)*(x))
                inline double Dis(Node *a, Node *b) {
                        if (a == null || b == null) return 0;
                        return sqrt(pow(a->x - b->x) + pow(a->y - b->y));
                }
                void Delete(Node *x) {
                        Splay(x, null);
                        Node *L = Prev(x), *R = Succ(x);
                        Splay(L, x);Splay(R, x);
                        double Ldis = Dis(x, L), Rdis = Dis(x, R), M = Dis(L, R);
                        L->S += (M - Ldis), R->S += (M - Rdis);
                        Ans += (M - Ldis - Rdis);
                        L->SetC(R, 1);
                        root = L;
                        root->p = null;
                }
                inline Node* New(int x, int y) {
                        Node* ret = new Node;
                        ret->x = x, ret->y = y;
                        ret->S = 0, ret->ch[0] = ret->ch[1] = null;
                        return ret;
                }
                void Updata(Node* now) {
                        Node *L = Prev(now), *R = Succ(now);
                        double Ldis = Dis(L, now), Rdis = Dis(R, now), M = Dis(L, R);
                        L->S += (Ldis - M);
                        R->S += (Rdis - M);
                        now->S = Ldis + Rdis;
                        Ans += (Ldis + Rdis - M);
                }
                void Insert(Node* &now, int x, int y, Node* last) {
                        if (now == null) {
                                now = New(x, y); now->p = last;
                                Splay(now, null);
                                Updata(root);
                                return;
                        }
                        if (x <= now->x)
                                Insert(now->ch[0], x, y, now);
                        else
                                Insert(now->ch[1], x, y, now);
                }
                double Cha(Node *L, Node *M, Node *R) {
                        return (L->x - M->x) * (R->y - M->y) - (R->x - M->x) * (L->y - M->y);
                }
                bool Ok(Node *now) {
                        Node *L = Prev(now), *R = Succ(now);
                        if (L == null || R == null || Cha(L, now, R) > -eps) return true;
                        else {
                                Delete(now);
                                return false;
                        }
                }
                void Adjust(Node *now) {
                        //Left
                        while (true) {
                                Node *L = Prev(now);
                                Node *LL = Prev(L);
                                if (LL == null || L == null) break;
                                if (Cha(L, now, LL) > -eps)
                                        break;
                                else 
                                        Delete(L);
                        }
                        //Right
                        while (true) {
                                Node *R = Succ(now);
                                Node *RR = Succ(R);
                                if (R == null || RR == null) break;
                                if (Cha(RR, now, R) > -eps) 
                                        break;
                                else
                                        Delete(R);
                        }
                }
                void Push(int x, int y) {
                        Insert(root, x, y, null);
                        if (!Ok(root)) return;
                        Adjust(root);
                }
                double Ask(void) {
                        return Ans;
                }
        };
}
namespace Solve {
        const int MAXN = 100050;
 
        inline int ScanInt(void) {
                int c, r = 0;
                while (c = getchar(), !isdigit(c)) {}
                r = c - '0';
                while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
                return r;
        }
 
        double Ans[MAXN];
        struct Query {bool flag; int index;}Q[MAXN];
        struct Point {int x, y;bool No;}a[MAXN];
 
        Data::SplayTree T;
 
        int n, m, nLimit;
        void Input(void) {
                nLimit = ScanInt();int x0 = ScanInt(), y0 = ScanInt();
                T.Push(0, 0);
                T.Push(nLimit, 0);
                T.Push(x0, y0);
                n = ScanInt();
                for (int i = 1; i <= n; i++) a[i].x = ScanInt(), a[i].y = ScanInt();
                m = ScanInt();
                for (int i = 1; i <= m; i++) {
                        Q[i].flag = ScanInt() - 1;
                        if (!Q[i].flag) {
                                int u = ScanInt();
                                a[u].No = true;
                                Q[i].index = u;
                        }
                }
                for (int i = 1; i <= n; i++) if (!a[i].No) {
                        T.Push(a[i].x, a[i].y);
                }
        }
 
        void Work(void) {
                int nAsk = 0;
                for (int i = m; i >= 1; i--) {
                        if (Q[i].flag)
                                Ans[++nAsk] = T.Ask();
                        else
                                T.Push(a[Q[i].index].x, a[Q[i].index].y);
                }
                for (int i = nAsk; i >= 1; i--)
                        printf("%.2lf\n", Ans[i]);
        }
        
        void solve(void) {
                Input();
                Work();
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("defense.in", "r", stdin);
                freopen("defense.out", "w", stdout);
        #endif
        Solve::solve();
        return 0;
}