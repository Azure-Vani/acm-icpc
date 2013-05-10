//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
    const int MAXN = 400050;
    int a[MAXN], n;
    inline void Input(void) {
        int c;
        while (islower(c = getchar())) {
            a[++n] = c - 'a' + 1;
            a[++n] = -1;
        }
        n--;
    }
    int L[MAXN];
    inline void Extend(void) {
        int MaxR = -1, where;
        for (register int i = 1; i <= n; i++) {
            register int it = 0;
            if (i <= MaxR) {
                it = std::min(L[where - (i - where)], MaxR - i);
            }
            while (i - it > 0 && i + it <= n && a[i - it] == a[i + it])
                ++it;
            L[i] = --it;
            if (MaxR < i + L[i]) {
                MaxR = i + L[i];
                where = i;
            }
        }
    }
    int C[MAXN << 1];
    inline void ins(int u, int t) {
        for (u = n - u + 1; u <= n; u += u&-u)
            C[u] = std::min(C[u], t);
    }
    inline int Cal(int u) {
        int ret = C[0];
        for (u = n - u + 1; u; u -= u&-u)
            ret = std::min(ret, C[u]);
        return ret;
    }
    struct Node {
        int value, pos;
        inline friend bool operator <(const Node& a, const Node& b) {
            return a.value + a.pos < b.value + b.pos;
        }
        inline void operator =(const Node& oth) {
            value = oth.value;
            pos = oth.pos;
        }
    }f[19][MAXN], null;
    int left[MAXN], pow[MAXN];
    inline Node Ask(int l, int r) {
        if (l < 1) l = 1; if (r > n) r = n;
        if (l > r) return null;
        if (!(l&1) && l > 1) l--;
        int u = pow[r - l + 1];
        return std::min(f[u][l], f[u][r - (1 << u) + 1]);
    }
    inline void Prepare(void) {
        memset(C, 60, sizeof C);
        for (register int i = 1, j; i <= n; i++) {
            ins(i + L[i], i);
            j = Cal(i);
            f[0][i].value = left[i] = j - (i - j);
            f[0][i].pos = i;
        }
        for (register int i = 2; i <= n; i++) {
            if ((i&(i-1)) == 0) pow[i] = pow[i - 1] + 1;
            else pow[i] = pow[i - 1];
        }
        for (register int k = 1; (1 << k) <= n; k++)
            for (register int i = 1; i <= n; i++)
                f[k][i] = std::min(f[k - 1][i], f[k - 1][i + (1 << (k - 1))]);
    }
    inline int Update(int l, int r) {
        if (l > r ) return 0;
        register int ret = (r - l + 1) >> 1;
        if ((r&1) && (l&1)) ++ret;
        return ret;
    }
    inline int Work(void) {
        int ret = 2;
        for (register int i = 1; i <= n; i++) {
            Node tmp = Ask(i - L[i] - 1, i - 1);
            if (!tmp.pos) continue;
            int Len = Update(tmp.value, i + (i - tmp.pos) - 1);
            ret = std::max(ret, Len);
        }
        return ret;
    }
    inline void solve(void) {
        Input();
        Extend();
        Prepare();
        printf("%d\n", Work());
    }
int main(void) {
#ifdef Debug
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    solve();
    return 0;
}