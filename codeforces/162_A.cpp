#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <list>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	char ch[1000010];

	inline long long gcd(long long a, long long b) {
		if (!b) return a; else return gcd(b, a % b);
	}

	struct Fac {
		long long a, b;
		Fac(long long _a, long long _b) {
			a = _a, b = _b;
			long long t = gcd(a, b);
			a /= t, b /= t;
		}
		inline Fac operator +(const Fac& oth) {
			Fac ret(oth.b * a + oth.a * b, b * oth.b);
			return ret;
		}
		inline friend bool operator <(const Fac& c, const Fac& oth) {
			int a = c.a, b = c.b;
			return a * oth.b < oth.a * b;
		}
	};

	list<int> T;

	inline void solve(void) {
		scanf("%s", ch); int n =strlen(ch);
		list<int>::iterator it = T.end();
		for (int i = 0; i < n; i++) {
			it = T.insert(it, i + 1);
			if (ch[i] == 'r') it++;
		}
		foreach(it, T) printf("%d\n", *it);
	}
}

int main(void) {
	#ifdef FILEIO
//		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
