#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int n, a, b, Ans; string st;
vector<int> L[3];

void set(int u, int n, int t) {
	Ans += n; 
	while (n--) st[L[u].back()] = t + '0', L[u].pop_back();
}

int main(void) {
	freopen("in", "r", stdin);
	cin >>n>>a>>b>>st;
	for (int i = 0; i < (int)st.length(); i++) {
		L[st[i] - '0'].push_back(i);
	}
	int n0 = a - L[0].size(), n1 = b-L[1].size();
	if (a + b > n) cout <<-1<<endl; else {
		if (n0 >= 0 && n1 >= 0) {
			set(2, n0, 0);
			set(2, n1, 1);
		} else if (n0 >= 0 && n1 <= 0) {
			int d = min(n0, -n1);
			set(1, d, 0);
			if (d == n0) set(1, -n1 - d, 2); else set(2, n0 + n1, 0);
		} else if (n0 <= 0 && n1 >= 0) {
			int d = min(-n0, n1);
			set(0, d, 1);
			if (d == n1) set(0, -n0 - d, 2); else set(2, n1 + n0, 1);
		} else {
			set(0, -n0, 2); set(1, -n1, 2);
		}
		cout <<Ans<<endl<<st<<endl;
	}
	return 0;
}

