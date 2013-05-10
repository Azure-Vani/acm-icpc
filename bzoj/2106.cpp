#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cctype> 
#include <string> 
#include <cstring> 
#include <cstdio> 
#include <iterator>
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

const int MAXN = 3000;

int nNode = 0, Stack[MAXN], n, cur = 0, Link[MAXN];
bool vis[215], vaild[MAXN], clear[MAXN];int hash[MAXN];
char ch[MAXN];

string st;
struct Node {
	char c; vector<int> next;
}a[MAXN];

vector<int> List[MAXN], Edge[MAXN];

class PostfixRLE {
	public:
	void AddEdge(int x, int y) {
		Edge[x].pb(y);
		Edge[y].pb(x);
	}
	void Merge(vector<int> &a, const vector<int> &b) {
		foreach(it, b) a.pb(*it);
	}
	void Unique(vector<int> &a) {
		std::sort(a.begin(), a.end());
		vector<int>::iterator it = unique(a.begin(), a.end());
		a.erase(it, a.end());
	}
	bool find(int u) {
		foreach(it, Edge[u]) if (hash[*it] != cur && !clear[*it]) {
			hash[*it] = cur;
			if (Link[*it] == -1 || find(Link[*it])) {
				Link[*it] = u;
				return true;
			}
		}
		return false;
	}
	int Match(void) {
		memset(Link, -1, sizeof Link);
		int ret = 0;
		for (int i = 0; i <= n - 1; i++) if (vaild[i]) {
			cur++;
			ret += find(i);
		}
		return ret;
	}
	int Dfs(int u) {
		if (islower(a[u].c)) {
			List[u].pb(a[u].c);
			return 1;
		}
		int ret = 1;
		foreach(it, a[u].next) {
			ret += Dfs(*it);
		}
		vector<int> &T = List[u];
		n = a[u].next.size();
		memset(vis, 0, sizeof vis);
		memset(vaild, 0, sizeof vaild);
		for (int ii = 0; ii < n; ii++) {
			int i = a[u].next[ii];
			Edge[ii].clear();
			if (islower(a[i].c)) {
				if (!vis[(int)a[i].c]) {
					vaild[ii] = true;
					vis[(int)a[i].c] = true;
					T.pb(a[i].c);
				} else ret--;
			}
		}
		for (int ii = 0; ii < n; ii++) if (vaild[ii]) {
			int i = a[u].next[ii];
			for (int jj = 0; jj < n; jj++) {
				int j = a[u].next[jj];
				if (!islower(a[j].c) && count(List[j].begin(), List[j].end(), a[i].c)) {
					AddEdge(ii, jj);
				}
			}
		}
		int M = Match();
		ret -= M;
		for (int i = 0; i < n; i++) if (!islower(a[a[u].next[i]].c)) {
			clear[i] = true;
			if (M == Match()) {
				Merge(T,List[a[u].next[i]]);
			}
			clear[i] = false;
		}
		Unique(T);
		return ret;
	}

	int getCompressedSize(void) {
		int top = 0;
		for (int i = 0; i <= (int)st.length() - 1; i++) {
			if (islower(st[i])) {
				a[++nNode].c = st[i];
				Stack[++top] = nNode;
			} else {
				a[++nNode].c = st[i];
				for (int k = 0; k <= 1; k++) {
					int t = Stack[top--];
					if (a[t].c == st[i]) {
						Merge(a[nNode].next, a[t].next);
					} else a[nNode].next.pb(t);
				}
				Stack[++top] = nNode;
			}
		}
		return Dfs(nNode);
	}
	
};
int main(void) {
	PostfixRLE ___test;  
	cin >>st;
	int ret = ___test.getCompressedSize();
	cout <<ret<<endl;
	return 0;
}