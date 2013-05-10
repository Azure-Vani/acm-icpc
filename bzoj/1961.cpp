#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
namespace Solve {
        const long MAXN = 105;
        const long MAXB = 10005;
 
        inline long Read(void) {
                long r = 0; int ch;
                while (ch = getchar(), !isdigit(ch)){}
                r = ch - '0';
                while (ch = getchar(), isdigit(ch)) r = r * 10 + ch - '0';
                return r;
        }
        long n, w[MAXN] = {0};
        struct Segment {
                long l, r;
        };
        struct Set {
                long n; Segment A[MAXB];
                Set(){n = 0; memset(A, 0, sizeof A);}
 
                inline Segment& operator ()(const long x) {return A[x];}
                Set& operator =(const Set& a) {
                        n = a.n;
                        memcpy(A + 1, a.A + 1, sizeof(Segment) * n);
                        return *this;
                }
                inline friend Set operator +(Set& a, long w) {
                        Set c;
                        long cnt = 0;
                        for (long i = 1; i <= a.n; i++)
                                if (a(i).r + w >=0) {
                                        cnt++;
                                        c(cnt).l = std::max(0l, a(i).l + w);
                                        c(cnt).r = a(i).r + w;
                                }
                        c.n = cnt;
                        return c;
                }
                inline long Value(void) {
                        long ret = 0;
                        for (long i = 1; i <= n; i++) 
                                ret += (A[i].r - A[i].l + 1);
                        return ret;
                }
        };
 
        long best = 0, ID;
 
        void AddMain(Set& a, long w) {
                Set b, c;
                b = a + w;
                long l1 = 1, l2 = 1, pos, cnt = 1;
                if (a(1).r < b(1).r)
                        pos = a(1).r, l1++;
                else
                        pos = b(1).r, l2++;
                
                c(1).l = 0;
                while (l1 <= a.n || l2 <= b.n) {
                        if (l1 <= a.n && ( (l2 <= b.n && a(l1).l < b(l2).l) || l2 > b.n)) {
                                if (a(l1).l > pos + 1) {
                                        c(cnt).r = pos;
                                        cnt++;
                                        c(cnt).l = a(l1).l;
                                }
                                pos = std::max(a(l1).r, pos);
                                l1++;
                        }else if (l2 <= b.n) {
                                if (b(l2).l > pos + 1) {
                                        c(cnt).r = pos;
                                        cnt++;
                                        c(cnt).l = b(l2).l;
                                }
                                pos = std::max(b(l2).r, pos);
                                l2++;
                        }
                }
                c(cnt).r = pos;
                c.n = cnt;
                a = c;
        }
        inline void Add(const Set &s, Set& ret, long l, long r) {
                ret = s;
                for (long i = l; i <= r; i++)
                        AddMain(ret, w[i]);
        }
        void Make(long l, long r, Set& s) {
                if (l == r) {
                        long t = s.Value();
                        if (t > best)
                                ID = l, best = t;
                        return;
                }
                Set L, R;
                long mid = (l + r) >> 1;
                Add(s, L, l, mid);
                Add(s, R, mid + 1, r);
                Make(l, mid, R);
                Make(mid + 1, r, L);
        }
        inline void Input(void) {
                n = Read();
                for (long i = 1; i <= n; i++) w[i] = Read();
        }
        void Work(void) {
                Set S;
                S.n = 1;
                Make(1, n, S);
                
                for (long i = 1; i <= n; i++)
                        if (i != ID)
                                AddMain(S, w[i]);
                for (long i = 1; i <= n; i++)
                        if (i != ID)
                                AddMain(S, -w[i]);
 
                printf("%ld %ld\n", w[ID], S(1).r + 1);
        }
        void solve(void) {
                Input();
                Work();
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::solve();
        return 0;
}