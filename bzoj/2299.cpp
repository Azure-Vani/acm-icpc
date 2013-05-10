//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
        int gcd(int a, int b) {
                if (b) return gcd(b, a % b); else return a;
        }
        void Exgcd(int a, int b, int &x, int &y) {
                if (!b) {
                        x = 1, y = 0;
                        return;
                }
                Exgcd(b, a % b, x, y);
                int temp = y;
                y = x - a / b * y;
                x = temp;
        }
        bool Gao(int a, int b, int c, int &x, int &y) {
                int t = gcd(a, b), delta;
                if (c % t) return false; else delta = c / t; 
                Exgcd(a, b, x, y);
                x *= delta, y *= delta;
                return true;
        }
        bool odd(int a, int b) {
                a = abs(a), b = abs(b);
                if ((a & 1) == (b & 1)) return 0; else return 1;
        }
        void Work(int a, int b, int x0, int y0) {
                int X1, Y1, X2, Y2; bool Check = true;
                Check &= Gao(a, b, x0, X1, Y1);
                Check &= Gao(a, b, y0, X2, Y2);
                if (!Check) {puts("N");return;}
                while ((a % 2 == 0) && (b % 2 == 0)) a >>= 1, b >>= 1;
                int num = odd(X1, Y2) + odd(X2, Y1);
                int delta = (a & 1) + (b & 1);
                if (num == 0 || (num == 1 && delta == 1) || (num == 2 && delta))
                        puts("Y");
                else 
                        puts("N");
        }
        void Check(int now, int m, int p) {
                if (m % now || p % now) puts("N");
                else puts("Y");
        }
        void solve(void) {
                int a, b, x, y;
                scanf("%d%d%d%d", &a, &b, &x, &y);
                a = abs(a), b = abs(b);
                if (!a) {
                        Check(b, y, x);
                }else 
                if (!b) {
                        Check(a, x, y);
                }else
                Work(a, b, x, y);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("vector.in", "r", stdin);
                freopen("vector.out", "w", stdout);
        #endif
        int _; scanf("%d", &_);
        while (_--)
                Solve::solve();
        return 0;
}