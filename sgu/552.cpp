#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int base = 13331;

typedef string Int64;

inline Int64 getHash(char ch[]) {
	/*int n = strlen(ch); Int64 ret = 0;
	for (int i = 0; i < n; i++) ret = ret * base + ch[i];*/
	return string(ch);
}

map<vector<Int64>, int> T;
vector<Int64> tmp;

int n, m, fim[9];Int64 list[4]; char ch[20];

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d", &n); fim[1] = 0, fim[2] = 1, fim[4] = 2, fim[8] = 3;
	for (int j = 1, t; j <= n; j++) {
		scanf("%d", &t);
		for (int i = 0; i < t; i++) scanf("%s", ch), list[i] = getHash(ch); sort(list, list + t);
		for (int i = 1, p; i < (1 << t); i++) {
			tmp.resize(0); p = i;
			while (p) {
				int now = p & -p;
				tmp.push_back(list[fim[now]]), p -= now;
			}
			T[tmp]++;
		}
	}
	scanf("%d", &m);
	for (int i = 1, t; i <= m; i++) {
		scanf("%d", &t); tmp.resize(0);
		for (int j = 0; j < t; j++) scanf("%s", ch), tmp.push_back(getHash(ch)); sort(tmp.begin(), tmp.end());
		printf("%d\n", T[tmp]);
	}
	return 0;
}

