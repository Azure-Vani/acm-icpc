//#define Debug
#include <cstdio>
#include <algorithm>
#define LL "%lld"
namespace Solve {
        const int LENG = 20;
        const int MAXS = 180;
        const int MAXR = 1010;
        typedef long long ll;
        int K;
        struct pair {
                ll cnt;int rest; bool vis;
                void Renew(pair N) {
                        cnt += N.cnt;
                        rest = N.rest;
                }
                pair():cnt(0), rest(0){}
                pair(int val) {val >= K ? (cnt = 1, rest = 0) : (cnt = 0, rest = val), vis = true;}
        }f[LENG][MAXS][MAXR];
 
        pair Dp(int L, int Sum, int rest) {
                if (Sum > K) Sum = K;
                pair& Now = f[L][Sum][rest];
                if (Now.vis) return Now;
                Now.vis = true;
                if (!L) {
                        int val = Sum + rest;
                        Now = pair(val);
                        return Now;
                }
                Now = pair(rest);
                for (int i = 0; i < 10; i++)
                        Now.Renew(Dp(L - 1, Sum + i, Now.rest));
                return Now;
        }
        int Digit(ll now) {
                int ret = 0; while (now) ret += now % 10 , now /= 10; return ret;
        }
        void Work(ll l, ll r) {
                pair Ans;
                while (l <= r) {
                        ll pow = 1, L = 0, n_pow;
                        while (l + (n_pow = pow * 10) <= r + 1 && (l % n_pow == 0)) pow = n_pow, L++;
                        pair Temp = Dp(L, Digit(l / pow), Ans.rest);
                        Ans.Renew(Temp);
                        l += pow;
                }
                printf(LL "\n", Ans.cnt);
        }
        void solve(void) {
                ll l, r;
                scanf(LL LL "%d", &l, &r, &K);
                Work(l, r);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::solve();
        return 0;
}