#include <iostream>
#include <string>
using namespace std;
string repeat(string st, const int a) {
	string ret;
	for (int i = 1; i <= a; i++) ret += st;
	return ret;
}
const int MAXN = 2000;
string a[] = {"", "a","ab","aab","aaab","aaaab","aababb","aaababb","aababbaa","aaababbaa","aaaababbaa","aababbaabab","aaababbaabab","aaaababbaabab","aababbbaaababb","aaababbbaaababb","aaaababbbaaababb","aaaaababbbaaababb","aababbaaabaababbaa","aaabaabbabaabbbabaa","aababbaabababbaababb"};
int n;
int main(void) {
	cin >>n;
	if (n <= 11) {
		cout <<a[n]<<endl;
		return 0;
	}
	int r = (n - 5) % 6;
	int t = (n - 5 - r) / 6;
	if (n % 6 != 2) {
		string ret = "aabab" + repeat("bbaaba", t + 1);
		cout <<ret.substr(0, n)<<endl;
	} else {
		int t = (n - 14) / 6;
		string ret = "aabab" + repeat("bbaaba", t) + "bbaaababb";
		cout <<ret.substr(0, n)<<endl;
	}
}

