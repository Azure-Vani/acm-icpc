#line 95 "LCMSet.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>

using namespace std;

class LCMSet {
	public:
	inline int gcd(int a, int b) {
		return !b?a:gcd(b, a % b);
	}
	inline bool check(int x, const vector<int>& C) {
		int tmp = 1;
		for (int i = 0; i < C.size(); i++) {
			if (gcd(x, C[i]) == C[i]) {
				long long t = gcd(tmp, C[i]);
				tmp = (long long)tmp * C[i] / t;
			}
		}
		return tmp == x;
	}
	string equal(vector <int> A, vector <int> B) {
		for (int i = 0; i < A.size(); i++) {
			if (!check(A[i], B)) return string("Not equal");
		}
		for (int i = 0; i < B.size(); i++) {
			if (!check(B[i], A)) return string("Not equal");
		}
		return string("Equal");
	}

};// BEGIN CUT HERE



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
