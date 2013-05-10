#define OJ

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
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>

#define mk make_pair
#define pb push_back
#define rep(i,r) for(int i = 0; i < r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899

typedef long long Int64;

using namespace std; 

bool a[60][60];

class RelabelingOfGraph { public:
	vector <int> renumberVertices(vector <string> m) {
		int n = m.size();
		rep(i,n) rep(j,n) a[i][j] = m[i][j] - '0';
		rep(k,n) rep(i,n) rep(j,n) a[i][j] |= a[i][k] & a[k][j];
		vector<int> R;
		rep(i,n) if (a[i][i]) return R; else a[i][i] = true;
		rep(i,n) {
			int tmp = -1;
			rep(j,n) tmp += a[j][i];
			R.pb(tmp);
			rep(l1,n) if (a[l1][i]) rep(l2,n) if (!a[l2][i]) a[l1][l2] = true;
		}
		return R;
	}
	
 
};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
