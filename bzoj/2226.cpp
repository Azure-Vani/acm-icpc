//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#define LL "%lld"
 
int const MAXN = 1000003;
int phi[MAXN], Prime[MAXN], cnt = 0, tag[MAXN];
void GetPhi(void) {
    tag[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!tag[i]) tag[i] = i, Prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt; j++) {
            int t = i * Prime[j]; if (t >= MAXN) break;
            tag[t] = Prime[j];
            if (i % Prime[j] == 0) {
                phi[t] = phi[i] * Prime[j];
                break;
            }else phi[t] = phi[i] * (Prime[j] - 1);
        }
    }
}
 
namespace Solve {
    typedef long long ll;
    inline int ScanInt(void) {
        int c, r;
        while (c = getchar(), !isdigit(c)) {}
        r = c - '0';
        while (c = getchar(),  isdigit(c)) r = (r << 1) + (r << 3) + c - '0';
        return r;
    }
    
    int factory[MAXN], l = 0, Pool[MAXN];
    ll Ans = 0;
    int n;
    inline ll Cal(int now) {
        int last = n / now;
        if (last == 1 || last == 2) Ans += 1; else
        Ans += (ll)(((ll)phi[last] >> 1) * (ll)last);
    }
    void Gao(int n) {
	    int last = 0;l = 0;
	    while (n != 1) {
		if (last != tag[n]) factory[tag[n]] = 0, Pool[++l] = tag[n];
		factory[tag[n]]++;
		last = tag[n];
		n /= tag[n];
	    }
    }
    void Find(int which, int now) {
	    if (which > l){ Cal(now);return;}
	    int t = Pool[which];
	    for (int i = 0; i <= factory[t]; i++) {
			Find(which + 1, now);
			now *= t;
	    }
    }

    void solve(void) {
        n = ScanInt();
        Ans = 0;
	Gao(n);
	Find(1, 1);
        printf(LL "\n", Ans * (ll)n);
    }
}
int main(int argc, char** argv) {
    #ifdef Debug
        freopen("1.in", "r", stdin);
        freopen("1.out", "w", stdout);
    #endif
    GetPhi();
    int _; scanf("%d", &_);
    while (_--) 
        Solve::solve();
    return 0;
}
