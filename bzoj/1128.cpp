//#define Debug
#include <cassert>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 1005;

	int n, a[MAXN];

	#define Base 1000000
	struct Frac {
		int num, deno;
		Frac(int a, int b):num(a), deno(b){}
	};
	struct BigInt {
		Int64 a[5000];int n;
		BigInt(){memset(a, 0, sizeof a); n = 0;}
		inline int operator %(const int c) {
			Int64 Last = 0;
			for (int i = n; i >= 1; i--)
				Last = (Last * Base + a[i]) % c;
			return Last;
		}
		inline BigInt operator *(const int c) {
			BigInt ret;
			for (int i = 1; i <= n; i++) { 
				ret.a[i] = a[i] * c;
			}
			int &l = ret.n; l = 1;
			while (l < n || ret.a[l] > Base)
				ret.a[l + 1] += ret.a[l] / Base, ret.a[l] %= Base, l++;
			return ret;
		}
		friend std::ostream &operator <<(std::ostream& out, const BigInt& c) {
			out <<c.a[c.n];
			for (int i = c.n - 1; i >= 1; i--) {
				for (int j = 10; j < Base; j *= 10)
					if (c.a[i] < j) out <<'0';
				out <<c.a[i];
			}
			return out;
		}
		void operator =(const BigInt& c) {
			memcpy(a + 1, c.a + 1, sizeof (Int64) * (c.n));
			n = c.n;
		}
		void operator =(int c) {
			if (c == 0) n = 1; else
				while (c) a[++n] = c % Base, c /= Base;
		}
		inline BigInt operator /(const int c) {
			BigInt ret;
			Int64 Last = 0;
			for (int i = n; i >= 1; i--) {
				Int64 Now = Last * Base + a[i];
				Int64 t = Now / c; Last = Now % c;
				if (t || ret.n)
					ret.a[++ret.n] = t;
			}
			std::reverse(ret.a + 1, ret.a + ret.n + 1);
			return ret;
		}
	};
	int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
	struct Fraction {
		BigInt num, deno;
		inline Fraction operator *(Frac c) {
			Fraction ret;
			if (c.num == 0) {ret.deno = 1; ret.num = 0; return ret;}
			int g = gcd(c.deno, c.num); c.deno /= g, c.num /= g;
			int t1 = num % c. deno, t2 = deno % c.num;
			int g1 = gcd(t1, c.deno), g2 = gcd(t2, c.num);
			c.deno /= g1, c.num /= g2;
			ret.num = num / g1 * c.num;
			ret.deno = deno / g2 * c.deno;
			return ret;
		}
		friend std::ostream &operator <<(std::ostream& out, const Fraction& a) {
			out <<a.num<<'/'<<a.deno;
			return out;
		}
	}f[MAXN];

	void solve(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		f[n].num = 1, f[n].deno = a[n];
		for (int i = n - 1; i >= 1; i--)
			f[i] = f[i + 1] * Frac(a[i + 1] - 1 , a[i]);
		for (int i = 1; i <= n; i++)
			std::cout <<f[i]<<std::endl;
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
