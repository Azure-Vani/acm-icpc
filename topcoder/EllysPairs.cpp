#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

class EllysPairs {public:
	int getDifference(vector<int> a) {
		sort(a.begin(), a.end());
		vector<int> S;
		for (int i = 0, j = a.size() - 1; i < j; i++, j--) S.push_back(a[i] + a[j]);
		sort(S.begin(), S.end());
		return S[S.size() - 1] - S[0];
	}
};
