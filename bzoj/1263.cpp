/*#include <cstdio>
typedef unsigned long long ll;
#define LL "%lld"
#define max(a, b) ((a)>(b)?(a):(b))
ll n, f[500], g[500];
int main(int argc, char** argv) {
	scanf(LL, &n);
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = 0;
		for (int j = 0; j <= i; j++)
			if (f[i] < f[j] * (i - j))
				f[i] = f[j] * (i - j), g[i] = j;
	}
	printf(LL "\n", f[n]);
	while (n) {
		printf(LL " ",n - g[n]);
		n = g[n];
	}
	return 0;
}*/
//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#define max(a, b) ((a)>(b)?(a):(b))
namespace Solve {
	const int MAXN = 10200;
	int n;
	
	struct Big {
		int a[MAXN], n;
		void Go(void) {
			int l = 1;
			while (a[l] > 9 || l < n) a[l + 1] += a[l] / 10, a[l] %= 10, l++;
			n = l;
		}
		void Put(void) {
			printf("%d\n", n);
			for (int i =  n; i >= max(n - 99, 1); i--)
				printf("%d", a[i]);
			puts("");
		}
		void operator =(int t) {
			memset(a, 0, sizeof a);
			if (t < 10){ a[n = 1] = t, a[2] = 0; return; }
			n = 0;
			while (t > 0) a[++n] = t % 10 , t /= 10;
			a[n + 1] = 0;
		}
		void operator =(Big& t) {
			memcpy(a, t.a, sizeof (int) * (t.n + 1));
			n = t.n;
		}
	};

	void Mul(Big& a, Big& b) {
		Big c; c = 0;
		for (int i = 1; i <= a.n; i++)
			for (int j = 1; j <= b.n; j++)
				c.a[i + j - 1] += a.a[i] * b.a[j];
		c.n = a.n + b.n - 1;
		c.Go();
		a = c;
	}
	Big& Pow(int n) {
		static Big ret; static Big d;ret = 1; d = 3;
		while (n > 0) {
			if (n & 1) Mul(ret, d);
			Mul(d, d);
			n >>= 1;
		}
		return ret;
	}

	void solve(void) {
		scanf("%d", &n);
		int d;
		if (n % 3 == 1) {
			Big a = Pow(n / 3 - 1);
			Big b; b = 4;
			Mul(a, b);
			a.Put();
		}else
		if (n % 3 == 2) {
			Big a= Pow(n / 3);
			Big b; b = 2;
			Mul(a, b);
			a.Put();
		}else {
			Big a = Pow(n / 3);
			a.Put();
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
