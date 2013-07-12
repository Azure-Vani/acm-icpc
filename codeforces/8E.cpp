#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n; long long k, pow[60], f[60][4];
vector<int> a;

vector<int> reverse(vector<int> c) {
	reverse(c.begin(), c.end());
	return c;
}

vector<int> Not(vector<int> c) {
	for (int i = 0; i < (int)c.size(); i++) c[i] ^= 1;
	return c;
}

inline void Set(vector<int> &I, int t, int i) {
	if (t == 0) I.push_back(i);
	if (t == 1) I.push_back(0), I.push_back(1);
	if (t == -1) I.push_back(1);
}

inline void Update(int p, pair<int, int> mask) {
	for (int i = 0; i < 2; i++) {
		vector<int> I;
		Set(I, mask.first, i);
		if (i == 0 && mask.first != 0) continue;
		for (int j = 0; j < 2; j++) {
			vector<int> J;
			Set(J, mask.second, j);
			if (j == 0 && mask.second != 0) continue;
			for (int _i = 0; _i < (int)I.size(); _i++)
				for (int _j = 0; _j < (int)J.size(); _j++) {
					f[p][i * 2 + j] += f[p - 1][I[_i] * 2 + J[_j]];
				}
		}
	}
}

pair<int, int> mask[2][2] = {make_pair(0, 1), make_pair(1, 0), make_pair(-1, 0), make_pair(0, -1)};

inline long long Cal(void) {
	memset(f, 0, sizeof f); int res = n - a.size(), nL = (n + 1) >> 1; f[0][0] = 1;
	for (int i = 1; i <= nL; i++) {
		if (i <= res) {
			if (i > (int)a.size()) {
				Update(i, mask[0][0]);
				Update(i, mask[1][1]);
				if (i - 1 != n / 2) {
					Update(i, mask[0][1]);
					Update(i, mask[1][0]);
				}
			} else {
				Update(i, mask[a[i - 1]][0]);
				Update(i, mask[a[i - 1]][1]);
			}
		} else Update(i, mask[a[i - 1]][a[n - i]]);
	}
	long long ret = 0; for (int i = 0; i < 4; i++) ret += f[nL][i];
	return ret;
}

int main(void) {
//	freopen("in", "r", stdin);
	cin >>n>>k; pow[0] = 1; k++;
	for (int i = 1; i <= 59; i++) pow[i] = pow[i - 1] << 1;
	for (int i = 1; i <= n; i++) {
		a.push_back(0);
		long long tmp = Cal();
		if (i != 1 && tmp < k) {
			k -= tmp;
			a.pop_back();
			a.push_back(1);
		}
	}
	if (k > 1 || !(reverse(a) >= a && Not(reverse(a)) >= a)) puts("-1"); else {
		for (int i = 0; i < n; i++) printf("%d", a[i]); puts("");
	}
	return 0;
}

