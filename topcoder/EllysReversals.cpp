#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int a[60][60];

inline bool same(string a, string b) {
	if (a.length() != b.length()) return false;
	vector<string> S1, S2;
	for (int i = 0; i < (int)a.length(); i += 2) {
		string s1, s2;
		s1 += a[i]; if (i != a.length()) s2 += a[i + 1];
		S1.push_back(s1 + s2);
		S1.push_back(s2 + s1);
	}
	for (int i = 0; i < (int)b.length(); i += 2) {
		string s1, s2; s1 += b[i]; if (i != b.length()) s2 += b[i + 1];
		S2.push_back(s1 + s2);
		S2.push_back(s2 + s1);
	}
	sort(S1.begin(), S1.end());
	sort(S2.begin(), S2.end());
	for (int i = 0; i < S1.size(); i++) if (S1[i] != S2[i]) return false; return true;
}

int vis[60], n;

inline int Dfs(int u) {
	vis[u] = true;
	int ret = 1;
	for (int i = 0; i < n; i++) 
		if (a[u][i] && !vis[i]) {
		ret += Dfs(i);
	}
	return ret;
}

class EllysReversals{public:
	int getMin(vector<string> words) {
		n = words.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				a[i][j] = same(words[i], words[j]);
			}
		int tmp = 0, ret = 0;
		for (int i = 0; i < n; i++) if (!vis[i]) {
			tmp = Dfs(i);
			ret += tmp & 1;
		}
		return ret;
	}
};

int main(void) {
	vector<string> T;
	T.push_back("esprit");
	T.push_back("redotopc");
	T.push_back("odcpoter");
	EllysReversals Q;
	printf("%d\n", Q.getMin(T));
	return 0;
}

