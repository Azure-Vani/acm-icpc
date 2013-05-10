//#define FILEIO
 
#define INPUT "rabbit.in"
#define OUTPUT "rabbit.out"
 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
 
#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
 
using namespace std;
 
namespace Solve {
        inline void solve(void) {
                int n;
                scanf("%d", &n);
                printf("%d\n", n * (n - 1) / 2);
                for (int i = 1; i <= n; i++) 
                        for (int j = i + 1; j <= n; j++) {
                                int k;
                                if (j - i > (n - (j - i))) {
                                        k = (i + (n - (j - i)) - 1) % n + 1;
                                } else {
                                        k = (j + j - i - 1) % n + 1;
                                }
                                printf("%d %d %d\n", i, j, k);
                        }
        }
}
 
int main(void) {
        #ifdef FILEIO
                freopen(INPUT, "r", stdin);
                freopen(OUTPUT, "w", stdout);
        #endif
        Solve::solve();
        return 0;
}