//#define Debug
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
        typedef long long Int64;
        const int MAXN = 300020;
 
        inline int ScanInt(void) {
                int r = 0, c;
                while (c = getchar(), !isdigit(c)) {}
                r = c - '0';
                while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
                return r;
        }
 
        int a[MAXN], n, Mod, max = 0;
        
        void Input(void) {
                n = ScanInt(); Mod = ScanInt();
                for (int i = 1; i <= n; i++) max = std::max(a[i] = ScanInt(), max);
        }
 
#define LowBit(x) ((x) & (-(x)))
        class BIT {public:
                int a[MAXN], n; void Set(int _n) {n = _n;}
                inline void Insert(int t, int u) {for (int i = t; i <= n; i += LowBit(i)) a[i] += u;}
                inline int Cal(int u) {int ret = 0; for (int i = u; i >= 1; i -= LowBit(i)) ret += a[i]; return ret;}
        }T;
 
        void Ex_gcd(int a, int b, int &x, int &y) {
                if (!b) {
                        x = 1, y = 0; return;
                }
                Ex_gcd(b, a % b, x, y);
                int t = x; x = y, y = t - a / b * y;
        }
        int _E(int a) {
                int x, y;
                Ex_gcd(a, Mod, x, y);
                x %= Mod;
                return x < 0 ? (x + Mod) : x;
        }
 
        int factory[MAXN], hash[MAXN], cnt = 0;
 
        inline int Prepare(void) {
                int tmp = Mod;
                for (int i = 2; i * i <= Mod; i++) if (tmp % i == 0) {
                        factory[++cnt] = i;
                        while (tmp % i == 0) tmp /= i, hash[cnt]++;
                }
                if (tmp > 1) factory[++cnt] = tmp, hash[cnt] = 1;
        }
 
        int up[MAXN], down[MAXN];
 
        inline int Divid(int n, int a[]) {
                for (int i = 1; i <= cnt; i++) {
                        while (n % factory[i] == 0) n /= factory[i], a[i]++;
                }
                return n;
        }
 
        inline int Pow(int a, int n) {
                int r = 1;
                while(n) { if (n & 1) r = (Int64) r * a % Mod; a = (Int64) a * a % Mod; n >>= 1;}
                return r;
        }
 
        int number[MAXN], yy[MAXN];
 
        void Work(void) {
                int Ans = 0, uplast = 1, downlast = 1;
                T.Set(max); T.Insert(a[n], 1); number[a[n]]++;
                for (int i = n - 1; i >= 1; i--) {
                        int Sk = ++number[a[i]], Now = 1;
                        T.Insert(a[i], 1);
                        int count = T.Cal(a[i] - 1);
                        uplast = (Int64) uplast * Divid(n - i, up) % Mod;
                        downlast = (Int64) downlast * Divid(Sk, down) % Mod;
                        if (count) count = Divid(count, yy); else continue;
                        int tmp1 = 1;
                        for (int j = 1; j <= cnt; j++) {
                                tmp1 = (Int64) tmp1 * Pow(factory[j], yy[j] + up[j] - down[j]) % Mod;
                                yy[j] = 0;
                        }
                        int tmp2 = (Int64) uplast * _E(downlast) % Mod;
                        count = (Int64) count * tmp1 % Mod;
                        count = (Int64) count * tmp2 % Mod;
                        Ans = (Int64) ((count + Ans) % Mod);
                }
                printf("%d\n", (Ans + 1) % Mod);
        }
        
        void solve(void) {
                Input();
                Prepare();
                Work();
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
                freopen("1.out", "w", stdout);
        #endif
        Solve::solve();
        return 0;
}