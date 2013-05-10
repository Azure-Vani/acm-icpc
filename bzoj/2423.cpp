#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
 
const long MAXN = 5005;
const long MOD = 100000000;
 
#define max(a, b) ((a)>(b)?(a):(b))
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        string s1, s2;
        long f[2][MAXN] = {0}, g[2][MAXN] = {0};
        getline(cin, s1); getline(cin, s2);
        s1 = '#' + s1, s2 = '$' + s2;
        long n1 = s1.length() - 1, n2 = s2.length() - 1; bool now = 1, bef = 0;
 
        for (long i = 1; i < n1 - 1; i++) {
                now ^= 1, bef ^= 1;
                for (long j = 1; j < n2 - 1; j++) {
                        g[now][j] = f[now][j] = 0;
                        
                        f[now][j] = max(f[now][j - 1], f[bef][j]);
                        if( s1[i] == s2[j] )
                                f[now][j] = max(f[now][j], f[bef][j - 1] + 1);
 
                        if(f[now][j] == 1 && s1[i] == s2[j]) g[now][j] = 1;
                        if( s1[i] == s2[j] ) {
                                if( f[now][j] == f[bef][j - 1]  + 1)
                                        g[now][j] = (g[now][j] + g[bef][j - 1]) % MOD;
                                if( f[now][j] == f[bef][j] )
                                        g[now][j] = (g[now][j] + g[bef][j]) % MOD;
                                if( f[now][j] == f[now][j - 1] )
                                        g[now][j] = (g[now][j - 1] + g[now][j]) % MOD;
                        }else{
                                if( f[now][j - 1] < f[bef][j] ) {
                                        g[now][j] = g[bef][j];
                                }else
                                if( f[now][j - 1] > f[bef][j] ) {
                                        g[now][j] = g[now][j - 1];
                                }else {
                                        if( f[bef][j] > f[bef][j - 1] ) {
                                                g[now][j] = (g[bef][j] + g[now][j - 1]) % MOD;
                                        }
                                        else {
                                                g[now][j] = (g[now][j - 1] + g[bef][j] - g[bef][j - 1] + MOD ) % MOD;
                                        }
                                }
                        }
                }
        }
        cout <<f[now][n2 - 2]<<endl<<g[now][n2 - 2]<<endl;
        return 0;
}