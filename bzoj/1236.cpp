#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 19;
	typedef long long int64;
	#define LL "%lld"
	int64 f[MAXN], pow[MAXN], Leng[MAXN];int digit[MAXN];
	
	void Initialize(void) {
		pow[0] = 1;
		for (int i = 1; i < MAXN; i++) pow[i] = pow[i - 1] * 10;
		for (int i = 1; i < 10; i++) digit[i] = digit[i - 1] + ((i & 1) ? i : -i);
		int64 base = 45; f[1] = 5;
		for (int i = 2; i < MAXN; i++, base *= 10) f[i] = f[i - 1] + ((i & 1) ? base : -base);
	}
	
	inline int Length(int64 n) { if (!n) return 1; int ret = 0; while (n) ret++, n /= 10; return ret; }

	void Work(int64 n) {
		if (n < 10) {printf("%d\n", digit[n]); return;}
		int k = Length(n);int64 ret = f[k - 1];
		if (k & 1) {
			ret += digit[9] * (n / 10ll - pow[k - 2]) + digit[n % 10];
			if (!((n % 10) & 1)) {for (int i = k; i >= 2; i--) ret += (i & 1) ^ (k & 1) ? n / pow[i - 1] % 10ll : -n / pow[i - 1] % 10ll;}
		}
		else 
			for (int i = 1; i <= k; i++) {
				int flag = ((i & 1) << 1) - 1, now = n / pow[i - 1] % 10ll;
				int64 front = n / pow[i], behind =  n % pow[i - 1] + 1ll;
				if (front) front -= pow[Length(front) - 1];
				int64 temp = 0;
				temp += 45ll * front * pow[i - 1];
				for (int j = 1; j < now; j++)
					temp += j *pow[i - 1];
				temp += behind * now;
				ret += flag * temp;
			}
		printf(LL "\n", ret);
	}

	void solve(void) {
		int64 n;
		Initialize();
		scanf(LL, &n);
		Work(n);
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
