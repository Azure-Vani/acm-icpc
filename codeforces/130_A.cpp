//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <string>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 300;

	string st;
	vector<string> ans;
	int n = st.length();

	bool Ok(int i) {
		if (i >= n - 2) return false;
		return (st[i] == 'W' && st[i + 1] == 'U' && st[i + 2] == 'B');
	}

	inline void solve(void) {
		cin >>st; n = st.size();
		for (int i = 0; i < n; ) {
			if (Ok(i)) i += 3;
			else {
				string tmp;
				while (i < n && !Ok(i)) tmp += st[i], i++;
				ans.pb(tmp);
			}
		}
		for (int i = 0; i < (int)ans.size() - 1; i++) cout <<ans[i]<<' '; if (ans.size()) cout <<ans[(int)ans.size() - 1]<<endl;
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
