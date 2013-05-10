//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
long f[60][60][30] = {0};
char ch[60];
long Dfs(long l, long r, long flag) {
        if (l == r) return f[l][r][flag] = (ch[l] != flag);
        if (f[l][r][flag] != -1) return f[l][r][flag];
        
        bool check = true;
        for (long i = l+1; i <= r; i++)
                if (ch[i] != ch[i-1]){
                        check = false;
                        break;
                }
        if (check) return f[l][r][flag] = (ch[l] != flag);
 
        long res = 0x6eeeeeee;
        for (long i = l; i < r; i++){
                long l1 = 0x6eeeeeee, l2= 0x6eeeeeee;bool hash1[30] = {0}, hash2[30] = {0};
                for (long j = l; j <= i; j++) hash1[ ch[j] - 'A'] = true;
                for (long j = i+1; j <=r; j++) hash2[ ch[j] - 'A'] = true;
 
                for (long color = 'A'; color <= 'Z'; color++){
                        if(hash1[color - 'A']) l1 = std::min(l1, Dfs(l, i, color) + (color != flag));
                        if(hash2[color - 'A']) l2 = std::min(l2, Dfs(i+1, r, color) + (color != flag));
                }
                if (l1 + l2 < res) res = l1 + l2;
        }
        return f[l][r][flag] = res;
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen ("1.in","r",stdin);
        #endif
        scanf("%s", ch);
        long n = strlen(ch), ans = 0x6eeeeeee;
        memset(f, -1, sizeof f);
        for (long i = 'A'; i <= 'Z'; i++){
                Dfs(0, n - 1, i);
                if (f[0][n-1][i]+1 < ans) ans = f[0][n-1][i]+1;
        }
        printf("%ld", ans);
        return 0;
}