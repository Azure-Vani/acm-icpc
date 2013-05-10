#include <cstdio>
#include <algorithm>
#include <cmath>
namespace Solve {
    const int MAXN = 1501;
    const int MAXM = (MAXN * (MAXN - 1));
    typedef double ll;
 
    class dPoint {public:int x, y;}a[MAXN];
    class MidPoint {public:
        long long d;dPoint M;dPoint A;
        inline bool operator ==(const MidPoint& a) {
            return M.x == a.M.x && M.y == a.M.y && d == a.d;
        }
        inline friend bool operator <(const MidPoint& a, const MidPoint& b) {
            if (a.M.x != b.M.x) return a.M.x < b.M.x;
            else if (a.M.y != b.M.y) return a.M.y < b.M.y;
            else if (a.d != b.d) return a.d < b.d;
            else return a.A.x < b.A.x;
        }
    };
    static MidPoint S[MAXM];
 
    int n, nMid;
     
    #define sqr(x) ((long long)(x)*(x))
    #define dis(x1, y1, x2, y2) (sqr((x1) - (x2)) + sqr((y1) - (y2)))
    void Input(void) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
        for (int i = 1; i < n; i++) for (int j = i + 1; j <= n; j++) {
            int x = (a[i].x + a[j].x), y = (a[i].y + a[j].y);long long d = dis(a[j].x, a[j].y, a[i].x, a[i].y);
            S[nMid].d = d, S[nMid].M.x = x, S[nMid].M.y = y, S[nMid++].A = a[i];
            S[nMid].d = d, S[nMid].M.x = x, S[nMid].M.y = y, S[nMid++].A = a[j];
        }
    }
 
    inline bool More90(const dPoint& a, const dPoint& b, const dPoint& M) {
        return (a.x - M.x / 2.0) * (b.x - M.x / 2.0) + (a.y - M.y / 2.0) * (b.y - M.y / 2.0) < 0;
    }
    double X1, X2, Y1, Y2;
    inline long long Square(const dPoint& a, const dPoint& b, const dPoint& M) {
        X1 = (a.x - M.x / 2.0), Y1 = (a.y - M.y / 2.0), X2 = (b.x - M.x / 2.0), Y2 = (b.y - M.y / 2.0);
        long long ret = (long long)((X1 * Y2 - X2 * Y1) * 2.0);
        return ret < 0 ? -ret : ret;
    }
 
    long long Ans = 0, Si;
    inline void Gao(MidPoint *L, MidPoint *R) {
        MidPoint *tmp = L, *St = L;
        for (; L != R - 1; L++) {
            while (tmp != R - 1 && !More90(L->A, (tmp + 1)->A, tmp->M)) {
                tmp++;
                if (tmp == R)
                    tmp = St;
            }
            Si = Square(L->A, tmp->A, L->M);
            Ans = std::max(Si, Ans);
            if (tmp == R) break;
        }
    }
 
    #define Cross(a, b, c) (((a).x - (c).x / 2.0) * ((b).y - (c).y / 2.0) - ((b).x - (c).x / 2.0) * ((a).y - (c).y / 2.0))
    inline bool cmp(MidPoint a, MidPoint b) {
        return Cross(a.A, b.A, a.M) > 0;
    }
 
    MidPoint *now, *L;
    void solve(void) {
        Input();
        MidPoint *start = S, *end = S + nMid, *backup;
        std::sort(start, end);
        while (backup = start, start != end) {
            while (start + 1 != end && *(start + 1) == *start) start++;
            if (start - backup > 0) {
                std::sort(backup, start + 1, cmp);
                Gao(backup, start + 1);
            }
            start++;
        }
        printf("%lld\n", Ans);
    }
}
int main(int argc, char** argv) {
    Solve::solve();
    return 0;
}