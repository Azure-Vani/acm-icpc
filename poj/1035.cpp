#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#define REP(i, l, r) for(int i = l; i <= r; i++)
using namespace std;

#pragma GCC optimize("O3")

const int base = 27;
typedef unsigned long long Int64;
typedef pair<int, string> PII;

map<Int64, vector<PII> > M;
set<PII> Ans;

inline Int64 Geth(const string& st) {
	Int64 ret = 0;
	REP(i, 0, (int)st.length() - 1) ret = ret * base + st[i] - 'a' + 1;
	return ret;
}

string st, ss;

inline void Gen(const string& ss) {
	vector<PII> tmp = M[Geth(ss)];
	for (vector<PII>::iterator it = tmp.begin(); it != tmp.end(); ++it) Ans.insert(*it);
}

int main(void) {
	freopen("in", "r", stdin);
	int L = 0;
	while (cin >> st, st != "#") M[Geth(st)].push_back(make_pair(++L, st));//, cout<<st+"'s hash is "<<Geth(st)<<endl;
	while (cin >> st, st != "#") {
		Ans.clear();
		//cout <<st+"'s hash is "<<Geth(st)<<endl;
		if (M.count(Geth(st))) {cout <<st<<" is correct"<<endl; continue;}
		cout <<st<<":";
		REP(i, 0, (int)st.length()) {
			REP(c, 'a', 'z') {
				ss = st, ss.insert(i, string(1, c));
				if (M.count(Geth(ss))) Gen(ss);
				if (i != (int)st.length()) {
					ss = st, ss.replace(i, 1, string(1, c));
					if (M.count(Geth(ss))) Gen(ss);
				}
			}
			if (i != (int)st.length()) {
				ss = st, ss.erase(i, 1);
				if (M.count(Geth(ss))) Gen(ss);
			}

		}
		for (set<PII>::iterator it = Ans.begin(); it != Ans.end(); ++it) cout <<' '<<it->second; cout <<endl;
	}
	return 0;
}

