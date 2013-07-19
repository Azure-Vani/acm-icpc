#include <cstdio>
#include <algorithm>
#include <tr1/unordered_map>
#include <vector>
#include <cstring>

#pragma GCC optimize("O2")

using namespace std;

const int MAXN = 1000010;
const int Mod = 1200007;

int n; char ch[MAXN];

vector<int> now;

typedef tr1::unordered_map<int, int> I;

I M;

int main(void) {
	freopen("in", "r", stdin);
	scanf("%s", ch + 1); n = strlen(ch + 1);
	for (int i = n; i >= 1; i--) {
		int S = 0; 
		vector<int>::iterator it = find(now.begin(), now.end(), ch[i] - 'a'); if (it != now.end()) now.erase(it); now.insert(now.begin(), ch[i] - 'a');
		for (int j = 0; j < (int)now.size() && now[j] != ch[i - 1] - 'a'; j++) {
			S |= 1 << now[j];
			M[S]++;
		}
	}
	int q; scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		char st[26]; scanf("%s", st);int t = strlen(st), S = 0; 
		for (int j = 0; j < t; j++) S |= 1 << (st[j] - 'a');
		printf("%d\n", M[S]);
	}
	return 0;
}

