#include <cstdio>
#include <algorithm>
#include <cctype>
const int MAXN = 100050;
namespace Data {
        struct Node {
                Node *ch[2]; int l, r; int max, delta, mdelta, evermax;
                inline void Add(int d) {delta += d; mdelta = std::max(mdelta, delta); evermax = std::max(evermax, max += d);}
                inline void Add(int last, int d) {mdelta = std::max(mdelta, delta + last); delta += d; evermax = std::max(evermax, max + last); max += d;}
                inline void Pass(void) {ch[0]->Add(mdelta, delta);ch[1]->Add(mdelta, delta);mdelta = delta = 0;}
                inline void Updata(void) {max = std::max(ch[0]->max, ch[1]->max); evermax = std::max(ch[0]->evermax, std::max(max, ch[1]->evermax));}
                void Build(int _l, int _r) {
                        if (_l == _r) {l = r = _l;return;}l = _l, r = _r;
                        int mid = (_l + _r) >> 1;
                        (ch[0] = new Node)->Build(_l, mid);
                        (ch[1] = new Node)->Build(mid + 1, _r);
                }
                void Add(int _l, int _r, int d) {
                        if (_l > _r) return;
                        if (_l <= l && r <= _r) {Add(d); return;}
                        int mid = (l + r) >> 1;Pass();
                        ch[0]->Add(_l, std::min(_r, mid), d);
                        ch[1]->Add(std::max(mid + 1, _l), _r, d);
                        Updata();
                }
                int Ask(int _l, int _r) {
                        if (_l > _r) return 0;
                        if (_l <= l && r <= _r) return evermax;
                        Pass();Updata();
                        int mid = (l + r) >> 1;
                        return std::max(ch[0]->Ask(_l, std::min(mid, _r)), ch[1]->Ask(std::max(mid + 1, _l), _r));
                }
        };
        class SegmentTree {public:
                Node *root;
                void Set(int n) {root = new Node; root->Build(1, n);}
                void Add(int l, int r, int d) {root->Add(l, r, d);}
                int Ask(int l, int r) {return root->Ask(l, r);}
        };
}
namespace Solve {
        inline int ScanInt(void) {
                int r = 0, c, d;
                while (c = getchar(), !isdigit(c) && c != '-') {}
                if (c != '-') r = c - '0';
                while (d = getchar(),  isdigit(d)) r = r * 10 + d - '0';
                return c == '-' ? -r : r;
        }
 
        struct Interval {
                int l, index; Interval* next;
                Interval(int l, int index, Interval* next):l(l), index(index), next(next){}
        }*a[MAXN];
        int Ans[MAXN], n, m, c[MAXN];
        Data::SegmentTree T;
        void Input(void) {
                T.Set(n = ScanInt()); int i, l, r;
                for (i = 1; i <= n; i++) c[i] = ScanInt();
                for (m = ScanInt(), i = 0; i < m; i++) 
                        l = ScanInt(), r = ScanInt(), a[r] = new Interval(l, i, a[r]);
        }
        #define X(a) ((a) + 100000)
        int Last[MAXN << 1];
        void solve(void) {
                Input();
                for (int i = 1; i <= n; i++) {
                        T.Add(Last[X(c[i])] + 1, i, c[i]), Last[X(c[i])] = i;
                        for (Interval *p = a[i]; p; p = p->next) 
                                Ans[p->index] = T.Ask(p->l, i);
                }
                for (int i = 0; i < m; i++) printf("%d\n", Ans[i]);
        }
}
int main(int argc, char** argv) {
        Solve::solve();
        return 0;
}
 