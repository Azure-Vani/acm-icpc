// Author: Xiangyu Luo (Vani)

#include <algorithm>
#include <cstdio>
#define rep(i,l,r) for(int i = l; i <= r; i++)
using namespace std;
int n, a[110], f[110];
int main(void) {
	//freopen("puppet.in","r",stdin); freopen("puppet.out","w",stdout); 
	while (scanf("%d", &n) == 1) {
        a[0]=0;
        rep(i, 1, n) { scanf("%d", &a[i]); } a[n+1]=0;
    	sort(a,a+n+1);
        rep(i,1,n){
    		int &tmp = f[i]; tmp = 0;
    		rep(j,0,i - 1) {
    			rep(k, 0, i - j - 1) {
    				bool virgin = true;
    				rep(o, j + 1, i - k) if (abs(a[o] - a[o + k]) > 1) {virgin = false; break;}
    				if (virgin && abs(a[j + k] - a[i - k + 1]) > 1) tmp = max(tmp, f[j] + k);
    			}
    		}
    	}
    	printf("%d\n", f[n]);
    }
	return 0;
}