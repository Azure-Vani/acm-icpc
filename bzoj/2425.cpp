//#define Debug
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
typedef long long Long;
 
Long ans = 0;
Long hash[1000] = {0};
 
Long GetSetSum(Long *h) {
        Long l = 0; Long  a[10] = {0}, s = 0;
        for (long i = 0; i <10 ;i++)
                if(h[i] > 0)
                        a[ ++l ] = h[i], s += h[i];
 
        Long l1[1000] = {0}, l2[1000] = {0}, v1 = 0, v2 = 0;
        for (long i = 1; i <= s; i++) l1[i] = i; v1 = s;
        
        for (long i = 1; i<=l; i++)
                for (long j = 1; j <= a[i]; j++)
                        l2[ ++v2 ] = j;
        std::sort(l2 + 1, l2 + 1 + v2);
 
        Long p = 1,r = 1;
        for (long j = 1; j <= v1; j++) {
                r *= l1[j];
                while( p <= v2 && r % l2[p] == 0) r /= l2[p++];
        }
        return r;
}
 
int main(int argc, char ** argv){
        #ifdef Debug
                freopen("1.in","r",stdin);
        #endif
 
        char ch[6000];
        scanf("%s",ch);
        long n = strlen(ch);
        Long hash[1000] = {0};
        for (long i = 0; i < n; i++)
                hash[ch[i] - '0']++;
 
        for (long i = 0; i < n; i++) {
                Long s = 0;
                for (long k = 0; k <= ch[i] - '0' - 1; k++)
                        if(hash[k] > 0){
                                hash[k]--;
                                s += GetSetSum(hash);
                                hash[k]++;
                        }
                ans += s;
                hash[ch[i] - '0']--;
        }
        
        printf("%lld\n",ans);
        return 0;
}